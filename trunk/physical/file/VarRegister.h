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

/**
 * Implementa registros de longitud variable
 * Para eso se guarda la long de los registros a disco
 */
class VarRegister: public Register
{
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	VarRegister();

	/**
	 * Constructor de copia
	 * @param orig valor a copiar
	 */
	VarRegister(const VarRegister &orig);

	/**
	 * Constructor
	 * @param value stream que contiene el valor del registro
	 * @param size tamaño del registro
	 */
	VarRegister(char *value, unsigned int size);
	~VarRegister();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Convierte a registro un stream pasado por parametro.
	 * Es necesario pasar el tamaño ya que el registro es de tamaño variable.
	 * @param valor stream con el valor a convertir en registro
	 * @param size tamaño del stream.
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool setValue(char * valor,unsigned int size);


	/**
	 * Convierte a registro un int pasado por parametro
	 * @param value valor a setear
	 * @return bool true en caso de ok, false en caso contrario
	 */
	bool setValue(int value);

	/**
	 * Convierte a registro un string pasado por parametro
	 * @param value valor a setear
	 * @return bool true en caso de ok, false en caso contrario
	 */
	bool setValue(std::string &value);

	/**
	 * Recupera el stream que corresponde a un Registro
	 * IMPORTANTE: se asigna memoria mediante un new dentro de este
	 * metodo, es importante guardar un puntero al stream para liberar
	 * la memoria desde afuera despues
	 * @return char * stream que representa el registro.
	*/
	char * getValue();

	/**
	 * Obtiene el tamaÃ±o del Registro sin contar los datos de control (en bytes)
	 * @return unsigned int el tamano del contenido del registro
	 */
	unsigned int getSize() const;

	/**
	 * Obtiene el tamaÃ±o del Registro contabilizando los datos de control (en bytes)
	 * @return unsigned int el tamano del registro
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
	 * IMPORTANTE: se asigna memoria mediante un new dentro de este
	 * metodo, es importante guardar un puntero al stream para liberar
	 * la memoria desde afuera despues
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
