/*
 * BlockManager.h
 *
 *  Created on: 25/04/2010
 *      Author: alex
 */

#ifndef BLOCKMANAGER_H_
#define BLOCKMANAGER_H_
#include "Block.h"
#include <iostream>


typedef enum {LEFT_SIDE, RIGHT_SIDE} sideEnum;
/**
 * Clase encargada de hacer las operacione de redistribucion en los nodos
 */
class BlockManager
{
public:

	/**
	 * Se encarga de fusionar 2 bloques
	 * @param block1 bloque en el que van a quedar los registros
	 * @param block2 bloque que se va a vaciar.
	 * @return bool true en caso de OK false en caso contrario
	 * @throw exception en caso de pasarle puntero a NULL
	 */

	static bool merge(Block *block1, Block *block2);

	/**
	 * Se encarga de balancear la carga de 2 bloques
	 * @param block1
	 * @param block2
	 * @return bool true en caso de OK false en caso contrario
	 */

	static bool balanceLoad(Block *block1, Block *block2, sideEnum side=RIGHT_SIDE);

	/**
	 * Se encarga de redistrbuir la carga de 2 bloques en caso de overflow...
	 * Ademas inserta en una posicion dada el elemento que provoco el overflow.
	 * Conserva los registros que se encuentran en blank, es decir coloca los elementos
	 * provenientes del overflow del bloque original al final del bloque blank
	 * @param orig bloque que esta en overflow
	 * @param blank bloque en el cual se van a acomodar los registros sobrantes del otro bloque
	 * @param reg registro que produjo el overflow
	 * @param pos posicion que va a ocupar el registro que provoco el overflow
	 * @return bool true en caso de OK false en caso contrario
	 * @throws exception en caso de que pos supere la cantidad de elementos total.
	 */
	static bool redistributeOverflow(Block *orig, Block *blank, VarRegister &reg, unsigned int pos);




	//--------------------------------deprecated---------------------------------------//
	/**
	 * @deprecated
	 */
	static bool split(Block *orig, Block *blank);

	/**
	 * @deprecated
	 */
	static bool mergeBlocks(Block *block1, Block *block2,  VarRegister &reg, unsigned int pos);

	/**
	 * @deprecated
	 */
	static bool redistributeUnderflow(Block *block1, Block *block2, VarRegister &reg, unsigned int pos);

private:
	static bool redistributeLeft(Block *blockA, Block *blockB, sideEnum side, bool simulate);

};

#endif /* BLOCKMANAGER_H_ */
