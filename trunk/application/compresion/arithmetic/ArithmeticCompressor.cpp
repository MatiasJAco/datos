/*
 * ArithmeticCompressor.cpp
 *
 *  Created on: 16/06/2010
 *      Author: kira
 */

#include "ArithmeticCompressor.h"

ArithmeticCompressor::ArithmeticCompressor(Coder coder,const std::string fileName,unsigned int maxbits)
{
	m_coder = coder;
	m_maxbits = maxbits;

	m_floor = 0;
	m_roof = pow(2,maxbits)-1;

	if (m_coder == COMPRESSOR)
		m_bitFile = new BitFile(WRITE_FILE);
	else
		m_bitFile = new BitFile(READ_FILE);

	m_bitFile->open(fileName);
}

ArithmeticCompressor::~ArithmeticCompressor() {
	m_bitFile->close();
	delete m_bitFile;
}

void ArithmeticCompressor::compress(short symbol,FrequencyTable & ft)
{
	m_floor = getFloorSymbol(symbol,ft);
	m_roof = getRoofSymbol(symbol,ft);

	normalize();

	if (overflow())
		emit();
}

short ArithmeticCompressor::decompress(FrequencyTable& ft)
{
//	getSymbol(num,ft);

	return 0;
}

