#include <iostream>
#include <sstream>

#include "../application/compresion/ppmc/PpmcTree.h"
#include "../logic/structures/tree/BPlusTree.h"
#include "../logic/logger/Logger.h"
#include <cstdlib>
#define UNDEFINED -1

using namespace std;

typedef enum {COMPRESS, DECOMPRESS, UNDEFINED_ACTION} actionTypeEnum;

int main(int argc, const char* argv[])
{
	if (argc == 1)
	{
		cout << "Comandos para usar el ppmc:" << endl;
		cout << "-c [orden] (comprime con contextos hasta el orden dado)" << endl;
		cout << "-d (Descomprime)" << endl;
		cout << "-f [path] (Indica el path del archivo a comprimir/descomprimir)" << endl;
		cout << "-e (Estadisticas)" << endl;
		cout << "-v (Imprime por pantalla las tablas de frecuencia para todos los contextos)" << endl;
		cout << "-vv [contexto] (Imprime las tablas de frecuencias para un contexto dado)" << endl;
		cout << "-h (Ayuda)" << endl;
		return 0;
	}
	int i;
	string saux;


	string filePath= "";
	string ctxName;
	int ctxOrder;
	bool showAllCTX=false;
	bool showOneCTX=false;
	bool showStatistics=false;
	bool showHelp=false;
	string logText;
	Logger *log = Logger::Instance();
	actionTypeEnum action =UNDEFINED_ACTION;



	//Obtengo todas las opciones seteadas para el compresor
	for(i=1; i < argc ; i++)
	{
		saux = argv[i];

		if(saux == "-f")
		{
			i++;
			if(i < argc)
				filePath = argv[i];
			else
			{
				cout << "Faltan parametros. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
				return 0;
			}

		}else
		if(saux == "-c")
		{
			action = COMPRESS;
			i++;
			if(i < argc)
			{
				saux = argv[i];
				ctxOrder = atoi(saux.c_str());

				//Verifico que haya sido un numero el contexto max
				if(ctxOrder == 0)
				{
					if(saux!="0")
					{
						cout << "Contexto maximo incorrecto. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
						return 0;
					}
				}

				if(ctxOrder <0 || ctxOrder >100)
				{
					cout << "Contexto maximo fuera de rango(debe estar entre 0 y 100). Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
					return 0;
				}
			}
			else
			{
				cout << "Faltan parametros. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
				return 0;
			}
		}
		else
		if(saux == "-d")
		{
			action = DECOMPRESS;
		}

		else
		if(saux == "-vv")
		{
			showOneCTX =true;
			i++;
			if(i < argc)
				ctxName = argv[i];
			else
			{
				cout << "Faltan parametros. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
				return 0;
			}
		}else

		if(saux == "-v")
			showAllCTX=true;
		else

		if(saux == "-e")
			showStatistics=true;
		else

		if(saux == "-h")
			showHelp=true;
		else
		{
			cout << "Parametro Invalido. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
			return 0;
		}

	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	//------------------------Validacion--------------------------------//

	//--------------------------compress/decompress---------------------//

	//action = COMPRESS;ctxOrder=10; filePath="she-is-my-sin.txt";

	if(action !=UNDEFINED_ACTION)
	{
		std::remove("contador.dat");
		std::remove("arbol.dat");
		std::remove("arbol.dat.free");
		if(filePath == "")
		{
			cout << "Debe ingresar el nombre del archivo. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
			return 0;
		}
	}
	GeneralStructure* tree = NULL;
	Ppmc* ppmcCompresor = NULL;

	try{
	tree = new BPlusTree("arbol.dat",65536,0.5);
	ppmcCompresor = new PpmcTree(tree);



	stringstream info;
	if(action == COMPRESS)
	{
		info << "Comprimiendo archivo "<<filePath<<  " con contexto "<<ctxOrder<<endl;
		logText = info.str();
		log->insert(&logText[0]);

		ppmcCompresor->compress(filePath, ctxOrder);

		logText = "La compresion fue exitosa\n";
		log->insert(&logText[0]);
	}

	else
		if(action == DECOMPRESS)
		{
			info << "Descomprimiendo archivo "<<filePath<<endl;
			logText = info.str();
			log->insert(&logText[0]);
			ppmcCompresor->deCompress(filePath);

			info.clear();
			info << "La compresion fue exitosa "<<endl;
			logText = info.str();
			log->insert(&logText[0]);
		}


	//---------------------------HELP-----------------------------------//
	if(showHelp)
	{

		cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
		cout << argv[0]<< " -c 2 -f texto.txt" << endl;
		cout << argv[0]<< " -c 2 -f texto.txt -e" << endl;
		cout << argv[0]<< " -v" << endl;
		cout << argv[0]<< " -vv DI" << endl;
		cout << argv[0]<< " -d -f texto.txt.ppmc2" << endl;



	}

	if(showAllCTX)
	{
		ppmcCompresor->printAllContexts();
	}

	else
		if(showOneCTX)
		{
			try{
				ppmcCompresor->printContext(ctxName);
			}
			catch (ManagerException e)
			{
				cout << "No se encontro el contexto "<< ctxName<<endl;
			}
		}


	if(showStatistics &&action == COMPRESS )
		ppmcCompresor->getStatistics(ctxOrder);

	}
	catch (CompressionException e)
	{
		logText = (e.what());
		log->insert(&logText[0]);
	}
	catch (ManagerException e)
	{
		logText = (e.what());
		log->insert(&logText[0]);
	}
	catch (PhysicalException e)
	{
		logText = (e.what());
		log->insert(&logText[0]);
	}
	catch(exception e)
	{
		logText = (e.what());
		log->insert(&logText[0]);
	}

	delete tree;
	delete ppmcCompresor;
	//delete log;
	return 0;
}
