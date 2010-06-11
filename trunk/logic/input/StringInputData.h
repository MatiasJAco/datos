/*
 * StringInputData.h
 *
 *  Created on: Apr 13, 2010
 *      Author: adrian
 */

#ifndef STRINGINPUTDATA_H_
#define STRINGINPUTDATA_H_

#include "InputData.h"

/**
 * Esta clase representa un dato ingresado por el usuario, siendo el valor del dato una cadena de caracteres.
 */
class StringInputData: public InputData {

public:
	StringInputData();
	StringInputData(std::string key,std::string value);

	virtual ~StringInputData();

	/**
	 * Este metodo define la clave del dato ingresado por el usuario.
	 * @param key Es la clave del dato.
	 */
	void setKey(std::string key);

	/**
	 * Este metodo coloca el valor del dato ingresado por el usuario.
	 * @param value Es el valor del dato.
	 */
	void setValue(std::string value);

	/**
	 * Devuelve la clave del dato ingresado por el usuario.
	 * @return Devuelve la clave del dato.
	 */
	std::string getKey()const;

	/**
	 * Devuelve el valor del dato ingresado por el usuario.
	 * @return Devuelve el valor del dato.
	 */
	string getValue()const;

	/**
	 * Convierte a stream el dato.
	 * @param stream Es el stream al que se convertira el dato.
	 * @return Devuelve el stream pasado por parametro, pero lleno de bytes que representan al dato.
	 */
	char* toStream(char* stream) const;

	/**
	 * Convierte un stream a dato.
	 * @param stream Es la tira de bytes que representa al dato.
	 */
	void toData(const char* stream);

	/**
	 * Devuelve el tamaño del dato.
	 * @return Devuelve el tamaño de este dato.
	 */
	unsigned int size() const;

	/**
	 * Devuelve una nueva instancia de InputData.
	 * @return Devuelve una nueva instancia del dato.
	 */
	InputData* newInstance() const;

	/**
	 * Devuelve una cadena de caracteres que representa una descripcion del dato ingresado por el usuario.
	 * @return Devuelve la cadena de caracteres que representa al dato.
	 */
	std::string toString()const;
};

#endif /* STRINGINPUTDATA_H_ */
