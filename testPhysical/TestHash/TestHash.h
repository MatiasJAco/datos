/*
 * TestHash.h
 *
 *  Created on: Jun 27, 2010
 *      Author: adrian
 */

#ifndef TESTHASH_H_
#define TESTHASH_H_

#include <iostream>
#include <sstream>
#include "../logic/structures/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/structures/hash/Hash.h"
#include "../logic/ppmc/md5/MD5.h"
#include "../logic/ppmc/bigint/BigIntegerLibrary.hh"
#include "../logic/ppmc/Ppmc.h"
#include "../logic/ppmc/PpmcHash.h"
#include "../application/compresion/common/FrequencyTable.h"
#include "../application/compresion/common/CharFrequency.h"

class TestHash {
public:
	TestHash();
	virtual ~TestHash();

	void testStringInputData();
	void testTable();
	void testTable2();
	void testTable3();
	void testTable4();
	void testModifyHash();
	void testRemoveHash();
	void testRemoveHash2();
	void testEjemplo();
	void testGetKeys();
	void testBigInt();
	void testMd5();
	void testHashFunction();
	void testFreqTable();
	void testPpmcHashComprimir();
	void testPpmcHashDescomprimir();
};

#endif /* TESTHASH_H_ */
