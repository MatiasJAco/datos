/*
 * FixedRegister.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "FixedRegister.h"

using namespace std;

FixedRegister::FixedRegister():Register()
{
	//Por default lo pongo en un valor falso, para forzar a setear el tamaño
	m_size = 0;
}

FixedRegister::FixedRegister(const unsigned int size):Register()
{
	if(size>0)
		m_size = size;
}

FixedRegister::FixedRegister(char *value, const unsigned int size):Register()
{
	if(size>0)
	{
		m_size = size;
		setValue(value, size);
	}
}

FixedRegister::~FixedRegister()
{
	if(m_value !=NULL)
		delete [] m_value;
}


bool FixedRegister::setValue(char *valor, unsigned int size)
{
	bool retVal=true;

	if(valor !=NULL&& size>0)
	{
		m_size=size;

		if(m_value !=NULL)
			delete [] m_value;

		m_value = new char[size];
		char *p=m_value;

		memcpy(p,valor,size*sizeof(char));

		retVal=true;
	}
	else
		retVal=false;

	return true;
}



char *FixedRegister::getValue()
{
	char * retChar=NULL;

	if(m_value !=NULL&& m_size>0)
	{
		char *p=m_value;

		retChar = new char[m_size+1];

		memcpy(retChar,p,m_size*sizeof(char));
	}

	return retChar;
}

bool FixedRegister::deserialize(char * stream)
{
	return true;
}


unsigned int FixedRegister::getSize()
{
	return m_size;
}


