/*
 * BlockManager.cpp
 *
 *  Created on: 25/04/2010
 *      Author: alex
 */

#include "BlockManager.h"

bool BlockManager::balanceLoad(Block *blockA, Block *blockB, sideEnum side)
{
	bool retVal=false;

	if(blockA!=NULL &&blockB!=NULL)
	{
		//Simulo la operacion primero para ver si hay suficientes elementos
		retVal = innerRedistribute(blockA, blockB, side, true);

		if(retVal)
			retVal = innerRedistribute(blockA, blockB, side, false);
	}
	else
		throw "Se pasaron punteros a NULL";

	return retVal;
}

bool BlockManager::innerRedistribute(Block *blockA, Block *blockB, sideEnum side, bool simulate)
{
	unsigned int missing;
	unsigned int relocateSize=0;
	unsigned int sizeA;
	unsigned int sizeB;
	unsigned int minSize;
	bool breakLoop=false;
	VarRegister varR;

	sizeA=blockA->getUsedSpace();
	sizeB=blockB->getUsedSpace();
	minSize=blockA->getMinimalLoad();

	bool retVal=false;

	if(side ==LEFT_SIDE)
	{
		blockA->jumpEndCounter();

		if(!simulate)
			blockB->restartCounter();

		while(relocateSize<missing)
		{
			varR = blockA->getPreviousRegister(true);
			relocateSize+= varR.getDiskSize();

			if(blockA->isFirstRegister())
				breakLoop = true;

			if(!simulate)
			{
				blockB->addRegister(varR);
				blockA->deleteRegister();
			}
			if(breakLoop)
				break;
		}

		if((sizeB-relocateSize) >=minSize)
			retVal =true;
	}
	else
	{
		blockA->jumpEndCounter();

			if(!simulate)
				blockB->restartCounter();

			while(relocateSize<missing)
			{
				varR = blockB->getNextRegister(true);
				relocateSize+= varR.getDiskSize();

				if(blockB->isLastRegister())
					breakLoop = true;

				if(!simulate)
				{
					blockA->addRegister(varR);
					blockB->deleteRegister();
				}
				if(breakLoop)
					break;
			}

			if((sizeA-relocateSize) >=minSize)
				retVal =true;
	}

	return retVal;
}

bool BlockManager::merge(Block *block1, Block *block2)
{
	bool retVal=false;

	if(block1!=NULL &&block2!=NULL)
	{
		unsigned int minSize=block1->getMinimalLoad();

		if(block1->getUsedSpace()<= minSize && block2->getUsedSpace()<= minSize)
		{
			VarRegister varR;
			unsigned int lastReg=block1->getRegisterAmount()-1;

			block1->getRegisterN(lastReg);

			block2->restartCounter();

			while(!block2->isLastRegister())
			{
				varR = block2->getNextRegister(true);
				block1->addRegister(varR);
			}

			block2->clear();
		}
	}
	else
		throw "Se pasaron punteros a NULL";

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
		unsigned int lastReg=blank->getRegisterAmount()-1;

		blank->getRegisterN(lastReg+pos-i);
		blank->addRegister(regIns);
	}

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

bool BlockManager::mergeBlocks(Block *block1, Block *block2, VarRegister & reg, unsigned int pos)
{
	bool retVal=false;

	throw "DEPRECATED";
	return retVal;
}






