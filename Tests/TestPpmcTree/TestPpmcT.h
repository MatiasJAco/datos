/*
 * testPpmcT.h
 *
 *  Created on: 14/06/2010
 *      Author: matias
 */

#ifndef TESTPPMCT_H_
#define TESTPPMCT_H_

#include "../logic/structures/tree/BPlusTree.h"
#include "../logic/input/StringInputData.h"
#include "../application/compresion/ppmc/Ppmc.h"
#include "../application/compresion/ppmc/PpmcTree.h"
#include <iostream>
#include <sstream>


using namespace std;


class TestPpmcT {

public:
	TestPpmcT();
	virtual ~TestPpmcT();

public:
	void run();

protected:
	void testCreateContext();
	void testExistsCharacterInContext();
	void testAddCharacterToContext();
	void testIncreaseFrequency();
	void testPrintAllContexts();
	void testGetNextContext();

private:
	PpmcTree* mainFixture;
};

#endif /* TESTPPMCT_H_ */
