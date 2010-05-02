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

bool BlockManager::exchangeBlock(Block *blockA, Block *blockB)
{


	bool retVal=false;

	if(blockA!=NULL &&blockB!=NULL)
	{
		unsigned int blockNumA=blockA->getBlockNumber();
		unsigned int blockNumB=blockB->getBlockNumber();

		blockA->m_blockNumber=blockNumB;
		blockB->m_blockNumber=blockNumA;

	}
	return retVal;
}

bool BlockManager::innerRedistribute(Block *blockA, Block *blockB, sideEnum side, bool simulate)
{
	unsigned int missing;
	unsigned int relocateSize=0;
	unsigned int sizeA;
	unsigned int sizeB;
	unsigned int minSize;
	unsigned int fixedRegisterCount;
	unsigned int i;
	VarRegister varR;

	sizeA=blockA->getUsedSpace();
	sizeB=blockB->getUsedSpace();
	minSize=blockA->getMinimalLoad();

	bool retVal=false;

	if(side ==LEFT_SIDE)
	{

		if(minSize > sizeB)
		{

			missing = minSize -sizeB;

			blockA->jumpLastRegister();

			//Si no estoy simulando procedo tambien sobre el bloque B
			if(!simulate)
				blockB->restartCounter();

			while(relocateSize<missing)
			{
				varR = blockA->getPreviousRegister(true);

				//Ponemos como caso base que llegue al primer registro
				//No se pueden sacar todos los registros a un bloque
				if(blockA->isFirstRegister())
					break;

				relocateSize+= varR.getDiskSize();

			}
			if(!simulate)
			{
				while(!blockA->isLastRegister())
				{
					varR =blockA->peekRegister();
					blockB->addRegister(varR);
					blockA->deleteRegister();
				}
			}

			if((sizeA-relocateSize) >=minSize)
				retVal =true;
		}
	}
	else
	{
		if(minSize > sizeA)
		{
			missing = minSize -sizeA;
			blockB->restartCounter();
			fixedRegisterCount = blockB->getFixedRegisterCount();

			if(!simulate)
				blockA->jumpEndCounter();

			for(i=0; i <fixedRegisterCount;i++)
				blockB->getNextRegister();

			while(relocateSize<missing)
			{
				varR = blockB->peekRegister();

				//Ponemos como caso base que llegue al primer registro
				//No se pueden sacar todos los registros a un bloque
				if(blockB->isLastRegister())
					break;

				relocateSize+= varR.getDiskSize();

				if(!simulate)
				{
					blockA->addRegister(varR);
					blockB->deleteRegister();
				}

			}

			if((sizeB-relocateSize) >=minSize)
				retVal =true;
		}
	}

	blockA->restartCounter();
	blockB->restartCounter();

	return retVal;
}

bool BlockManager::merge(Block *block1, Block *block2,sideEnum side )
{
	bool retVal=false;
	bool isOverflow=false;

	if(block1!=NULL &&block2!=NULL)
	{
		unsigned int combinedSize;

		if(side==LEFT_SIDE)
		{
			combinedSize =block1->getUsedSpace()-block2->getUsedSpace()-block2->getBlockControlDataSize();
			isOverflow = combinedSize > block1->getBlockSize();
		}
		else
		{
			combinedSize =block2->getUsedSpace()-block1->getUsedSpace()-block1->getBlockControlDataSize();
			isOverflow = combinedSize > block2->getBlockSize();
		}

		if(!isOverflow)
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
			retVal=true;
		}
	}
	else
		throw "Se pasaron punteros a NULL";

	if(side==LEFT_SIDE&&retVal)
		retVal = exchangeBlock(block1,block2);

	block1->restartCounter();
	block2->restartCounter();

	return retVal;
}

bool BlockManager::redistributeOverflow(Block *orig, Block *blank, VarRegister & regIns, unsigned int pos)
{
	bool retVal=true;

	unsigned int cumSize=0;
	unsigned int sizeFirst=orig->getMinimalLoad();
	unsigned int i=0;

	if(sizeFirst == 0)
		throw "No se seteo el load factor";

	orig->restartCounter();
	VarRegister varR;
	VarRegister varR2;

	//Obtenemos la cantidad de elementos
	//a dejar en el bloque original para hacer el split
	while(!orig->isLastRegister()&&cumSize<sizeFirst)
	{
		varR =orig->getNextRegister(true);
		if(pos!=i)
		{
			cumSize+= varR.getDiskSize();
		}
		//Si el reg a insertar va en la primera mitad
		//se contabiliza su tama�o en el primer bloque.
		else
			cumSize+= regIns.getDiskSize();
		i++;
	}

	//Lo que quedo despu�s de la mitad se redistribuye a blank
	unsigned int lastReg=blank->getRegisterAmount();


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
		blank->getRegisterN(lastReg+pos-i);
		blank->addRegister(regIns);
	}
	orig->restartCounter();
	blank->restartCounter();

	return retVal;
}

bool BlockManager::split(Block *orig, Block *blank)
{
	bool retVal=false;
	throw "DEPRECATED";

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






