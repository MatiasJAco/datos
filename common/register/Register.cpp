/*
 * Registro.cpp
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#include "Register.h"

using namespace std;

Register::Register() {
	// TODO Auto-generated constructor stub

}

Register::~Register() {
	// TODO Auto-generated destructor stub
}

std::istream & operator >>(std::istream & is, const Register & reg)
{
	return is;
}



std::ostream & operator <<(std::ostream & os, const Register & reg)
{
	os << reg.toString();

	return os;
}

bool Register::operator >(const Register & registro) const
{
	throw ("Operador > no implementado");
}



bool Register::operator <(const Register & registro) const
{
	throw ("Operador < no implementado");
}



bool Register::operator ==(const Register & registro) const
{
	throw ("Operador == no implementado");
}

Register *Register::getRegisterKey() const
{
	throw ("No se definio getRegisterKey() para esta clase");
}






