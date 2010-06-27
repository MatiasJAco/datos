/*
 * main.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: Adrián Bernardi
 */

#include "../Tests/TestPhysical/TestPhysical.h"
#include "../Tests/TestNode/TestNode.h"
#include "../Tests/TestLogger/TestLogger.h"
#include "../Tests/TestBPlusTree/TestBPlusTree.h"
#include "../Tests/TestCompressor/TestArithmetic.h"
#include "../Tests/TestPpmcTree/TestPpmcT.h"
#include "../Tests/TestHash/TestHash.h"

void testAllPhysical() {
	TestPhysical* testPhysical = new TestPhysical();
	try {
		//testPhysical->testVarRegister();
		//testPhysical->testFixedRegister();
		//testPhysical->testFreeBlockFile();
		//testPhysical->testBlock();
		//testPhysical->testFile();
		testPhysical->testSecuentialFile();
	}
	catch (PhysicalException e) {
		std::cout << e.what() << std::endl;
	}
}

void testAllNode() {
	TestNode* testNode = new TestNode();
	testNode->testNode();
}

void testAllLogger() {
	TestLogger* testLogger = new TestLogger();
	testLogger->testLogger();
}

void testAllBPlusTree() {
	TestBPlusTree* testBPlusTree = new TestBPlusTree();
	testBPlusTree->testBPlusTree();
}

void testAllArithmetic() {
	TestArithmetic* test = new TestArithmetic();
	test->run();
	delete test;
}

void testAllPpmcTree() {
	TestPpmcT* test1 = new TestPpmcT();
	test1->run();
	delete test1;
}

void testAllHash() {
	TestHash* testHash = new TestHash();

	/* TESTS DE HASH */
	//testHash->testRemoveHash();
	//testHash->testRemoveHash2();
	//testHash->testEjemplo();
	//testHash->testModifyHash();
	//testHash->testGetKeys();

	/* TESTS VARIOS */
	//testHash->testStringInputData();
	//testHash->testFreqTable();

	/* TESTS DE PPMC */
	testHash->testPpmcHashComprimir();
	//testHash->testPpmcHashDescomprimir();

	/* TESTS PARA LA FUNCION HASH NUEVA */
	//testHash->testBigInt();
	//testHash->testMd5();
	//testHash->testHashFunction();

	/*  TESTS TABLE */
	//testHash->testTable();
	//testHash->testTable2();
	//testHash->testTable3();
	//testHash->testTable4();
}

int main() {
	//testAllPhysical();
	//testAllNode();
	//testAllLogger();
	//testAllBPlusTree();
	//testAllArithmetic();
	//testAllPpmcTree();
	testAllHash();
	return 0;
}
