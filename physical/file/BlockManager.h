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


class BlockManager
{
public:
	static bool split(Block *orig, Block *blank);

	static bool merge(Block *block1, Block *block2);

	static bool balanceLoad(Block *block1, Block *block2);
};

#endif /* BLOCKMANAGER_H_ */
