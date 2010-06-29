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

	void testStatic(std::string toCompress,std::string output);
	void testDinamic(std::string toCompress,std::string output);

protected:
	void testStaticCompress();
	void testStaticDecompress();

	void testDinamicCompress();
	void testDinamicDecompress();

private:// Utilitarios.

	void initializeToCompress(std::string str);
	void loadStaticFTable(std::string);
	void loadDinamicFTable();
	unsigned long getFrequencySymbol(std::string frase,char c);

private:
	ArithmeticCompressor* m_compressor;

	FrequencyTable m_ft;

	short* m_tocompress;
	short m_sizetoCompress;

	std::string m_filecompressed;
	int m_maxbits;
};

#endif /* TESTARITHMETIC_H_ */
