/*
 * TestPpmcT.cpp
 *
 *  Created on: 14/06/2010
 *      Author: matias
 */

#include "testPpmcT.h"

TestPpmcT::TestPpmcT() {
	BPlusTree* bPlusTree = new BPlusTree("arbol.dat",92,0.5);
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
	testPrintAllContexts();
}

void TestPpmcT::testCreateContext(){
	/*mainFixture->createContext("a");
	mainFixture->createContext("abs");
	mainFixture->createContext("n");
	mainFixture->showContexts();*/
}

void TestPpmcT::testAddCharacterToContext(){
	/*mainFixture->createContext("a");
	mainFixture->createContext("abs");
	mainFixture->createContext("n");
	mainFixture->addCharacterToContext("abs","a");
	mainFixture->showContexts();*/
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
