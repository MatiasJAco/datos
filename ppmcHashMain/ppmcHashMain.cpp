#include <iostream>
#include <sstream>

#include "../application/compresion/ppmc/PpmcHash.h"
#include "../logic/structures/hash/Hash.h"
#include <cstdlib>

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
	int ctxOrder=1;
	bool showAllCTX=false;
	bool showOneCTX=false;
	bool showStatistics=false;
	bool showHelp=false;
	actionTypeEnum action =UNDEFINED_ACTION;
	string error;
	Logger *log = Logger::Instance();


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

	try{
	//--------------------------compress/decompress---------------------//
	if(action !=UNDEFINED_ACTION)
	{
		std::remove("tabla.txt");
		std::remove("hash.bin");
		std::remove("hash.bin.free");
		if(filePath == "")
		{
			cout << "Debe ingresar el nombre del archivo. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
			return 0;
		}
	}

	GeneralStructure* hash = new Hash();
	Ppmc* ppmcCompresor = new PpmcHash(hash);




	if(action == COMPRESS)
		ppmcCompresor->compress(filePath, ctxOrder);
	else
		if(action == DECOMPRESS)
			ppmcCompresor->deCompress(filePath);


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


	delete hash;
	delete ppmcCompresor;

	}
	catch (CompressionException e)
	{
		error = (e.what());
		log->insert(&error[0]);
	}
	catch (ManagerException e)
	{
		error = (e.what());
		log->insert(&error[0]);
	}
	catch (PhysicalException e)
	{
		error = (e.what());
		log->insert(&error[0]);
	}
	catch(exception e)
	{
		error = (e.what());
		log->insert(&error[0]);
	}

	delete log;

	return 0;
}
