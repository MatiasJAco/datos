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
//	std::string b = "I was born admist the purple waterfalls. I was weak, yet not unblessed. Death to the world, alive for the journey,1243254543634534534534534534598345098459083409583450309843509384509384509834905809283590283905829308590238509283095820938502938590843kjtoiawjuflkasjdoiut0989080935kjiosuf098twkejoisudf09awerkjoisudfoiasud09r81q43uasfj KIRA KIRA KIRA KIRA ASDF 1893 fasdkjfakls, akldfjkaljfd, paititi \n";
//	testStatic("DIVIDIDOS","divididos.gzip");

	// Con este string se ve el bug.
//	testStatic("I was born admist the purple waterfalls. I was weak, yet not unblessed. Death to the world, alive for the journey,1243254543634534534534534534598345098459083409583450309843509384509384509834905809283590283905829308590238509283095820938502938590843kjtoiawjuflkasjdoiut0989080935kjiosuf098twkejoisudf09awerkjoisudfoiasud09r81q43uasfj KIRA KIRA KIRA KIRA ASDF 1893 fasdkjfakls, akldfjkaljfd, paititi \n","random.gzip");
	std::string b = "ab";

	std::string file="she-is-my-sin";

	std::remove((file+".gzip").c_str());

	try
	{
		testDinamicFile((file+".txt").c_str());
	}
	catch(CompressionException e)
	{
		cout << e.what() << endl;
	}
}


void TestArithmetic::testDinamicFile(string archToCompress)
{
	SequentialFile* file;

	m_filecompressed = archToCompress.substr(0,archToCompress.find(".txt"))+".gzip";
	m_maxbits = 26;

	file = new SequentialFile(READ_FILE);
	file->setInputType(TEXT);
	string fileOrig = "filesOrig/"+archToCompress;

	file->open(fileOrig);
	loadDinamicFTable();
	testDinamicCompress(file);
	file->close();
	m_ft.clearTable();

	delete file;

	cout << "Compress terminado"<<endl;

	file = new SequentialFile(WRITE_FILE);
	file->setInputType(TEXT);
	string fileDesc = "filesDescomp/"+archToCompress;

	std::remove(fileDesc.c_str());
	file->open(fileDesc);
	loadDinamicFTable();
	testDinamicDecompress(file);
	file->close();
	m_ft.clearTable();

	delete file;

	cout << "Decompress terminado"<<endl;
}

void TestArithmetic::testDinamicCompress(SequentialFile* archToCompress)
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,m_maxbits);

	unsigned int i = 0;
	bool isNotEOF = true;

	while (isNotEOF)
	{
		char c = archToCompress->readChar(isNotEOF);

		if (isNotEOF)
		{
			m_compressor->compress(c,m_ft);
			m_ft.increaseFrequency(c,1);
			i++;
		}
	}

	m_compressor->compress(EOF_CHAR,m_ft);
	//m_compressor->compress('a',m_ft);

	delete m_compressor;
}

void TestArithmetic::testDinamicDecompress(SequentialFile* archdescomprimido)
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,m_maxbits);
	short c =  UNDEFINED_CHAR;
	int i = 0;

	while (c!=EOF_CHAR)
	{
		c = m_compressor->decompress(m_ft);

		if (c!=EOF_CHAR)
		{
//			cout << (char) c<<endl;
/*			if(i%10==0)
				cout <<endl;*/
			m_ft.increaseFrequency(c,1);
			archdescomprimido->writeChar(c);
			i++;
		}
	}

	delete m_compressor;
}

void TestArithmetic::testStaticFile(string archToCompress)
{
	throw "No esta implementado completamente el estatico para un archivo porque tendria que cargar la tabla de frecuencias";

	SequentialFile* file;

	m_filecompressed = archToCompress.substr(archToCompress.find(".txt"))+".gzip";
	m_maxbits = 8;

	file = new SequentialFile(READ_FILE);
	string fileOrig = "filesOrig/"+archToCompress;

	loadStaticFTable(file);

	file->open(fileOrig);
	testStaticCompress(file);
	file->close();

	delete file;

	file = new SequentialFile(WRITE_FILE);
	string fileDesc = "filesDescomp/"+archToCompress;

	std::remove(fileDesc.c_str());
	file->open(fileDesc);
	testStaticDecompress(file);
	file->close();

	delete file;

}


void TestArithmetic::testStaticCompress(SequentialFile* archToCompress)
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,m_maxbits);

	unsigned long i = 0;
	unsigned long qchars = m_ft.getFrequencyTotal();

	for (i = 0;i < qchars;i++)
	{
		char c = archToCompress->readChar();
		m_compressor->compress(c,m_ft);
	}

	delete m_compressor;

}

void TestArithmetic::testStaticDecompress(SequentialFile* archdescomprimido)
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,m_maxbits);

	int i = 0;
	int qchars = m_ft.getFrequencyTotal();

	for (i = 0; i< qchars; i++)
	{
		char c = m_compressor->decompress(m_ft);
		archdescomprimido->writeChar(c);
	}

	delete m_compressor;
}

void TestArithmetic::testStaticString(string toCompress,string archcomprimido)
{
	std::string decompressed;

	loadStaticFTable(toCompress);

	cout << m_ft.toPrintableString();

	m_filecompressed = archcomprimido;
	m_maxbits = 3;

	testStaticCompress(toCompress);
	testStaticDecompress(decompressed);

	m_ft.clearTable();

	cout << decompressed.c_str() << endl;
}

void TestArithmetic::testDinamicString(string toCompress,string archcomprimido)
{
	std::string decompressed;

	m_filecompressed = archcomprimido;

	m_maxbits = 8;


	loadDinamicFTable();
	testDinamicCompress(toCompress);
	m_ft.clearTable();

	loadDinamicFTable();
	testDinamicDecompress(decompressed);
	m_ft.clearTable();

	cout << decompressed.c_str() << endl;

}

void TestArithmetic::testStaticCompress(string toCompress)
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,m_maxbits);

	unsigned long i = 0;
	unsigned long qchars = m_ft.getFrequencyTotal();

	for (i = 0;i < qchars;i++)
	{
		char c = toCompress[i];
		m_compressor->compress(c,m_ft);
	}

	delete m_compressor;
}

void TestArithmetic::testStaticDecompress(string& decompressed)
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,m_maxbits);

	int i = 0;
	int qchars = m_ft.getFrequencyTotal();

	for (i = 0; i< qchars; i++)
	{
		char c = m_compressor->decompress(m_ft);
		decompressed[i] = c;
	}

	delete m_compressor;
}

void TestArithmetic::testDinamicCompress(string toCompress)
{
	// Le paso el nombre del archivo donde quiero que guarde lo que comprimio.
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR,m_filecompressed,m_maxbits);

	int i = 0;
	int qchars = toCompress.size();

	for (i = 0;i <= qchars ;i++)
	{
		char c = toCompress[i];
		m_compressor->compress(c,m_ft);
		m_ft.increaseFrequency(c,1);
	}

	m_compressor->compress(EOF_CHAR,m_ft);

	delete m_compressor;
}

void TestArithmetic::testDinamicDecompress(string& decompressed)
{
	m_compressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,m_filecompressed,m_maxbits);
	short c =  UNDEFINED_CHAR;
	int i = 0;

	while (c!=EOF_CHAR)
	{
		c = m_compressor->decompress(m_ft);

		if (c!=EOF_CHAR)
		{
			m_ft.increaseFrequency(c,1);
			decompressed[i] = c;
			i++;
		}
	}

	delete m_compressor;
}


// ------------------Metodos utilitarios--------------------------------

// Devuelve la frecuencia de un simbolo en un string,
// podria llevarse a TableFrequency en un constructor con string.
unsigned long TestArithmetic::getFrequencySymbol(string frase,char c)
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


void TestArithmetic::loadStaticFTable(string toCompress)
{
	int i = 0;
	int qchars = toCompress.size();
	// Guardo las frecuencia de los caracteres.
	for (i = 0;i< qchars;i++)
	{
		char c = toCompress[i];
		unsigned long freq = m_ft.getFrequency(c);

		if (freq==0)
			m_ft.setFrequency(c,getFrequencySymbol(toCompress,c));
	}
}


void TestArithmetic::loadStaticFTable(SequentialFile* file)
{
	bool isNotEOF = false;

	while (isNotEOF)
	{
		char c = file->readChar(isNotEOF);
		if (isNotEOF)
			{
			unsigned long freq = m_ft.getFrequency(c);
			if (freq==0)
				///FALTA IMPLEMENTARLO PERO SE USA EL DINAMICO POR AHORA.
				m_ft.setFrequency(c,getFrequencySymbol("agadsgas",c));
			}
	}
}
