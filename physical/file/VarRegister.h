/*
 * VarRegister.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef VARREGISTER_H_
#define VARREGISTER_H_
#include "Register.h"
#include <sstream>
#include <cstring>
#include <iostream>


class VarRegister: public Register
{
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	VarRegister();
	VarRegister(std::stringstream value);
	~VarRegister();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Convierte a registro un stream pasado por parametro
	 */
	bool setValue(char * valor,unsigned int size);

	bool setValue(char * valor);

	/**
	 * Recupera el stream que corresponde a un Registro
	*/
	char * getValue();

	/**
	 * Obtiene el tamaño del Registro (en bytes)
	 */
	unsigned int getSize();

};

#endif /* VARREGISTER_H_ */
