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

class VarRegister {
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	VarRegister();
	VarRegister(std::stringstream value);
	~VarRegister();

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

};

#endif /* VARREGISTER_H_ */
