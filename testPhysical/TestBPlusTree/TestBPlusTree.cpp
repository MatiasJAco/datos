/*
 * TestBPlusTree.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: adrian
 */

#include "TestBPlusTree.h"

TestBPlusTree::TestBPlusTree() {
}

TestBPlusTree::~TestBPlusTree() {
}

void TestBPlusTree::testBPlusTree() {
	TestTree* test1 = new TestTree();
	test1->run();
	delete test1;
}
