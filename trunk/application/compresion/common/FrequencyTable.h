/*
 * FrequencyTable.h
 *
 *  Created on: 13/06/2010
 *      Author: alex
 */

#ifndef FREQUENCYTABLE_H_
#define FREQUENCYTABLE_H_

#include <list>
#include "CharFrequency.h"

#define EOF_CHAR 256
#define ESC_CHAR 257
#define UNDEFINED_CHAR 258

/**
 * Clase encargada de manejar la tabla de frecuencias
 * Se encarga de serializar y deserializar las frecuencias a un string
 * para su guardado en disco.
 * En ella se almacenan los caracteres con su frecuencia, y luego se los convierte en un string
 * para ser guardado en disco
 * Los caracteres se guardan como short para poder almacenar el EOF y el ESC
 * @see InputData, CharFrequency
 *
 */
class FrequencyTable {

typedef std::list<CharFrequency> CharFrequencyList;
typedef CharFrequencyList::iterator CharFrequencyListIterator;


public:
	//-----------------------CONSTRUCTOR/DESTRUCTOR---------------------------//
	FrequencyTable();

	FrequencyTable(const FrequencyTable &ft );

	virtual ~FrequencyTable();

	/**
	 * Devuelve la frecuencia del caracter pasado por parametro.
	 * Si el caracter no existe se devuelve 0
	 * @param c el caracter cuya frecuencia se pide
	 * @return unsigned long la frecuencia del caracter pasdo por parametro.
	 */
	unsigned long getFrequency(short c);

	/**
	 * Obtiene el caracter que corresponde a una determinada frecuencia acumulada.
	 * @param freq la frecuencia acumulada que se esta buscando
	 * @return short el caracter UNDEFINED_CHAR en caso de no encontrarlo
	 */
	short getChar(unsigned long freq);

	/**
	 * Devuelve la suma de todas las frecuencias
	 * @return unsigned long la suma de todas las frecuencias
	 */
	unsigned long getFrequencyTotal();


	/**
	 * Obtiene la suma de los caracteres anteriores hasta el actual
	 *  Si el caracter no existe se devuelve 0
	 * @param c caracter a buscar
	 * @return unsigned long suma de todos los caracteres hasta el actual
	 */
	unsigned long getCumFrequency(short c);

	/**
	 * Permite setear la frecuencia para un caracter
	 * Si ya existe se modifica la frecuencia existente, si no existe se
	 * agrega a la tabla.
	 * @param c caracter
	 * @param freq la frecuencia del caracter
	 */
	void setFrequency(short c, unsigned long freq);

	/**
	 * Setea la frecuencia para un caracter especificado.
	 * Si ya existe se modifica la frecuencia existente, si no existe se
	 * agrega a la tabla.
	 * @param cf caracter con su frecuencia
	 */
	void setFrequency(CharFrequency cf);

	/**
	 * Incrementa la frecuencia para el caracter c.
	 * Si no encuentra el caracter lo agrega a la tabla.
	 * @param c caracter para el cual se incrementa la frecuencia
	 * @param ammount cantidad en la cual se incrementa la frecuencia (por default es 1)
	 */
	void increaseFrequency(short c, unsigned long ammount);

	//------------------------SERIALIZE/DESERIALIZE---------------------------//
	/**
	 * Carga una tabla de frecuencias a partir de un string serializado
	 * con todos los datos de la tabla de frecuencias.
	 * Si ya existian datos en la tabla de frecuencias se eliminan.
	 * @param serialized
	 */
	void deserialize(std::string serialized);

	/**
	 * Convierte la tabla a un string para su almacenamiento en disco.
	 * La tabla se guarda ordenada por el valor ascii del caracter.
	 * @return string string con el contenido de la tabla serializado.
	 */
	std::string toString();


	std::string toPrintableString();

	/**
	 * Excluye de una tabla los caracteres de otra tabla.
	 * El ESC_CHAR no se borra de la tabla resultante, aunque estuviera en la tabla a restar.
	 * @param ft tabla con caracteres a restar
	 * @return FrequencyTable tabla resultante de restar los caracteres contenidos en ft
	 */
	FrequencyTable excludeFromTable(FrequencyTable &ft);

	FrequencyTable operator= (FrequencyTable ft);


	//--------------------------ATTRIBUTES------------------------------------//
private:
	CharFrequencyList m_Frequencies;

	unsigned long m_FrequencyTotal;

	bool m_isSorted;
};

#endif /* FREQUENCYTABLE_H_ */
