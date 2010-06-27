/*
 * TestArithmetic.cpp
 *
 *  Created on: 26/06/2010
 *      Author: kira
 */

#include "TestArithmetic.h"

using namespace std;

TestArithmetic::TestArithmetic() {
	// TODO Auto-generated constructor stub

//	m_tocompress = "Naciste en una prisión que no puedes oler, probar ni tocar. Una prisión para tu mente";
	m_tocompress = "DIVIDIDOS";
	m_filecompressed = "comprimido.gzip"; //xD

	m_ft.setFrequency('D',3);
	m_ft.setFrequency('I',3);
	m_ft.setFrequency('O',1);
	m_ft.setFrequency('S',1);
	m_ft.setFrequency('V',1);
}

TestArithmetic::~TestArithmetic() {
	// TODO Auto-generated destructor stub

	if (m_compressor != NULL)
		delete m_compressor;
}

void TestArithmetic::run()
{
	testCompress();
//	testDecompress();
}

void TestArithmetic::testCompress()
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,256);


	int i = 0;
	int qchars = m_tocompress.size();

	for (i = 0;i < qchars;i++)
	{
		char c = m_tocompress[i];
		m_compressor->compress(c,m_ft);
	}

	delete m_compressor;
}

void TestArithmetic::testDecompress()
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,256);

	int i = 0;
	int qchars = m_ft.getFrequencyTotal();

	for (i = 0; i< qchars; i++)
	{
		char c = m_compressor->decompress(m_ft);
		cout << c << endl;
	}

}
