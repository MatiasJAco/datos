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
	unsigned int missing;
	unsigned int relocateSize=0;
	unsigned int surplus;
	unsigned int sizeA;
	unsigned int sizeB;
	unsigned int minSize;
	VarRegister varR;

	if(blockA!=NULL &&blockB!=NULL)
	{
		sizeA=blockA->getUsedSpace();
		sizeB=blockB->getUsedSpace();
		minSize=blockA->getMinimalLoad();


		if(side == RIGHT_SIDE)
		{
			missing=minSize-sizeA;

			if(missing>0)
			{
				retVal = redistributeLeft(blockA, blockB,  side, true);

				if(retVal)
				{
					retVal = redistributeLeft(blockA, blockB,  side, false);
				}
			}

		}
		else
		{
			missing=minSize-sizeB;

			surplus=sizeA-minSize;
		}

	}
	else
		throw "Se pasaron punteros a NULL";

	return retVal;
}

bool BlockManager::redistributeLeft(Block *blockA, Block *blockB, sideEnum side, bool simulate)
{
	unsigned int missing;
	unsigned int relocateSize=0;
	unsigned int surplus;
	unsigned int sizeA;
	unsigned int sizeB;
	unsigned int minSize;
	VarRegister varR;

	sizeA=blockA->getUsedSpace();
	sizeB=blockB->getUsedSpace();
	minSize=blockA->getMinimalLoad();

	bool retVal=false;
	blockA->jumpEndCounter();

	while(relocateSize<missing)
	{
		varR = blockB->getPreviousRegister(true);
		relocateSize+= varR.getDiskSize();

		if(blockA->isFirstRegister())
		{
			break;
		}
	}
	if((sizeB-relocateSize) >=minSize)
		retVal =true;

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






