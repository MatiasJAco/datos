/*
 * testBPlusTree.cpp
 *
 *  Created on: 29/04/2010
 *      Author: matias
 */
#include <iostream>
#include <sstream>
#include "../logic/structures/tree/BPlusTree.h"


#include "TestTree.h"


using namespace std;

int main(int argc, char *argv[])
{
	TestTree* test1 = new TestTree();

	test1->run();

	delete test1;

}
