/*
 * TestPpmcT.cpp
 *
 *  Created on: 14/06/2010
 *      Author: matias
 */

#include "TestPpmcT.h"

TestPpmcT::TestPpmcT() {
	BPlusTree* bPlusTree = new BPlusTree("arbol.dat", 120, 0.5);
	this->mainFixture=new PpmcTree(bPlusTree);
}

TestPpmcT::~TestPpmcT() {
	if (mainFixture!=NULL)
		delete mainFixture;
}

void TestPpmcT::run()
{
//	testCreateContext();
//	testExistsCharacterInContext();
//	testAddCharacterToContext();
//	testIncreaseFrequency();
//	testPrintAllContexts();
//	testGetNextContext();
	testPpmcTreeCompress();
}

void TestPpmcT::testCreateContext(){
	/*mainFixture->createContext("a");
	mainFixture->createContext("abs");
	mainFixture->createContext("n");
	mainFixture->showContexts();*/
}

void TestPpmcT::testAddCharacterToContext(){
	short character=150;
	std::string stringContext="ab";
	FrequencyTable* frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	character=25;
	stringContext="s";
	delete frequencyTable;
	frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,3); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	character=176;
	stringContext="b";
	delete frequencyTable;
	frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	StringInputData stringInputData;
	mainFixture->findInStructure("ab",stringInputData);
	frequencyTable->deserialize(stringInputData.getValue());
	frequencyTable->setFrequency(15,1);
	mainFixture->modifyInStructure("ab",frequencyTable->toString());
	mainFixture->printAllContexts();
	}

void TestPpmcT::testIncreaseFrequency(){
	/*mainFixture->createContext("a");
	mainFixture->createContext("abs");
	mainFixture->createContext("n");
	mainFixture->addCharacterToContext("n","a");
	mainFixture->increaseFrequency("n","a");
	mainFixture->increaseFrequency("n","a");
	mainFixture->showContexts();*/
}

void TestPpmcT::testPrintAllContexts(){
	short character=150;
	std::string stringContext="ab";
	FrequencyTable* frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	character=25;
	stringContext="s";
	delete frequencyTable;
	frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,3); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	mainFixture->printAllContexts();

}

void TestPpmcT::testGetNextContext(){

	short character=150;
	std::string stringContext="tb";
	FrequencyTable* frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,2); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	character=25;
	stringContext="ab";
	delete frequencyTable;
	frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,3); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	character=176;
	stringContext="b";
	delete frequencyTable;
	frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	frequencyTable->setFrequency(character,5); // Agrega el caracter al contexto a crearse, con una ocurrencia.
	mainFixture->insertInStructure(stringContext,frequencyTable->toString());
	mainFixture->printAllContexts();
	StringInputData stringInputData;
	mainFixture->findInStructure("tb",stringInputData);
	mainFixture->getNextContext("b",stringInputData);
	frequencyTable->deserialize(stringInputData.getValue());
	std::cout<<frequencyTable->toPrintableString();

}

void TestPpmcT::testPpmcTreeCompress() {
	std::string path = "./archivoAComprimir.txt";
	int maxContext = 2;

	std::string previousCompressionFile = "archivoAComprimir.txt";
	previousCompressionFile.append(".ppmc");
	stringstream ss;
	ss << maxContext;
	previousCompressionFile.append(ss.str());

	std::remove(previousCompressionFile.c_str());
	this->mainFixture->compress(path, maxContext);

	std::remove("arbol.dat");
	std::remove("arbol.dat.free");
	std::remove("contador.dat");
	std::remove("logger.txt");
	std::remove("logger1.txt");
}
