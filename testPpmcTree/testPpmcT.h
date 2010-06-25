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
#include "../logic/ppmc/Ppmc.h"
#include "../logic/ppmc/PpmcTree.h"

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
	void testGetCharacterOccurrences();


private:
	Ppmc* mainFixture;
};

#endif /* TESTPPMCT_H_ */
