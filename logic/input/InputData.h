/*
 * InputData.h
 *
 *  Created on: Apr 13, 2010
 *      Author: adrian
 */

#ifndef INPUTDATA_H_
#define INPUTDATA_H_

#include <iostream>
#include <sstream>

#include "../../physical/utils/ByteConverter.h"

using namespace std;

/**
 * Clase abstracta que permite modelar un dato ingresado por el usuario.
 */
class InputData {

protected:
	string key;
	string value;

public:
	InputData();
	virtual ~InputData();

	virtual void setKey(string key) = 0;
	virtual void setValue(std::string value) = 0;
	virtual  string getKey()const = 0;
	virtual string getValue()const = 0;

	/**
	 * Devuelve el stream correspondiente al dato.
	 * @param stream stream en donde se almacena.
	 * @return El mismo stream. El resultado de este metodo sera utilizado en las llamadas a setValue de Register.
	 */
	virtual char* toStream(char* stream) const = 0;

	/**
	 * Convierte el stream pasado por parametro a un InputData
	 * @param stream Stream a convertir.
	 */
	virtual void toData(const char* stream) = 0;

	/**
	 * Tama�o del dato.
	 */
	virtual unsigned int size() const = 0;

	/**
	 * Devuelve una instancia de InputData. Necesario, porque esta clase es abstracta
	 * Desde donde es instanciada deberia destruirse el objeto.
	 * @return InputData.
	 */
	virtual InputData* newInstance() const = 0;

	/**
	 * Devuelve una cadena de caracteres que representa una descripcion del dato ingresado por el usuario.
	 * @return Devuelve la cadena de caracteres que representa al dato.
	 */
	virtual std::string toString()const = 0;

};

#endif /* INPUTDATA_H_ */
