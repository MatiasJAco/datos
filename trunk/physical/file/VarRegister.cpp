/*
 * VarRegister.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "VarRegister.h"


using namespace std;

VarRegister::VarRegister():Register()
{
}


VarRegister::VarRegister(char *value, unsigned int size):Register()
{
	setValue(value, size);
}

VarRegister::~VarRegister()
{
	if(m_value !=NULL)
		delete m_value;
}

bool VarRegister::setValue(char * valor, unsigned int size)
{
		bool retVal=true;

		if(valor !=NULL)
		{
			if(m_value !=NULL)
				delete m_value;

			m_value = new char[size+1];
			char *p=m_value;

			memcpy(p,&size,sizeof(size));
			p+=sizeof(size);

			memcpy(p,valor,size*sizeof(char));

			retVal=true;
		}
		else
			retVal=false;

		return true;

}

unsigned int VarRegister::getSize()
{
	unsigned int size = 0;
	memcpy(&size,m_value,sizeof(size));

	return size;
}



char *VarRegister::getValue()
{
	char * retChar=NULL;

	if(m_value !=NULL)
	{
		unsigned int size = 0;

		char *p=m_value;

		memcpy(&size,m_value,sizeof(size));
		p+=sizeof(size);

		retChar = new char[size];

		memcpy(retChar,p,size*sizeof(char));
	}

	return retChar;
}



