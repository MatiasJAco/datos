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
 * Su funcion es abstraer a la logica de temas del tamaño propio de los registros.
 */
class BlockManager
{
public:

	/**
	 * Se encarga de fusionar 2 bloques
	 * El bloque que desaparece es el que provoco el underflow
	 * @param block1 bloque en el que van a quedar los registros
	 * @param block2 bloque que se va a vaciar.
	 * @param side bloque que va a desaparacer
	 * @return bool true en caso de OK false en caso contrario
	 * @throw exception en caso de pasarle puntero a NULL
	 */

	static bool merge(Block *block1, Block *block2, sideEnum side=RIGHT_SIDE);

	/**
	 * Se encarga de balancear la carga de 2 bloques, hacia izquierda o derecha
	 * dependiendo del parametro side. Mantiene el orden de los elementos
	 * Para esto se debe pasar en el bloque1 los elementos menores, en el 2 los siguientes, y la direccion
	 * del balanceo
	 * @param block1 primer bloque (elementos menores)
	 * @param block2 segundo bloque (elementos mayores)
	 * @param side direccion en la cual se realiza el balanceo
	 * @return bool true en caso de OK false en caso de no tener espacio en el bloque donante
	 * para realizar la operacion
	 * @throw exception en caso de pasarle puntero a NULL
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

	/**
	 * Intercambia el contenido del Bloque A por el del bloque B
	 * Si A tenia 123 y B 456
	 * B pasa a tener 456 y A pasa a tener 123
	 * @param blockA bloque a intercambiar
	 * @param blockB bloque a intercambiar
	 * @return bool true en caso de OK false en caso contrario
	 */
	static bool exchangeBlock(Block* blockA,Block*blockB);


	//--------------------------------deprecated---------------------------------------//
	/**
	 * TODO eliminar
	 * @deprecated
	 */
	static bool split(Block *orig, Block *blank);

	/**
	 * TODO eliminar
	 * @deprecated
	 */
	static bool mergeBlocks(Block *block1, Block *block2,  VarRegister &reg, unsigned int pos);

	/**
	 * TODO eliminar
	 * @deprecated
	 */
	static bool redistributeUnderflow(Block *block1, Block *block2, VarRegister &reg, unsigned int pos);

private:
	/**
	 * Para uso interno, no llamar desde afuera
	 */
	static bool innerRedistribute(Block *blockA, Block *blockB, sideEnum side, bool simulate);

};

#endif /* BLOCKMANAGER_H_ */
