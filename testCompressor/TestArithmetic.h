/*
 * TestArithmetic.h
 *
 *  Created on: 26/06/2010
 *      Author: kira
 */

#ifndef TESTARITHMETIC_H_
#define TESTARITHMETIC_H_

#include "../application/compresion/arithmetic/ArithmeticCompressor.h"

class TestArithmetic {

public:
	TestArithmetic();
//	TestArithmetic(ArithmeticCompressor::Coder coder,std::string fileName);
	virtual ~TestArithmetic();

	void run();

protected:

	void testCompress();
	void testDecompress();

private:
	ArithmeticCompressor* m_compressor;

	FrequencyTable m_ft;

	std::string m_tocompress;
	std::string m_filecompressed;
};

#endif /* TESTARITHMETIC_H_ */
