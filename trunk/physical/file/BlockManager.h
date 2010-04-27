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

/**
 * Clase encargada de hacer las operacione de redistribucion en los nodos
 */
class BlockManager
{
public:
	/**
	 * @deprecated
	 */
	static bool split(Block *orig, Block *blank);

	/**
	 * @deprecated
	 */
	static bool merge(Block *block1, Block *block2);

	/**
	 * @deprecated
	 */
	static bool balanceLoad(Block *block1, Block *block2);


	//--------------------------NUEVOS METODOS-------------------------------//
	static bool redistributeOverflow(Block *orig, Block *blank, VarRegister &reg, unsigned int pos);

	static bool mergeBlocks(Block *block1, Block *block2,  VarRegister &reg, unsigned int pos);

	static bool redistributeUnderflow(Block *block1, Block *block2, VarRegister &reg, unsigned int pos);
};

#endif /* BLOCKMANAGER_H_ */
