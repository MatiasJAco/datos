#include <iostream>
#include <sstream>

#include "../logic/ppmc/PpmcHash.h"
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
	int ctxOrder;
	bool showAllCTX=false;
	bool showOneCTX=false;
	bool showStatistics=false;
	bool showHelp=false;
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



	GeneralStructure* hash = new Hash();
	Ppmc* ppmcCompresor = new PpmcHash(hash);

	//------------------------Validacion--------------------------------//
	if(filePath == "")
	{
		cout << "Debe ingresar el nombre del archivo. Utilice \""<< argv[0]<< " -h\" para obtener mas ayuda. " << endl;
		return 0;
	}

	//--------------------------compress/decompress---------------------//
	if(action == COMPRESS)
		ppmcCompresor->compress(filePath, ctxOrder);
	else
		if(action == DECOMPRESS)
			ppmcCompresor->deCompress(filePath);


	//---------------------------HELP-----------------------------------//
	if(showHelp)
	{

		cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
		cout << argv[0]<< " -I \"(12;paytiti)\"" << endl;
		cout << argv[0]<< " -B \"(12;)\"" << endl;
		cout << argv[0]<< " -M \"(12;pepe)\"" << endl;
		cout << argv[0]<< " -Q \"(12;)\"" << endl;
		cout << argv[0]<< " -S" << endl;


	}

	if(showAllCTX)
		ppmcCompresor->printAllContexts();
	else
		if(showOneCTX)
			ppmcCompresor->printContext(ctxName);

	if(showStatistics)
		ppmcCompresor->getStatistics();


	delete ppmcCompresor;

	return 0;
}
