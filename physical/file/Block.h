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
#include "../utils/ByteConverter.h"
#include <sstream>
#include <list>

/**
 * Block
 */
class Block {
public:
	//------------------------TYPEDEFS----------------------------------//
	typedef std::list <VarRegister> RegisterList;
	typedef RegisterList::iterator RegisterListIt;


	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	Block(unsigned int blocknumber, unsigned int blockSize);
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
	unsigned int getRegisterAmount();

	unsigned int getBlockNumber();

	bool serialize(char *streamChar);

	bool deserialize(char *streamChar);

private:

	bool LoadBlockAtributes(char *streamChar);

	bool SaveBlockAtributes(char *streamChar);

private:

	unsigned int m_blockNumber;

	unsigned int m_blockSize;

	unsigned int m_FirstRegisterOffset;

	/**
	 * Espacio libre restante
	 */
	unsigned int m_usedBytes;

	/**
	 * Cantidad de registros en el nodo.
	 */
	unsigned int m_registerCount;

	/**
	 * Posicion actual dentro del nodo. Se usa para ir recorriendo
	 * secuencialmente
	 */
	RegisterListIt m_actualReg;

	/**
	 * Lista que contiene todos los Registers del bloque.
	 */
	RegisterList m_registers;


};

#endif /* BLOCK_H_ */
