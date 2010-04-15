/*
 * Block.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include "Register.h"
#include "VarRegister.h"
#include <sstream>
#include <list>

/**
 * Block
 */
class Block {
public:
	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	Block(unsigned int blocknumber);
	~Block();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Inserta un registro en la posicion actual.
	 * @see Register
	 */
	bool addRegister(const VarRegister &reg);

	/**
	 * Obtiene el proximo Register, siendo este de longitud variable.
	 * La informacion de la longitud del Register no es necesario pasarla,
	 * ya que se encuentra persistida en disco.
	 *
	 */
	VarRegister getNextRegister();

	/**
	 * Devuelve el contador al principio del bloque
	 */
	void restartCounter();

	//TODO poner un delete registro, y un modificar

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
	 * Lista que contiene todos los Registers del bloque.
	 */
	std::list <VarRegister> m_registers;

};

#endif /* BLOCK_H_ */
