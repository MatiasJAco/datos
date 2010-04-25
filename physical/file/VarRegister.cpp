/*
 * VarRegister.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "VarRegister.h"
#include "../utils/ByteConverter.h"


using namespace std;

VarRegister::VarRegister():Register()
{
}

VarRegister::VarRegister(const VarRegister &orig):Register()
{
	if(orig.m_value!=NULL)
	{
		unsigned int size;
		size = orig.getDiskSize();

		m_value = new char[size];
		memcpy(m_value,orig.m_value,sizeof(char)*size);
	}
}

VarRegister::VarRegister(char *value, unsigned int size):Register()
{
	setValue(value, size);
}

VarRegister::~VarRegister()
{
	if(m_value !=NULL)
		delete [] m_value;
	m_value =NULL;
}


bool VarRegister::serialize(char *stream)
{
	bool retVal=false;

	if(stream!=NULL)
	{
		unsigned int size;

		size=getSize();

		memcpy(stream,m_value,sizeof(char)*size+sizeof(size));
		retVal=true;
	}
	return retVal;
}

bool VarRegister::deserialize(char * stream)
{
	bool retVal=false;

	if(stream!=NULL)
	{
		if(m_value!=NULL)
			delete [] m_value;


		unsigned int size =0;
		memcpy(&size,stream,sizeof(size));

		m_value = new char[size+sizeof(unsigned int)];

		memcpy(m_value,stream,sizeof(char)*size+sizeof(unsigned int));
		retVal=true;
	}
	return retVal;
}

unsigned int VarRegister::getSize() const
{
	unsigned int size = 0;
	memcpy(&size,m_value,sizeof(size));

	return size;
}

unsigned int VarRegister::getDiskSize() const
{
	unsigned int size = VarRegister::getSize() + sizeof(unsigned int);
	return size;
}

char *VarRegister::getValue()
{
	char * retChar=NULL;

	if(m_value !=NULL)
	{
		unsigned int size = 0;

		char *p=m_value;

		size = getSize();

		p+=sizeof(size);
		retChar = new char[size+1];

		memcpy(retChar,p,size*sizeof(char));
	}

	return retChar;
}

bool VarRegister::setValue(int int1)
{
	return VarRegister::setValue((char*)&int1, sizeof(int));
}

bool VarRegister::setValue(string &value)
{
	return VarRegister::setValue((char*)value.c_str(),value.size()+1);
}

bool VarRegister::setValue(char * valor, unsigned int size)
{
		bool retVal=true;

		if(valor !=NULL)
		{
			if(m_value !=NULL)
				delete [] m_value;

			m_value = new char[size+sizeof(size)];
			char *p=m_value;

			memcpy(p,&size,sizeof(size));
			p+=sizeof(size);

			unsigned int temp =size*sizeof(char);
			temp++;
			memcpy(p,valor,size*sizeof(char));

			retVal=true;
		}
		else
			retVal=false;

		return true;

}

VarRegister & VarRegister::operator=(const VarRegister &orig)
{
	if(orig.m_value!=NULL)
	{
		unsigned int size;
		size = orig.getSize();

		if(m_value!=NULL)
			delete [] m_value;

		m_value = new char[size+sizeof(size)];
		memcpy(m_value,orig.m_value,sizeof(size)+sizeof(char)*size);
	}
	return *this;
}

void VarRegister::printRegister()
{
	if(m_value !=NULL)
		ByteConverter::printHexa(m_value,getSize()+sizeof(unsigned int));
	else
		cout << "Registro vacio"<<endl;
}



