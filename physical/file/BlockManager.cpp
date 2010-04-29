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


	throw "DEPRECATED";
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

bool BlockManager::redistributeUnderflow(Block *block1, Block *block2, VarRegister & reg, unsigned int pos)
{
	bool retVal=false;

	throw "DEPRECATED";
	return retVal;
}



bool BlockManager::redistributeOverflow(Block *orig, Block *blank, VarRegister & regIns, unsigned int pos)
{
	bool retVal=true;

	unsigned int cumSize=0;
	unsigned int sizeFirst=orig->getMinimalLoad();
	unsigned int i=0;

	orig->restartCounter();
	VarRegister varR;
	VarRegister varR2;


	while(!orig->isLastRegister()&&cumSize<sizeFirst)
	{
		varR =orig->getNextRegister(true);
		if(pos!=i)
		{
			cumSize+= varR.getDiskSize();
		}
		else
			cumSize+= regIns.getDiskSize();
		i++;
	}

	while(!orig->isLastRegister())
	{
		varR =orig->getNextRegister(false);
		orig->deleteRegister();
		blank->addRegister(varR);
	}


	if(pos<i)
	{
		orig->getRegisterN(pos);
		orig->addRegister(regIns);
	}
	else
	{
		blank->getRegisterN(pos-i);
		blank->addRegister(regIns);
	}

	return retVal;
}



bool BlockManager::mergeBlocks(Block *block1, Block *block2, VarRegister & reg, unsigned int pos)
{
	bool retVal=false;

	throw "DEPRECATED";
	return retVal;
}






