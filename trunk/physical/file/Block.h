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
	/**
	 * Definicion del tipo de datos que almacena los registros
	 */
	typedef std::list <VarRegister> RegisterList;

	/**
	 * Definicion del iterador de la lista
	 */
	typedef RegisterList::iterator RegisterListIt;


	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	/**
	 * Constructor
	 * @param blocknumber numero del bloque a crear
	 * @param blockSize tama�o del bloque
	 */
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

	/**
	 * Obtiene el numero del bloque actual
	 * @return numero de bloque
	 */
	unsigned int getBlockNumber();

	/**
	 * Muestra por pantalla el contenido del bloque. Se usa para debug
	 */
	void printRegisters();

	//--------------------SERIALIZE/DESERIALIZE-------------------//
	/**
	 * Convierte a un stream el contenido del registro
	 * @param streamChar stream de caracteres en el cual se coloca el contenido del bloque.
	 * tiene que tener memoria asignada desde el ambito del cual se la llama
	 * @return true en caso de ok, false en caso contrario
	 */
	bool serialize(char *streamChar);

	/**
	 * Carga el bloque desde un stream
	 * @param streamChar stream de caracteres del cual se carga el registro
	 * @return true en caso de ok, false en caso contrario
	 */
	bool deserialize(char *streamChar);

	/**
	 * Sirve para obtener la cantidad de bytes libres que quedan en el bloque.
	 * @return Devuelve la cantidad de bytes libres del bloque.
	 */
	unsigned int getRemainingSpace();

private:

	bool LoadBlockAtributes(char *streamChar);

	bool SaveBlockAtributes(char *streamChar);

private:

	unsigned int m_blockNumber;

	unsigned int m_blockSize;

	unsigned int m_FirstRegisterOffset;

	/**
	 * Espacio usado por el bloque
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
