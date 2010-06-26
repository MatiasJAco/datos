/*
 * TestCompressor.cpp
 *
 *  Created on: 26/06/2010
 *      Author: kira
 */

#include "TestArithmetic.h"

using namespace std;

int main(int argc, char *argv[])
{

	TestArithmetic* test = new TestArithmetic();

	test->run();

	delete test;

	return 0;
}
