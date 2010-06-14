/*
 * FrequencyTable.h
 *
 *  Created on: 13/06/2010
 *      Author: celeste
 */

#ifndef FREQUENCYTABLE_H_
#define FREQUENCYTABLE_H_

#include <list>
#include "CharFrequency.h"


/**
 * Clase encargada de manejar la tabla de frecuencias
 * Se encarga de serializar y deserializar las frecuencias a un string
 * para su guardado en disco.
 * En ella se almacenan los caracteres con su frecuencia, y luego se los convierte en un string
 * para ser guardado en disco
 * @see InputData, CharFrequency
 *
 */
class FrequencyTable {

typedef std::list<CharFrequency> CharFrequencyList;
typedef CharFrequencyList::iterator CharFrequencyListIterator;


public:
	//-----------------------CONSTRUCTOR/DESTRUCTOR---------------------------//
	FrequencyTable();

	virtual ~FrequencyTable();

	/**
	 * Devuelve la frecuencia del caracter pasado por parametro.
	 * @param el caracter cuya frecuencia se pide
	 * @return unsigned long la frecuencia del caracter pasdo por parametro.
	 */
	unsigned long getFrequency(char c);

	/**
	 * Devuelve la suma de todas las frecuencias
	 * @return unsigned long la suma de todas las frecuencias
	 */
	unsigned long getFrequencyTotal();

	/**
	 *
	 */
	unsigned long getCumFrequency(char c);

	/**
	 * Permite setear la frecuencia para un caracter
	 * @param c caracter
	 * @param freq la frecuencia del caracter
	 */
	void setFrequency(char c, unsigned long freq);

	/**
	 *
	 */
	void setFrequency(CharFrequency cf);

	//------------------------SERIALIZE/DESERIALIZE---------------------------//
	/**
	 *
	 */
	void deserialize(std::string serialized);

	/**
	 *
	 */
	std::string toString();

	//--------------------------ATTRIBUTES------------------------------------//
private:
	CharFrequencyList m_Frequencies;

	unsigned long m_FrequencyTotal;
};

#endif /* FREQUENCYTABLE_H_ */
