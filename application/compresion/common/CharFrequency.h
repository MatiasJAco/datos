/*
 * CharFrequency.h
 *
 *  Created on: 13/06/2010
 *      Author: alex
 */

#ifndef CHARFREQUENCY_H_
#define CHARFREQUENCY_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "../../../physical/utils/ByteConverter.h"
#include "../exceptions/CompressionException.h"

/**
 * Clase que guarda el par caracter/frecuencia
 */
class CharFrequency {

	static const unsigned int CHAR_FREQUENCY_SIZE=sizeof(short)+sizeof(unsigned long);

public:
	//--------------------CONSTRUCTOR/DESTRUCTOR---------------------------//
	CharFrequency();
	CharFrequency(const CharFrequency&);
	CharFrequency(short, unsigned long);
	virtual ~CharFrequency();

	static unsigned int getSize();
	/**
	 * Convierte al par caracter/Frecuencia en un string para su posterior
	 * guardado en disco
	 * @return string el par caracter/frecuencia serializado
	 */
	std::string toString();

	void deserialize(std::string &, unsigned int &pos);

	short getChar();

	unsigned long getFrequency();

	void setFrequency(unsigned long freq);

	static std::string shortToString(short val);

	static std::string longToString(long val);

	static long StringToLong(std::string &str, unsigned int &pos);

	static short StringToShort(std::string &str,unsigned int &pos);

	//-------------------OPERATORS----------------------------------------//
	bool operator < (const CharFrequency &cF) const;

	bool operator > (const CharFrequency &cF) const;


	bool operator == (const short &c) const;

	bool operator == (CharFrequency &c) const;

	CharFrequency operator= (const  CharFrequency & cf);

	CharFrequency operator+= (unsigned long const& y);

	//-------------------ATRIBUTES----------------------------------------//
private:

	short m_Char;
	unsigned long m_Frequency;
};

#endif /* CHARFREQUENCY_H_ */
