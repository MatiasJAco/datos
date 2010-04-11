/*
 * FixedRegister.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef FIXEDREGISTER_H_
#define FIXEDREGISTER_H_
#include "Register.h"

/**
 * Registros de longitud fija. No se persiste la longitud a disco
 * Siempre hay que indicar la longitud desde afuera
 */
class FixedRegister: public Register
{
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	FixedRegister(const unsigned int size);
	FixedRegister(std::stringstream value,const unsigned int size);
	~FixedRegister();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Convierte a registro un stream pasado por parametro
	 */
	bool setValue(std::stringstream valor);

	/**
	 * Recupera el stream que corresponde a un Registro
	 */
	std::stringstream getValue();

	/**
	 * Obtiene el tamaño del Registro (en bytes)
	 */
	unsigned int getSize();


private:
	unsigned int m_size;
};

#endif /* FIXEDREGISTER_H_ */
