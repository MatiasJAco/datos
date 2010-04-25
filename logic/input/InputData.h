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

#include "../physical/utils/ByteConverter.h"

using namespace std;

/**
 * Abstract class which represents and holds a user Input value.
 */
class InputData {

protected:
	int key;
	stringstream value;

public:
	InputData();
	virtual ~InputData();

	virtual void setKey(int key) = 0;
	virtual void setValue(std::stringstream& value) = 0;
	virtual  int getKey()const = 0;
	virtual string getValue() = 0;

	/**
	 * Devuelve el stream correspondiente al dato.
	 * @param stream stream en donde se almacena.
	 * @return El mismo stream.
	 * El resultado de este metodo sera utilizado en las llamadas a setValue de Register.
	 */
	virtual char* toStream(char* stream) const = 0;

	/**
	 * Convierte el stream pasado por parametro a un InputData
	 * @param stream Stream a convertir.
	 */
	virtual void toData(const char* stream) = 0;

	/**
	 * Tamaño del dato.
	 */
	virtual unsigned int size() = 0;

	/**
	 * Devuelve una instancia de InputData. Necesario, porque esta clase es abstracta
	 * Desde donde es instanciada deberia destruirse el objeto.
	 * @return InputData.
	 */
	virtual InputData* newInstance() = 0;

};

#endif /* INPUTDATA_H_ */
