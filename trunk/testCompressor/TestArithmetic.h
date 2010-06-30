/*
 * TestArithmetic.h
 *
 *  Created on: 26/06/2010
 *      Author: kira
 */

#ifndef TESTARITHMETIC_H_
#define TESTARITHMETIC_H_

#include "../application/compresion/arithmetic/ArithmeticCompressor.h"
#include "../physical/file/SequentialFile.h"
#include <exception>

class TestArithmetic {

public:
	TestArithmetic();
//	TestArithmetic(ArithmeticCompressor::Coder coder,std::string fileName);
	virtual ~TestArithmetic();

	void run();

protected:
	//------------------Para comprimir un archivo pasado por parametro----------------

	// Lee de un archivo de entrada, comprime en forma estatica y guarda el resultado de la compresion en output.
	void testStaticFile(std::string archToCompress);
	// Lee de un archivo de entrada, comprime en forma dinamica y guarda el resultado de la compresion en output.
	void testDinamicFile(std::string archToCompress);


	// ----------------Para comprimir un string pasado por param

	// Comprime uno en forma estatica y el otro en forma
	// dinamica un string pasado por parametro y guarda en output lo comprimido.
	void testStaticString(std::string toCompress,std::string archcomprimido);
	void testDinamicString(std::string toCompress,std::string archcomprimido);

protected:
	//---------------------Para comprimir un archivo de entrada pasado por param.------------

	// Compresion y descompresion dinamica, siendo file el archivo original.
	void testStaticCompress(SequentialFile* archToCompress);
	void testStaticDecompress(SequentialFile* archdescomprimido);

	// Compresion y descompresion dinamica, siendo file el archivo original.
	void testDinamicCompress(SequentialFile* archToCompress);
	void testDinamicDecompress(SequentialFile* archdescomprimido);

	//----------------------Para comprimir un string pasado por param-----------

	// Comprime y descomprime estaticamente strings pasados por parametro.
	void testStaticCompress(std::string str);
	void testStaticDecompress(std::string& str);

	// Comprime y descomprime dinamicamente strings pasados por parametro.
	void testDinamicCompress(std::string str);
	void testDinamicDecompress(std::string& str);



private:// Utilitarios.
	void loadStaticFTable(std::string);
	void loadStaticFTable(SequentialFile* file);
	void loadDinamicFTable();
	unsigned long getFrequencySymbol(std::string frase,char c);

private:
	ArithmeticCompressor* m_compressor;

	FrequencyTable m_ft;

	std::string m_filecompressed;
	int m_maxbits;
};

#endif /* TESTARITHMETIC_H_ */
