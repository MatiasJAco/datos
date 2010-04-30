/*
 * Block.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "Block.h"

using namespace std;

Block::Block(unsigned int blocknumber, unsigned int blocksize, float loadFactor)
{
	m_FirstRegisterOffset= sizeof(m_registerCount)+sizeof(m_usedBytes);

	if(blocksize < m_FirstRegisterOffset+1)
		throw "El tama�o del bloque debe poder por lo menos comprender los datos de control";

	restartCounter();
	m_blockNumber = blocknumber;
	m_blockSize = blocksize;
	m_usedBytes=m_FirstRegisterOffset;
	m_registerCount=0;
	m_LoadFactor=loadFactor;

}

Block::~Block()
{
}

void Block::restartCounter()
{

	if(m_registers.size()>0)
	{
		m_posActual=0;
		m_actualReg = m_registers.begin();
	}
	else
	{
		m_posActual=-1;
		m_actualReg = m_registers.end();
	}
}

void Block::jumpEndCounter()
{
	m_actualReg = m_registers.end();
	m_posActual = m_registers.size()-1;
}

VarRegister Block::getNextRegister(bool foward)
{
	RegisterListIt it;
	it=m_actualReg;

	VarRegister current;
	if(m_registers.size()>0)
	{
		if(it!=m_registers.end())
		{
			current=*it;
			it++;

			if(foward)
			{
				m_posActual++;
				m_actualReg =it;
			}
		}
	}

	return current;
}

VarRegister Block::peekRegister()
{
	VarRegister current;

	current = getNextRegister(false);

	return current;
}

bool Block::isLastRegister()
{
	bool retVal=true;
	RegisterListIt it=m_registers.end();

	if(m_registers.size() > 0)
		retVal = (m_actualReg ==it);

	return retVal;

}

bool Block::isFirstRegister()
{
	bool retVal=true;

	if(m_registers.size() > 0)
		retVal = m_actualReg ==m_registers.begin();

	return retVal;

}


bool Block::hasNextRegister()
{
	if (m_registers.size() == 0)
		return false;
	else if(m_registers.size() == 1)
		if (m_actualReg == m_registers.end())
			return false;
		else
			return true;
	else
		return m_actualReg != m_registers.end();
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

		//Relleno con ceros el resto del stream para no meter basura en el archivo
		//No es obligatorio...
		while(p <streamChar+m_blockSize)
		{
			*p=0;
			p++;
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
			m_registerCount++;
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

void Block::clear()
{
	m_registers.clear();
	m_registerCount=0;
	m_usedBytes=m_FirstRegisterOffset;
	restartCounter();
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
	loadResultEnum carga;
	return addRegister(reg, carga);
}

bool Block::addRegister(const VarRegister & reg, loadResultEnum &load)
{
	bool retVal=false;
	unsigned int newSize;

	//Calculo el tama�o que va a tener
	newSize = m_usedBytes+reg.getDiskSize();

	//Me fijo en que estado va a quedar la carga despues de la insercion
	load = evaluateLoad(newSize);

	//Valido que el registro a insertar no sea mas grande que un bloque
	if(reg.getDiskSize()> (m_blockSize-m_FirstRegisterOffset)/2)
		throw "Registro demasiado grande";

	//Si no va a haber overflow
	if(load != OVERFLOW_LOAD)
	{
		//Si ya hay algo en la lista de registros
		if(m_registers.size()>0)
			m_registers.insert(m_actualReg, reg);

		//Si no hay nada, el iterador apunta a cualquier cosa
		else
		{
			m_registers.push_back(reg);
			m_actualReg = m_registers.end();
		}

		m_posActual++;
		m_registerCount++;
		m_usedBytes+=reg.getDiskSize();
		retVal=true;
	}
	return retVal;
}

bool Block::modifyRegister(const VarRegister & reg)
{
	loadResultEnum carga;
	return modifyRegister(reg,carga);
}

bool Block::modifyRegister(const VarRegister & reg, loadResultEnum &load)
{
	bool retVal=false;
	VarRegister temp;
	unsigned int tamActual;
	unsigned int newSize;


	if(m_registers.size()>0&&m_actualReg!=m_registers.end())
	{
		temp = getNextRegister(false);
		tamActual= m_usedBytes-temp.getDiskSize();

		newSize =tamActual + reg.getDiskSize();

		load= evaluateLoad(newSize);

		if(load ==NORMAL_LOAD)
		{
			deleteRegister();
			addRegister(reg);
			m_usedBytes = tamActual+reg.getDiskSize();

			retVal=true;
		}

	}

	return retVal;
}

loadResultEnum Block::evaluateLoad(unsigned int bytes)
{
	loadResultEnum load = NORMAL_LOAD;

	if(bytes>m_blockSize)
		load = OVERFLOW_LOAD;
	else
		if(m_LoadFactor!=UNDEFINED_LOAD_FACTOR)
		{
			if(calculateFraction(bytes)<m_LoadFactor)
				load = UNDERFLOW_LOAD;
		}

	return load;
}

bool Block::deleteRegister()
{
	loadResultEnum carga;
	return deleteRegister(carga);
}

bool Block::deleteRegister(loadResultEnum &load)
{
	bool retVal=false;
	RegisterListIt it = m_actualReg;
	unsigned int regSize=0;
	RegisterListIt lastReg;
	it++;

	if(m_registers.size()>0&&m_actualReg!=m_registers.end())
	{
		regSize=m_actualReg->getDiskSize();
		lastReg = m_registers.end();
		lastReg--;

		if(m_actualReg==lastReg)
		{
			it=m_registers.end();
			m_posActual=-1;
		}

		//Calculo el tama�o que tendria despues de eliminar
		regSize=m_actualReg->getDiskSize();
		load= evaluateLoad(m_usedBytes-regSize);

		m_registers.erase(m_actualReg);

		if(m_registers.size()>0)
			m_actualReg=it;

		m_registerCount--;

		m_usedBytes-=regSize;

		retVal=true;
	}
	else
		throw "Error al eliminar el bloque";

	return retVal;
}

VarRegister Block::getRegisterN(unsigned int number)
{
	VarRegister reg;

	if(number > m_registers.size())
		throw "El numero del registro no existe en el bloque";

	unsigned int i;
	restartCounter();

	for(i=0; i < number; i++)
	{
		m_posActual++;
		m_actualReg++;
	}

	reg = getNextRegister(false);

	return reg;

}

VarRegister Block::getPreviousRegister(bool backward)
{
	VarRegister current;
	RegisterListIt it;
	it=m_actualReg;

	if(m_registers.size()>0)
	{
		if(it!=m_registers.end())
		{
			current=*it;
			it--;

			if(backward)
			{
				m_actualReg =it;
				m_posActual--;
			}
		}
	}

	return current;
}





float Block::calculateFraction(unsigned int value)
{
	float retVar= (float)value/m_blockSize;
	return retVar;
}

int Block::getPosActual()
{
	return m_posActual;
}

unsigned int Block::getUsedSpace()
{
	return m_usedBytes;
}

void Block::setLoadFactor(float factor)
{
	m_LoadFactor = factor;
}

float Block::getActualLoad()
{
	return (m_usedBytes/m_blockSize);
}

unsigned int Block::getBlockNumber()
{
	return m_blockNumber;
}

unsigned int Block::getRegisterAmount()
{
	return m_registerCount;
}

unsigned int Block::getMinimalLoad()
{
	unsigned int retVal = 0;

	if(m_LoadFactor!=UNDEFINED_LOAD_FACTOR)
		retVal =m_LoadFactor*m_blockSize;

	return retVal;
}

unsigned int Block::getRemainingSpace()
{
	return m_blockSize - m_usedBytes;
}


