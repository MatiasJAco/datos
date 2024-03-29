/*
 * testPhysical.cpp
 *
 *  Created on: 13/04/2010
 *      Author: alex
 */

#include "TestPhysical.h"

using namespace std;

////////////////////////////////////////////////////////////////

void TestPhysical::testVarRegister()
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



void TestPhysical::testFixedRegister()
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

void TestPhysical::testFreeBlockFile()
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

	 //archivo->showFreeNodes();

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

	 //archivo->showFreeNodes();

	archivo->close();
	delete archivo;

	cout << "fin testeo archivo bloques libres"<<endl;
	cout<< "------------------------"<<endl;


}
void TestPhysical::testFile()
{
	cout << "Testeo de file"<<endl;
	char * streamVar2;
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
		streamVar2 = var2.getValue();
		if(ByteConverter::bytesToInt(streamVar2) !=  i)
			cout << "Error en getNextRegister()"<<endl;
		delete [] streamVar2;
	}

	cout <<"Guardado bloque"<<endl;
	delete varR;

	if(block==NULL)
		cout << "error al crear el bloque"<<endl;

	if(!archivo->saveBlock(block))
		cout <<"Error al salvar el bloque"<<endl;

	delete block;

	block=NULL;

	delete archivo;

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
		streamVar2 = var2.getValue();
		if(ByteConverter::bytesToInt(streamVar2) !=  i)
			cout << "Error en getNextRegister()"<<endl;
		delete [] streamVar2;
	}



	archivo2->deleteFile();

	delete block;
	delete archivo2;

	cout << "Fin Testeo de file"<<endl;
	cout<< "------------------------"<<endl;

}

void TestPhysical::testBlock()
{
	cout << "Testeo de block"<<endl;
	BlockFile *archivo=new BlockFile("./pepito2", 0.5);

	Block*block;
	Block*block2;

	VarRegister var2;
	VarRegister *varR = new VarRegister();
	loadResultEnum loadResult;

	if(!archivo->open("./pepito2", 512))
		cout << "Error al abrir pepito"<<endl;

	block = archivo->getNewBlock();
	if(block==NULL)
		cout << "Error al pedir bloque nuevo"<<endl;


	if(block->getMinimalLoad() != 256)
		cout << "Error de getMinimalLoad(), resultado:"<<block->getMinimalLoad()<<endl;

	block2=archivo->getNewBlock();
	if(block2==NULL)
		cout << "Error al pedir bloque nuevo"<<endl;

	if(block2->getPosActual()!= -1)
		cout << "Error en pos actual1 "<<endl;


	block2->restartCounter();
	for(int i=0; i < 31; i++)
	{
		varR->setValue(i);
		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	if(block2->getPosActual()!= 30)
		cout << "Error en pos actual2 "<< block2->getPosActual()<< endl;


	string stringLargo = "esto la rompe seguro";
	varR->setValue(stringLargo);

	if(!block2->addRegister(*varR, loadResult))
		cout << "Se acabo el espacio"<<endl;

	for(int i=32; i < 60; i++)
	{
		varR->setValue(i);
		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}
	//block2->printRegisters();

	if(block2->getPosActual()!= 0x3b)
		cout << "Error en pos actual3 "<< block2->getPosActual()<< endl;

	if(block2->addRegister(*varR, loadResult))
		cout << "error de addRegister"<<endl;

	if(loadResult!=OVERFLOW_LOAD)
		cout << "No se detecto overflow"<<endl;


	cout << "-----------SPLIT------------------"<<endl;
	block2->getRegisterN(block2->getRegisterAmount()-1);

	var2=block2->getNextRegister(false);

	char * streamVar2 = var2.getValue();
	//cout << "actual"<< ByteConverter::bytesToInt(streamVar2)<<endl;
	delete [] streamVar2;

	block2->deleteRegister();

	var2=block2->getNextRegister(false);

	streamVar2 = var2.getValue();
	//cout << "actual"<< ByteConverter::bytesToInt(streamVar2)<<endl;
	delete [] streamVar2;

	var2 = block2->getRegisterN(31);
	streamVar2 = var2.getValue();
	if(ByteConverter::bytesToString(streamVar2)!= stringLargo)
		cout << "Error en el getRegisterN()"<<endl;

	delete [] streamVar2;


	block->clear();
	var2.setValue(1234);
	block->addRegister(var2);

	var2.setValue(23132123);
	BlockManager::redistributeOverflow(block2, block, var2, 1);

	//block2->printRegisters();
	//block->printRegisters();


	cout << "-----------fin SPLIT------------------"<<endl;
	cout << "Insercion"<<endl;

	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		varR->setValue(i);
		if(!block->addRegister(*varR))
			cout << "Se acabo el espacio"<<endl;

	}
	//block->printRegisters();

	string valorString="tu madre!";
	varR->setValue(valorString);

	block->addRegister(*varR);

	long j=42333;
	varR->setValue((char*)&j,sizeof(long));

	block->addRegister(*varR);
	//block->printRegisters();



	cout << "Recuperacion"<<endl;
	block->restartCounter();
	for(int i=0; i < 10; i++)
	{
		var2=block->getNextRegister();
		streamVar2 = var2.getValue();
		if(ByteConverter::bytesToInt(streamVar2) !=  i)
			cout << "Error en getNextRegister()"<<endl;
		delete []streamVar2;
	}

	cout <<"Guardado bloque"<<endl;


	try{
		string enorme = "sadlnaslndsak,ndskljan�kljndaLKJNSDA�KLASNKLJDASNKLJSD"
				"NKLJASDNLKJNLDKJSNkljjklJKLKJASJKASDJKLJKSADJKJKSADASDDASKKDSJAK"
				"ASasdlhakljk�ljl�kasd�las�lkj�lkj�sdaDKJDHJsdkhkassadhdsahjkasdsa"
				"daJKL�SDJKLDJLKDJSjhdshJKDHHDlkAJHDLKAJSHdlakHDLShdAKLJHDKLJSHdkljALK"
				"LKLkjsdalkjadslkjslk�AJD�LKAJd�lkjaD�LKJSl�dkjALDJAL�KSdj�lAJDLASJDLKA"
				"sda�KJDSLKJLKDJlkdjld�asjd�lJADLKHDSFKJHHLKDJJHFlkjhaskjhkljfsdhlkjSDLKJSAD"
				"LKDJALKjdsalkjsdaLKJDLKJASDLKJLKjdsalkjsadlkjasdlkkdjdlkdJLSKADJLKASDJ"
				"ASDL�JKLjdslkjsadlkjkljLKJSADLKJSADLKJLKSDJALKSADHJX MZ,MNDLAM�LSAKADsd"
				"lsakdjlkjf,MN KJXHYOEWJPWPOUPOwepoeipoerk�EKOERIAJ�DLF�LASDK�AKLFFsadsda";

		varR->setValue(enorme);
		block->addRegister(*varR);
		cout <<"error en limitacion del registro";

	}catch(char const* c)
	{

	}

	block->clear();

	varR->setValue(valorString);


	block->addRegister(*varR);


	//block->printRegisters();

	block->clear();

	unsigned int freeSpace = block->getRemainingSpace();
	if(freeSpace != 512-8)
		cout << "Error en el espacio libre del bloque"<< freeSpace<<endl;

	for(int i=0; i < 63; i++)
	{
		varR->setValue(i);
		if(!block->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	if(block->addRegister(*varR, loadResult))
		cout << "error de addRegister"<<endl;

	if(loadResult!=OVERFLOW_LOAD)
		cout << "No se detecto overflow"<<endl;

	freeSpace = block->getRemainingSpace();

	if(freeSpace!=0)
		cout << "Error en el espacio libre del bloque"<< freeSpace<<endl;

	block->restartCounter();

	varR->setValue(890);

	block->modifyRegister(*varR, loadResult);

	block->restartCounter();
	var2 = block->getNextRegister();

	streamVar2 = var2.getValue();
	if(ByteConverter::bytesToUInt(streamVar2)!=890)
		cout << "Error al modificar registro en caso de OVERFLOW"<<endl;

	delete [] streamVar2;

	if(loadResult ==OVERFLOW_LOAD)
		cout << "Falso Overflow"<<endl;

	cout << "-----------Merge----------------------"<<endl;


	block->clear();
	block2->clear();

	for(int i=0; i < 31; i++)
	{
		varR->setValue(i);

		if(!block->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;

		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	BlockManager::merge(block, block2);

	//block2->printRegisters();
	//block->printRegisters();



	block->restartCounter();

	var2 = block->peekRegister();
	streamVar2 = var2.getValue();
	//cout << "PEEK"<< ByteConverter::bytesToUInt(streamVar2)<<endl;
	delete []streamVar2;

	block->deleteRegister();

	//block->deleteRegister();

	if(block->getPosActual()!= 0)
		cout << "Error en pos actual2 "<< block->getPosActual()<< endl;

/*	block->jumpEndCounter();
	block->deleteRegister();*/

	//int pos = block->getPosActual();
	//int regAmount = block->getRegisterAmount();

	//if(pos!= regAmount-1)
	//	cout << "Error en pos actual3 "<< pos<< endl;
	//block->printRegisters();


	cout << "-----------Redistribute----------------------"<<endl;


	block->clear();
	block2->clear();

	for(int i=0; i < 31; i++)
	{
		varR->setValue(i);

		if(!block->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}


	for(int i=0; i < 16; i++)
	{
		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	if(BlockManager::balanceLoad(block, block2,LEFT_SIDE))
		cout << "Error en balance lft 1"<<endl;

/*	block2->printRegisters();
	block->printRegisters();*/

	block->clear();
	block2->clear();

	for(int i=0; i < 63; i++)
	{
		varR->setValue(i);

		if(!block->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}


	for(int i=63; i < 79; i++)
	{
		varR->setValue(i);

		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	//block2->printRegisters();
	//block->printRegisters();
	cout << "-------------redistribute left----------"<<endl;

	if(!BlockManager::balanceLoad(block, block2,LEFT_SIDE))
		cout << "Error en balance lft 2"<<endl;

	//block2->printRegisters();
	//block->printRegisters();


	cout << "-----------Redistribute-Right---------------------"<<endl;


	block->clear();
	block2->clear();

	for(int i=0; i < 16; i++)
	{
		varR->setValue(i);

		if(!block->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}


	for(int i=0; i < 32; i++)
	{
		varR->setValue(i);

		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	if(BlockManager::balanceLoad(block, block2,RIGHT_SIDE))
		cout << "Error en balance RGT 1"<<endl;

	//block2->printRegisters();
	//block->printRegisters();


	block->clear();
	block2->clear();

	for(int i=0; i < 16; i++)
	{
		varR->setValue(i);

		if(!block->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}


	for(int i=16; i < 79; i++)
	{
		varR->setValue(i);

		if(!block2->addRegister(*varR, loadResult))
			cout << "Se acabo el espacio"<<endl;

		if(loadResult ==OVERFLOW_LOAD)
			cout << "Falso Overflow"<<endl;
	}

	//block2->printRegisters();
	//block->printRegisters();
	cout << "-------------redistribute left----------"<<endl;

	if(!BlockManager::balanceLoad(block, block2,RIGHT_SIDE))
		cout << "Error en balance lft 2"<<endl;

	//block2->printRegisters();
	//block->printRegisters();





	delete varR;
	delete block;
	delete block2;
	delete archivo;
	block=NULL;



	delete block;

	cout << "Fin Testeo de block"<<endl;
	cout<< "------------------------"<<endl;

}


void TestPhysical::testSecuentialFile()
{
	try{
		SequentialFile file1(WRITE_FILE);
		SequentialFile file2(READ_FILE);

		file1.setBufferSize(10);

		string input= "Devon won't go to heaven";
		string input2= "she's just another lost soul";
		char * output=new char[input.size()+1];

		file1.open("devon");

		file1.writeNChar(input.c_str(), input.size()+1);
		file1.close();

		file1.open("devon");
		file1.writeNChar(input2.c_str(), input2.size()+1);


		file1.close();
		file2.open("devon");
		if(!file2.readNChar(output, input.size()+1))
			cout << "Hubo eof erroneo"<<endl;

		cout  << output<<endl;

		if(!file2.readNChar(output, input2.size()+1))
			cout << "Hubo eof erroneo"<<endl;

		if(file2.readNChar(output, 1))
			cout << "Falto eof ok1"<<endl;

		bool isEof;

		file2.readChar(isEof);

		if(isEof)
			cout << "Falto eof"<<endl;

		file2.close();
		file2.deleteFile();
		delete output;

	}
	catch(PhysicalException e)
	{
		cout << "ERROR"<<endl;
		cout << e.what()<<endl;
	}

}
