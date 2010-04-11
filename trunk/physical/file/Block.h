/*
 * Block.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include "Register.h"
#include "FixedRegister.h"//TODO ver si usar solo la clase abstracta
#include "VarRegister.h"
#include <sstream>

/**
 * Block
 */
class Block {
public:
	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	Block();
	~Block();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Inserta un registro en la posicion actual.
	 * @see Register
	 */
	bool addRegister(const Register &reg);

	/**
	 * Obtiene el proximo Register, siendo este de longitud fija
	 * y definida mediante el parametro que se le pasa. Es necesario pasar
	 * el tamaño del Registro ya que el tamaño no se persiste en disco, y es
	 * unicamente conocido por la capa logica.
	 * La instancia de Register se crea internamente.
	 * @see Register
	 */
	FixedRegister getFixedRegister(const unsigned int size);

	/**
	 * Obtiene el proximo Register, siendo este de longitud variable.
	 * La informacion de la longitud del Register no es necesario pasarla,
	 * ya que se encuentra persistida en disco.
	 * TODO ver si se deja que devuelva un VarRegister, o ponemos un Register *
	 */
	VarRegister getVarRegister();

	/**
	 * Obtiene la cantidad de registros.
	 */
	unsigned int getRegisterAmmount();

private:

	/**
	 * Espacio libre restante
	 */
	unsigned int m_freeBytes;

	/**
	 * Cantidad de registros en el nodo.
	 */
	unsigned int m_registerCount;

	/**
	 * Posicion actual dentro del nodo. Se usa para ir recorriendo
	 * secuencialmente
	 */
	unsigned int m_count;

	/**
	 * Contenido del bloque
	 * TODO DISCUTIR...
	 */
	std::stringstream m_value;

};

#endif /* BLOCK_H_ */
