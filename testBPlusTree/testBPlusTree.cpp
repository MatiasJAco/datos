/*
 * testBPlusTree.cpp
 *
 *  Created on: 29/04/2010
 *      Author: matias
 */
#include <iostream>
#include <sstream>
#include "../logic/tree/BPlusTree.h"


#include "TestLeafNode.h"


using namespace std;

int main(int argc, char *argv[])
{
	TestLeafNode* test1 = new TestLeafNode();

	test1->run();

	delete test1;

}
