/*
 * testPhysical.cpp
 *
 *  Created on: 13/04/2010
 *      Author: alex
 */
#include "../physical/file/VarRegister.h"
#include "../physical/file/FixedRegister.h"
#include "../physical/file/File.h"
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
	File *archivo=new File();

	Block*block;

	if(!archivo->openFile("./pepito", 1))
		cout << "Error al abrir pepito"<<endl;


	block = archivo->getNewBlock();

	if(block==NULL)
		cout << "error al crear el bloque"<<endl;


	if(!archivo->saveBlock(block))
		cout <<"Error al salvar el bloque"<<endl;

	delete archivo;

	cout << "Fin Testeo de file"<<endl;
	cout<< "------------------------"<<endl;

}

int main()
{

	testVarRegister();
	testFixedRegister();
	testFreeBlockFile();
	testFile();







	return 0;
}
