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
	VarRegister(const VarRegister &orig);
	VarRegister(char *value, unsigned int size);
	~VarRegister();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Convierte a registro un stream pasado por parametro
	 */
	bool setValue(char * valor,unsigned int size);

	/**
	 * Recupera el stream que corresponde a un Registro
	*/
	char * getValue();

	/**
	 * Obtiene el tamaño del Registro (en bytes)
	 */
	unsigned int getSize() const;

	/**
	 * Obtiene el tamaño del Registro (en bytes)
	 */
	unsigned int getDiskSize() const;

	/**
	 * Imprime m_value en hexadecimal, su principal uso es para debug
	 */
	void printRegister();

	//--------------------SERIALIZE/DESERIALIZE-------------------//
	/**
	 * Convierte a un stream el contenido del registro
	 * @param stream stream de caracteres en el cual se coloca el contenido del registro.
	 * tiene que tener memoria asignada desde el ambito del cual se la llama
	 * @return true en caso de ok, false en caso contrario
	 */
	bool serialize(char * stream);

	/**
	 * Carga el registro desde un stream
	 * @param stream stream de caracteres del cual se carga el registro
	 * @return true en caso de ok, false en caso contrario
	 */
	bool deserialize(char * stream);

	//----------------------------OPERATORS------------------------//
	/**
	 * Sobrecarga del operador =
	 */
	VarRegister & operator=(const VarRegister &orig);
};

#endif /* VARREGISTER_H_ */
