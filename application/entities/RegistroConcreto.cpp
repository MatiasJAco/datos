/*
 * RegistroConcreto.cpp
 *
 *  Created on: 27/03/2010
 *      Author: kira
 */

#include "RegistroConcreto.h"

using namespace std;

RegistroConcreto::RegistroConcreto(int clave, double tdouble, float tfloat, std::string tstring)
{
	m_clave = clave;
	m_double = tdouble;
	m_float = tfloat;
	m_string = tstring;

}

RegistroConcreto::~RegistroConcreto() {
	// TODO Auto-generated destructor stub
}

unsigned int RegistroConcreto::getSize()
{
	unsigned int size = 0;

	size = sizeof(m_clave)+sizeof(m_double)+sizeof(m_float)+sizeof(char)*(m_string.size()+1);

	return size;
}


char *RegistroConcreto::serialize(char *bytes)
{
	ByteConverter::intToBytes(m_clave,bytes);
	bytes+= sizeof(m_clave);
	ByteConverter::doubleToBytes(m_double, bytes);
	bytes+=sizeof(m_double);
	ByteConverter::floatToBytes(m_float, bytes);
	bytes+=sizeof(m_float);
	ByteConverter::stringToBytes(m_string,bytes);

	return bytes;
}



void RegistroConcreto::deserialize(const char *bytes)
{
	m_clave = ByteConverter::bytesToInt(bytes);
	bytes+=sizeof(m_clave);
	m_double = ByteConverter::bytesToDouble(bytes);
	bytes+=sizeof(m_double);
	m_float = ByteConverter::bytesToFloat(bytes);
	bytes+=sizeof(m_float);
	m_string = ByteConverter::bytesToString(bytes);

}



bool RegistroConcreto::operator <(Register & registro)
{
	RegistroConcreto *reg=dynamic_cast<RegistroConcreto*> (&registro);

	return (m_clave<reg->m_clave);
}



string RegistroConcreto::toString()
{
	stringstream retStr;

	retStr << "clave: "<<m_clave<<endl<<"double "<<m_double<<endl<<"float "<<
			m_float<<endl<<"string "<<m_string<<endl;

	return retStr.str();

}

bool RegistroConcreto::operator >(Register & registro)
{
	RegistroConcreto *reg=dynamic_cast<RegistroConcreto*> (&registro);

	return (m_clave>reg->m_clave);
}


bool RegistroConcreto::operator ==(Register & registro)
{
	RegistroConcreto *reg=dynamic_cast<RegistroConcreto*> (&registro);

	return (m_clave==reg->m_clave);
}

