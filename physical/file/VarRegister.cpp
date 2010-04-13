/*
 * VarRegister.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "VarRegister.h"


using namespace std;

VarRegister::VarRegister()
{
	m_value=NULL;
}


VarRegister::VarRegister(std::stringstream value)
{
}

VarRegister::~VarRegister()
{
	if(m_value !=NULL)
		delete m_value;
}

bool VarRegister::setValue(char * valor, unsigned int size)
{
		if(m_value !=NULL)
			delete m_value;

		m_value = new char[size+1];
		char *p=m_value;

		memcpy(p,&size,sizeof(size));
		p+=sizeof(size);

		memcpy(p,&valor,size);

		return true;

}

bool VarRegister::setValue(char * valor)
{
	return false;
}

unsigned int VarRegister::getSize()
{
	return 0;
}



char *VarRegister::getValue()
{

	unsigned int size = 0;

	char *p=m_value;

	memcpy(&size,m_value,sizeof(size));
	p+=sizeof(size);

	char * retChar = new char[size];

	memcpy(retChar,p,size);

	return retChar;
}



