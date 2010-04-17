/*
 * Block.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "Block.h"

Block::Block(unsigned int blocknumber, unsigned int blocksize)
{
	restartCounter();
	m_blockNumber = blocknumber;
	m_blockSize = blocksize;
	m_FirstRegisterOffset=sizeof(m_registerCount)+sizeof(m_usedBytes);

}

Block::~Block()
{
	// TODO Auto-generated destructor stub
}

void Block::restartCounter()
{
	m_actualReg = m_registers.begin();
}



VarRegister Block::getNextRegister()
{
	VarRegister current =*m_actualReg;
	m_actualReg++;

	return current;
}



bool Block::serialize(char *streamChar)
{
	bool retVal=false;

	if(SaveBlockAtributes(streamChar))
	{
		retVal=true;
	}
	return retVal;
}



bool Block::deserialize(char *streamChar)
{
	bool retVal=false;

	if(LoadBlockAtributes(streamChar))
	{
		unsigned int offset=m_FirstRegisterOffset;
		offset++;
		retVal=true;
	}
	return retVal;
}

bool Block::LoadBlockAtributes(char *streamChar)
{
	char *p;

	p = streamChar;

	m_registerCount=ByteConverter::bytesToUInt(p);
	p += sizeof(m_registerCount);

	m_usedBytes = ByteConverter::bytesToUInt(p);

	return true;
}

bool Block::SaveBlockAtributes(char *streamChar)
{
	char *p;

	p = streamChar;

	ByteConverter::uIntToBytes(m_registerCount,p);
	p += sizeof(m_registerCount);

	ByteConverter::uIntToBytes(m_usedBytes,p);

	return true;
}

bool Block::addRegister(const VarRegister & reg)
{
	return true;
}

unsigned int Block::getBlockNumber()
{
	return m_blockNumber;
}


unsigned int Block::getRegisterAmount()
{
	return m_registerCount;
}


