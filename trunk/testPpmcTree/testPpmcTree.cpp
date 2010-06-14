/*
 * testPpmcTree.cpp
 *
 *  Created on: 14/06/2010
 *      Author: matias
 */

#include <iostream>
#include <sstream>


#include "testPpmcT.h"


using namespace std;

int main(int argc, char *argv[])
{
	TestPpmcT* test1 = new TestPpmcT();

	test1->run();

	delete test1;

}
