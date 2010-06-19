/*
 * TestPpmcT.cpp
 *
 *  Created on: 14/06/2010
 *      Author: matias
 */

#include "testPpmcT.h"

TestPpmcT::TestPpmcT() {
	BPlusTree* bPlusTree = new BPlusTree("arbol.dat",92,0.5);
	this->mainFixture=new Ppmc(bPlusTree);
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
	testGetCharacterOccurrences();
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

void TestPpmcT::testGetCharacterOccurrences(){
	/*mainFixture->createContext("a");
	mainFixture->createContext("abs");
	mainFixture->createContext("n");
	mainFixture->addCharacterToContext("n","a");
	mainFixture->increaseFrequency("n","a");
	std::cout<<mainFixture->getCharacterOccurrences("n","a");
	mainFixture->showContexts();*/
}
