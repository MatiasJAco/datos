/*
 * CharFrequency.h
 *
 *  Created on: 13/06/2010
 *      Author: celeste
 */

#ifndef CHARFREQUENCY_H_
#define CHARFREQUENCY_H_

#include <iostream>
#include <sstream>

/**
 * Clase que guarda el par caracter/frecuencia
 */
class CharFrequency {
public:
	//--------------------CONSTRUCTOR/DESTRUCTOR---------------------------//
	CharFrequency();
	CharFrequency(const CharFrequency&);
	CharFrequency(char, unsigned long);
	virtual ~CharFrequency();

	/**
	 * Convierte al par caracter/Frecuencia en un string para su posterior
	 * guardado en disco
	 * @return string el par caracter/frecuencia serializado
	 */
	std::string toString();

	//-------------------OPERATORS----------------------------------------//
	bool operator < (const CharFrequency &cF) const;

	//-------------------ATRIBUTES----------------------------------------//
private:

	char m_Char;
	unsigned long m_Frequency;
};

#endif /* CHARFREQUENCY_H_ */
