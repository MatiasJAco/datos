/*
 * testPhysical.cpp
 *
 *  Created on: 13/04/2010
 *      Author: alex
 */
#include "../physical/file/VarRegister.h"
#include "../physical/file/FixedRegister.h"
#include "../physical/file/BlockFile.h"
#include "../physical/file/FreeBlockFile.h"
#include "../physical/utils/ByteConverter.h"
#include <sstream>
#include <fstream>

using namespace std;

////////////////////////////////////////////////////////////////

void testVarRegister()
{
	cout<< "Testeo reg variables"<<endl;

	VarRegister *varR = new VarRegister();

	long longVar=123443232434;
	long longVar2;
	int intVar=123455666;
	int intVar2;
	string stringVar ="tu madre!";
	string stringVar2;

	char * streamVar;

	//Se pasa la direccion del valor casteada a puntero a char
	if(!varR->setValue((char*)&longVar, sizeof(longVar)))
		cout << "Fallo al setear registro long "<<endl;

	if(varR->getSize() != sizeof(longVar))
		cout << "getSize error"<<endl;

	streamVar = varR->getValue();

	longVar2=ByteConverter::bytesToLong(streamVar);

	if(longVar!=longVar2)
	{
		cout <<"long1 "<<longVar<<",long2 "<<longVar2<<endl;
		cout << "Error en registro longs"<<endl;
	}


	delete []streamVar;

	if(!varR->setValue((char*)&intVar, sizeof(intVar)))
		cout << "Fallo al setear registro long "<<endl;

	streamVar = varR->getValue();

	intVar2=ByteConverter::bytesToInt(streamVar);

	if(intVar!=intVar2)
	{
		cout <<"int1 "<<intVar<<",intg2 "<<intVar2<<endl;
		cout << "Error en registro int"<<endl;
	}


	delete [] streamVar;

	if(!varR->setValue((char*)stringVar.c_str(), stringVar.size()+1))
		cout << "Fallo al setear registro string "<<endl;

	if(varR->getSize() != stringVar.size()*sizeof(char)+1)
		cout << "getSize error"<<endl;

	streamVar = varR->getValue();

	stringVar2=ByteConverter::bytesToString(streamVar);

	if(stringVar!=stringVar2)
	{
		cout <<"string1 "<<stringVar<<",string2 "<<stringVar2<<endl;
		cout << "Error en registro string"<<endl;
	}


	delete [] streamVar;

	delete varR;
	cout<< "Fin Testeo reg variables"<<endl;
	cout<< "------------------------"<<endl;
}



void testFixedRegister()
{
	cout<< "Testeo reg fijos"<<endl;


	FixedRegister *fixedR = new FixedRegister();

	if(fixedR->getSize() != 0)
		cout << "getSize error1"<<endl;

	long longVar=123443232434;
	long longVar2=0;
	int intVar=123455666;
	int intVar2=0;
	string stringVar ="tu madre!";
	string stringVar2="";

	char * streamVar;

	//Se pasa la direccion del valor casteada a puntero a char
	if(!fixedR->setValue((char*)&longVar, sizeof(longVar)))
		cout << "Fallo al setear registro long"<<endl;
	streamVar = fixedR->getValue();

	if(fixedR->getSize() != sizeof(longVar))
		cout << "getSize error2"<<endl;

	longVar2=ByteConverter::bytesToLong(streamVar);

	if(longVar!=longVar2)
	{
		cout <<"long1 "<<longVar<<",long2 "<<longVar2<<endl;
		cout << "Error en registro longs"<<endl;
	}


	delete []streamVar;

	if(!fixedR->setValue((char*)&intVar, sizeof(intVar)))
		cout << "Fallo al setear registro int "<<endl;

	streamVar = fixedR->getValue();

	intVar2=ByteConverter::bytesToInt(streamVar);

	if(intVar!=intVar2)
	{
		cout <<"int1 "<<intVar<<",intg2 "<<intVar2<<endl;
		cout << "Error en registro int"<<endl;
	}


	delete [] streamVar;

	if(!fixedR->setValue((char*)stringVar.c_str(), stringVar.size()+1))
		cout << "Fallo al setear registro int "<<endl;

	streamVar = fixedR->getValue();

	stringVar2=ByteConverter::bytesToString(streamVar);

	if(stringVar!=stringVar2)
	{
		cout <<"string1 "<<stringVar<<",string2 "<<stringVar2<<endl;
		cout << "Error en registro string"<<endl;
	}


	delete [] streamVar;

	delete fixedR;

	cout<< "Fin Testeo reg fijos"<<endl;
	cout<< "------------------------"<<endl;

}

void testFreeBlockFile()
{
	cout << "testeo archivo bloques libres"<<endl;
	FreeBlockFile *archivo=new FreeBlockFile();

	if(!archivo->open("free"))
		cout << "error al abrir el archivo de bloques libres"<<endl;

	unsigned int entrada=30;
	archivo->pushFreeBlock(entrada);

	unsigned int salida=0;

	if(!archivo->popFreeBlock(salida))
		cout << "error al leer el archivo de bloques libres"<<endl;

	if(entrada !=salida)
		cout << "Error en el push pop salida:"<<salida<<endl;


	 for(int i=0; i <100; i++)
	 {
		 archivo->pushFreeBlock(i);
		 if(i==57)
		 {
			 if(!archivo->popFreeBlock(salida))
			 {
				 cout << "Error del pop 57"<<endl;
			 }
			 if(salida!=57)
				 cout <<"error 57"<<endl;
		 }
	 }

	 archivo->showFreeNodes();

	 for(int i=0; i <99; i++)
	 {
		 if(!archivo->popFreeBlock(salida))
		 {
			 cout << "Error en el pop"<< i<<endl;
		 }


		 if(salida==57)
		 {
				 cout <<"error 57"<<endl;
		 }
	 }

	 if(archivo->popFreeBlock(salida))
	 {
		 cout << "error, no reporta archivo vacio"<<endl;
	 }

	 archivo->showFreeNodes();

	archivo->close();
	delete archivo;

	cout << "fin testeo archivo bloques libres"<<endl;
	cout<< "------------------------"<<endl;


}
void testFile()
{
	cout << "Testeo de file"<<endl;
	BlockFile *archivo=new BlockFile("./pepito", 0.5);

	Block*block;
	Block*block2;

	if(!archivo->open("./pepito", 512))
		cout << "Error al abrir pepito"<<endl;


	block = archivo->getNewBlock();

	block2=archivo->getNewBlock();
	archivo->saveBlock(block2);
	delete block2;

	block2=archivo->getNewBlock();
	archivo->saveBlock(block2);
	delete block2;

	block2=archivo->getNewBlock();
	archivo->saveBlock(block2);
	delete block2;

	archivo->deleteBlock(2);

	block2=archivo->getNewBlock();
	if(block2->getBlockNumber()!=2)
		cout << "Error en el nodo libre recuperado"<<endl;

	archivo->saveBlock(block2);
	delete block2;

	cout << "Insercion"<<endl;

	VarRegister *varR = new VarRegister();

	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		varR->setValue(i);
		if(!block->addRegister(*varR))
			cout << "Se acabo el espacio"<<endl;

	}
	block->printRegisters();

	string valorString="tu madre!";
	varR->setValue(valorString);

	block->addRegister(*varR);

	long j=42333;
	varR->setValue((char*)&j,sizeof(long));

	block->addRegister(*varR);
	block->printRegisters();

	VarRegister var2;

	cout << "Recuperacion"<<endl;
	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		var2=block->getNextRegister();
		if(ByteConverter::bytesToInt(var2.getValue()) !=  i)
			cout << "Error en getNextRegister()"<<endl;
	}

	cout <<"Guardado bloque"<<endl;
	delete varR;

	if(block==NULL)
		cout << "error al crear el bloque"<<endl;

	if(!archivo->saveBlock(block))
		cout <<"Error al salvar el bloque"<<endl;

	delete block;
	delete archivo;
	block=NULL;


	//----------------------Recuperacion de datos--------------------------//
	BlockFile *archivo2=new BlockFile();
	if(!archivo2->open("./pepito", 512))
		cout << "2 Error al abrir pepito"<<endl;

	block = archivo2->getBlock(1);

	cout << "Recuperacion desde otra instancia de File"<<endl;
	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		var2=block->getNextRegister();
		if(ByteConverter::bytesToInt(var2.getValue()) !=  i)
			cout << "Error en getNextRegister()"<<endl;
	}




	delete block;
	delete archivo2;

	cout << "Fin Testeo de file"<<endl;
	cout<< "------------------------"<<endl;

}

void testBlock()
{
	cout << "Testeo de block"<<endl;
	BlockFile *archivo=new BlockFile("./pepito", 0.5);

	Block*block;
	Block*block2;

	if(!archivo->open("./pepito", 512))
		cout << "Error al abrir pepito"<<endl;

	if(block==NULL)
		cout << "Error al pedir bloque nuevo"<<endl;
	block = archivo->getNewBlock();

	block2=archivo->getNewBlock();
	if(block2==NULL)
		cout << "Error al pedir bloque nuevo"<<endl;
	archivo->saveBlock(block2);
	delete block2;

	block2=archivo->getNewBlock();
	if(block2==NULL)
		cout << "Error al pedir bloque nuevo"<<endl;
	archivo->saveBlock(block2);
	delete block2;

	block2=archivo->getNewBlock();
	if(block2==NULL)
		cout << "Error al pedir bloque nuevo"<<endl;
	archivo->saveBlock(block2);
	delete block2;

	archivo->deleteBlock(2);

	block2=archivo->getNewBlock();
	if(block2->getBlockNumber()!=2)
		cout << "Error en el nodo libre recuperado"<<endl;

	archivo->saveBlock(block2);
	delete block2;

	cout << "Insercion"<<endl;

	VarRegister *varR = new VarRegister();

	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		varR->setValue(i);
		if(!block->addRegister(*varR))
			cout << "Se acabo el espacio"<<endl;

	}
	block->printRegisters();

	string valorString="tu madre!";
	varR->setValue(valorString);

	block->addRegister(*varR);

	long j=42333;
	varR->setValue((char*)&j,sizeof(long));

	block->addRegister(*varR);
	block->printRegisters();

	VarRegister var2;

	cout << "Recuperacion"<<endl;
	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		var2=block->getNextRegister();
		if(ByteConverter::bytesToInt(var2.getValue()) !=  i)
			cout << "Error en getNextRegister()"<<endl;
	}

	cout <<"Guardado bloque"<<endl;
	delete varR;

	try{
		string enorme = "sadlnaslndsak,ndskljanñkljndaLKJNSDAÑKLASNKLJDASNKLJSD"
				"NKLJASDNLKJNLDKJSNkljjklJKLKJASJKASDJKLJKSADJKJKSADASDDASKKDSJAK"
				"ASasdlhakljkñljlñkasdñlasñlkjñlkjñsdaDKJDHJsdkhkassadhdsahjkasdsa"
				"daJKLÑSDJKLDJLKDJSjhdshJKDHHDlkAJHDLKAJSHdlakHDLShdAKLJHDKLJSHdkljALK"
				"LKLkjsdalkjadslkjslkñAJDÑLKAJdñlkjaDÑLKJSlñdkjALDJALÑKSdjñlAJDLASJDLKA"
				"sdañKJDSLKJLKDJlkdjldñasjdñlJADLKHDSFKJHHLKDJJHFlkjhaskjhkljfsdhlkjSDLKJSAD"
				"LKDJALKjdsalkjsdaLKJDLKJASDLKJLKjdsalkjsadlkjasdlkkdjdlkdJLSKADJLKASDJ"
				"ASDLÑJKLjdslkjsadlkjkljLKJSADLKJSADLKJLKSDJALKSADHJX MZ,MNDLAMÑLSAKADsd"
				"lsakdjlkjf,MN KJXHYOEWJPWPOUPOwepoeipoerkñEKOERIAJÑDLFÑLASDKÑAKLFFsadsda";

		varR->setValue(enorme);
		block->addRegister(*varR);
		cout <<"error en limitacion del registro";

	}catch(char const* c)
	{

	}


	delete block;
	delete archivo;
	block=NULL;



	delete block;

	cout << "Fin Testeo de block"<<endl;
	cout<< "------------------------"<<endl;

}

int main()
{
try
{
	testVarRegister();
	testFixedRegister();
	testFreeBlockFile();
	testBlock();
	testFile();
}
catch (exception e)
{
	cout <<e.what()<<endl;
}






	return 0;
}
