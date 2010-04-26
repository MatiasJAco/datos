/*
 * BlockManager.cpp
 *
 *  Created on: 25/04/2010
 *      Author: alex
 */

#include "BlockManager.h"

bool BlockManager::balanceLoad(Block *block1, Block *block2)
{
	bool retVal=true;

	return retVal;
}



bool BlockManager::merge(Block *block1, Block *block2)
{
	bool retVal=true;

	return retVal;
}



bool BlockManager::split(Block *orig, Block *blank)
{
	bool retVal=true;

	blank->clear();

	unsigned int cumSize;
	unsigned int sizeFirst=orig->getMinimalLoad();

	orig->restartCounter();
	VarRegister varR;
	VarRegister varR2;

	for(cumSize=0;cumSize<sizeFirst&& !orig->isLastRegister(); cumSize+= varR.getDiskSize())
	{
		varR =orig->getNextRegister(true);
	}

	while(!orig->isLastRegister())
	{
		varR =orig->getNextRegister(false);
		orig->deleteRegister();
		blank->addRegister(varR);
	}

	return retVal;

}


