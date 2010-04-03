/*
 * StringRegister.cpp
 *
 *  Created on: 02/04/2010
 *      Author: kira
 */

#include "StringRegister.h"

using namespace std;

StringRegister::StringRegister(KeyInt clave,std::string tstring):m_clave(clave)
{
	m_string = tstring;

}

StringRegister::~StringRegister() {
	// TODO Auto-generated destructor stub
}


StringRegister::StringRegister(const StringRegister & reg)
{
	m_clave = reg.m_clave;
	m_string = reg.m_string;
}

unsigned int StringRegister::getSize() const
{
	unsigned int size = 0;

	size = m_clave.getSize() + sizeof(char)*(m_string.size()+1);

	return size;
}


char *StringRegister::serialize(char *bytes) const
{
	m_clave.serialize(bytes);
	bytes+= m_clave.getSize();
	ByteConverter::stringToBytes(m_string,bytes);

	return bytes;
}



void StringRegister::deserialize(const char *bytes)
{
	m_clave.deserialize(bytes);
	bytes+= m_clave.getSize();
	m_string = ByteConverter::bytesToString(bytes);

}


Register & StringRegister::operator =(const Register & registro)
{
	const StringRegister& reg = dynamic_cast<const StringRegister&> (registro);

 	if (this == &reg)      // Same object?
 		return *this;        // Yes, so skip assignment, and just return *this.

 	m_clave= reg.m_clave;
	m_string = reg.m_string;

	return *this;
}



Register *StringRegister::newInstance() const
{
	return new StringRegister(*this);
}

Register *StringRegister::getRegisterKey() const
{
	KeyInt *key = new KeyInt(m_clave);
	return key;
}

string StringRegister::toString() const
{
	stringstream retStr;

	retStr <<m_clave<< endl<<"string "<<m_string<<endl;

	return retStr.str();

}
