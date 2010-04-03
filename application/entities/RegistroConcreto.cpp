/*
 * RegistroConcreto.cpp
 *
 *  Created on: 27/03/2010
 *      Author: kira
 */

#include "RegistroConcreto.h"

using namespace std;

RegistroConcreto::RegistroConcreto(KeyInt clave, int tint,double tdouble, float tfloat, std::string tstring):m_clave(clave)
{
	m_int = tint;
	m_double = tdouble;
	m_float = tfloat;
	m_string = tstring;

}

RegistroConcreto::~RegistroConcreto() {
	// TODO Auto-generated destructor stub
}


RegistroConcreto::RegistroConcreto(const RegistroConcreto & reg)
{
	m_clave = reg.m_clave;
	m_int = reg.m_int;
	m_double = reg.m_double;
	m_float = reg.m_float;
	m_string = reg.m_string;
}

unsigned int RegistroConcreto::getSize() const
{
	unsigned int size = 0;

	size = m_clave.getSize()+ sizeof(m_int)+sizeof(m_double)+sizeof(m_float)+sizeof(char)*(m_string.size()+1);

	return size;
}


char *RegistroConcreto::serialize(char *bytes) const
{
	m_clave.serialize(bytes);
	bytes+= m_clave.getSize();
	ByteConverter::intToBytes(m_int,bytes);
	bytes+= sizeof(m_int);
	ByteConverter::doubleToBytes(m_double, bytes);
	bytes+=sizeof(m_double);
	ByteConverter::floatToBytes(m_float, bytes);
	bytes+=sizeof(m_float);
	ByteConverter::stringToBytes(m_string,bytes);

	return bytes;
}



void RegistroConcreto::deserialize(const char *bytes)
{
	m_clave.deserialize(bytes);
	bytes+= m_clave.getSize();
	m_int = ByteConverter::bytesToInt(bytes);
	bytes+=sizeof(m_int);
	m_double = ByteConverter::bytesToDouble(bytes);
	bytes+=sizeof(m_double);
	m_float = ByteConverter::bytesToFloat(bytes);
	bytes+=sizeof(m_float);
	m_string = ByteConverter::bytesToString(bytes);

}


Register & RegistroConcreto::operator =(const Register & registro)
{
	const RegistroConcreto& reg = dynamic_cast<const RegistroConcreto&> (registro);

 	if (this == &reg)      // Same object?
 		return *this;        // Yes, so skip assignment, and just return *this.

 	m_clave= reg.m_clave;
	m_int = reg.m_int;
	m_double = reg.m_double;
	m_float = reg.m_float;
	m_string = reg.m_string;

	return *this;
}



Register *RegistroConcreto::newInstance() const
{
	return new RegistroConcreto();
}


string RegistroConcreto::toString() const
{
	stringstream retStr;

	retStr <<m_clave<< endl<<"int: "<<m_int<<endl<<"double "<<m_double<<endl<<"float "<<
			m_float<<endl<<"string "<<m_string<<endl;

	return retStr.str();

}

