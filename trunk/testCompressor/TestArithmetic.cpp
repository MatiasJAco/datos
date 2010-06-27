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
	m_compressor = NULL;
}

TestArithmetic::~TestArithmetic() {
	// TODO Auto-generated destructor stub
	m_compressor = NULL;
}

void TestArithmetic::run()
{
//	testStatic("DIVIDIDOS","divididos.gzip");

	// Con este string se ve el bug.
	testStatic("estas","estas.gzip");

//	testStatic("Maria Celeste Maldonado","celeste.gzip");
}

void TestArithmetic::testStatic(std::string toCompress,std::string output)
{
	m_tocompress = new short[toCompress.size()];
	m_sizetoCompress = toCompress.size();

	initializeToCompress(toCompress);
	loadStaticFTable(toCompress);

	cout << m_ft.toPrintableString();

	m_filecompressed = output;
	m_maxsymbols = 256;

	testStaticCompress();
	testStaticDecompress();

	m_ft.clearTable();
	delete[] m_tocompress;
}

void TestArithmetic::testDinamic(std::string toCompress,std::string output)
{
	m_tocompress = new short[toCompress.size()];
	m_sizetoCompress = toCompress.size();

	initializeToCompress(toCompress);
	loadDinamicFTable();

	m_filecompressed = output;
	m_maxsymbols = 257;

	testDinamicCompress();
	testDinamicDecompress();

	m_ft.clearTable();
	delete [] m_tocompress;
}

void TestArithmetic::testStaticCompress()
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,m_maxsymbols);

	unsigned long i = 0;
	unsigned long qchars = m_ft.getFrequencyTotal();

	for (i = 0;i < qchars;i++)
	{
		char c = m_tocompress[i];
		m_compressor->compress(c,m_ft);
	}

	delete m_compressor;
}

void TestArithmetic::testStaticDecompress()
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,m_maxsymbols);

	int i = 0;
	int qchars = m_ft.getFrequencyTotal();

	for (i = 0; i< qchars; i++)
	{
		char c = m_compressor->decompress(m_ft);
		cout << c;
	}

	delete m_compressor;
}

void TestArithmetic::testDinamicCompress()
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,m_maxsymbols);

	int i = 0;

	for (i = 0;i < m_sizetoCompress;i++)
	{
		char c = m_tocompress[i];
		m_compressor->compress(c,m_ft);
		m_ft.increaseFrequency(c,1);
	}


	delete m_compressor;
}

void TestArithmetic::testDinamicDecompress()
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,m_maxsymbols);
	short c =  UNDEFINED_CHAR;

	while (c!=EOF_CHAR)
	{
		short c = m_compressor->decompress(m_ft);

		if (c!=EOF_CHAR)
		{
			m_ft.increaseFrequency(c,1);
			cout << (char)c;
		}
	}

	delete m_compressor;
}

// ------------------Metodos utilitarios--------------------------------

void TestArithmetic::initializeToCompress(std::string toCompress)
{
	int i = 0;
	m_sizetoCompress = toCompress.size();
	// Guardo en el arreglo el string.
	for (i = 0;i< m_sizetoCompress ;i++)
	{
		char c = toCompress[i];
		m_tocompress[i] = (short)c;
	}
}

// Devuelve la frecuencia de un simbolo en un string,
// podria llevarse a TableFrequency en un constructor con string.
unsigned long TestArithmetic::getFrequencySymbol(std::string frase,char c)
{
	int i = 0;
	int qchars = frase.size();

	unsigned long matchs = 0;

	for(i = 0; i< qchars;i++)
	{
		if (frase[i] == c)
			++matchs;
	}

	return matchs;
}

// Carga una tabla con todos  los caracteres ascii en 1 y el EOF.
void TestArithmetic::loadDinamicFTable()
{
	// Caracter ascii.
	short c = 0;
	int maxchars = 256;

	for(c = 0; c< maxchars;c++)
	{
		m_ft.setFrequency(c,1);
	}

	m_ft.setFrequency(EOF_CHAR,1);
}


void TestArithmetic::loadStaticFTable(std::string toCompress)
{
	int i = 0;
	m_sizetoCompress = toCompress.size();
	// Guardo las frecuencia de los caracteres.
	for (i = 0;i< m_sizetoCompress;i++)
	{
		unsigned long freq = m_ft.getFrequency(m_tocompress[i]);

		if (freq==0)
			m_ft.setFrequency(m_tocompress[i],getFrequencySymbol(toCompress,m_tocompress[i]));
	}
}
