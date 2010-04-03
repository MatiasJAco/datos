/*
 * KeyInt.cpp
 *
 *  Created on: 02/04/2010
 *      Author: kira
 */

#include "KeyInt.h"

using namespace std;

KeyInt::KeyInt() {
	// TODO Auto-generated constructor stub

}

KeyInt::KeyInt(int value)
{
	m_value = value;
}

KeyInt::~KeyInt() {
	// TODO Auto-generated destructor stub
}

bool KeyInt::operator <(const Register & registro) const
{
	const KeyInt& reg = dynamic_cast<const KeyInt&> (registro);

	return (m_value<reg.m_value);
}



bool KeyInt::operator >(const Register & registro) const
{
	const KeyInt& reg = dynamic_cast<const KeyInt&> (registro);

	return (m_value>reg.m_value);
}

bool KeyInt::operator ==(const Register & registro) const
{
	const KeyInt& reg = dynamic_cast<const KeyInt&> (registro);

	return (m_value==reg.m_value);
}



char *KeyInt::serialize(char *bytes) const
{
	ByteConverter::intToBytes(m_value,bytes);

	return bytes;
}


void KeyInt::deserialize(const char *bytes)
{
	m_value = ByteConverter::bytesToInt(bytes);
}


unsigned int KeyInt::getSize() const
{
	return sizeof(m_value);
}

Register & KeyInt::operator =(const Register & registro)
{
 	const KeyInt& reg = dynamic_cast<const KeyInt&> (registro);

 	if (this == &reg)      // Same object?
 		return *this;        // Yes, so skip assignment, and just return *this.

	m_value = reg.m_value;

	return *this;
}

std::string KeyInt::toString() const
{
	stringstream retStr;

	retStr << "clave: "<<m_value;

	return retStr.str();
}

Register *KeyInt::newInstance() const
{
	return new KeyInt();
}




