/*
 * Block.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "Block.h"

using namespace std;

Block::Block(unsigned int blocknumber, unsigned int blocksize)
{
	m_FirstRegisterOffset= sizeof(m_registerCount)+sizeof(m_usedBytes);

	if(blocksize < m_FirstRegisterOffset+1)
		throw "El tamaño del bloque debe poder por lo menos comprender los datos de control";

	restartCounter();
	m_blockNumber = blocknumber;
	m_blockSize = blocksize;
	m_usedBytes=m_FirstRegisterOffset;
	m_registerCount=0;


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
	VarRegister current(*m_actualReg);
	m_actualReg++;

	return current;
}



bool Block::serialize(char *streamChar)
{
	bool retVal=false;
	char *p=streamChar;
	unsigned int regSize;
	RegisterListIt it;

	if(SaveBlockAtributes(p))
	{
		p+=m_FirstRegisterOffset;

		for(it=m_registers.begin(); it !=m_registers.end(); it++, p+=regSize)
		{
			it->serialize(p);
			regSize=it->getDiskSize();
		}

		retVal=true;
	}
	return retVal;
}



bool Block::deserialize(char *streamChar)
{
	bool retVal=false;

	if(LoadBlockAtributes(streamChar))
	{
		char *p;
		unsigned int regSize;
		m_registers.clear();
		VarRegister temp;
		char * beginRegisters=streamChar+m_FirstRegisterOffset;
		char * endStream=streamChar+m_usedBytes;

		for(p=beginRegisters; p < endStream; p+=regSize)
		{
			temp.deserialize(p);
			regSize = temp.getDiskSize();
			m_registers.push_back(temp);
		}

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

void Block::printRegisters()
{
	RegisterListIt it;

	cout << "El nodo contiene:"<<endl;
	for (it=m_registers.begin(); it!=m_registers.end(); it++)
	{
	    cout << "Valor:" ;
	    it->printRegister();
	    cout << " Size:"<<it->getSize()<<","<<endl;

	}


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
	bool retVal=false;

	if(m_usedBytes+reg.getDiskSize()<=m_blockSize)
	{
		m_registers.insert(m_actualReg, reg);
		m_registerCount++;
		m_usedBytes+=reg.getDiskSize();
		retVal=true;
	}
	return retVal;
}

unsigned int Block::getBlockNumber()
{
	return m_blockNumber;
}


unsigned int Block::getRegisterAmount()
{
	return m_registerCount;
}


