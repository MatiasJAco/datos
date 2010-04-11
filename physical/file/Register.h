/*
 * Register.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef REGISTER_H_
#define REGISTER_H_
#include <sstream>

/**
 * Clase abstracta
 */
class Register
{
public:
	Register();
	virtual ~Register();

	/**
	 * Convierte a registro un stream pasado por parametro
	 */
	virtual bool setValue(std::stringstream valor)=0;

	/**
	 * Recupera el stream que corresponde a un Registro
	 */
	virtual std::stringstream getValue()=0;

	/**
	 * Obtiene el tamaño del Registro (en bytes)
	 */
	virtual unsigned int getSize()=0;



private:
	std::stringstream m_value;
};

#endif /* REGISTER_H_ */
