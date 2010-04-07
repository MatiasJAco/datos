/*
 * Registro.cpp
 *
 *  Created on: 27/03/2010
 *      Author: Adrián Bernardi
 */

#include "Registro.h"

Registro::Registro(int clave, string valor)
{
	this->clave = clave;
	this->valor = valor;
}

Registro::~Registro()
{
	// TODO Auto-generated destructor stub
}

unsigned int Registro::getSize() const
{
	unsigned int size = 0;
	size = sizeof(this->clave) + sizeof(this->valor);
	return size;
}

int Registro::getClave() const
{
    return this->clave;
}

string Registro::getValor() const
{
	return this->valor;
}

string Registro::toString() const
{
	stringstream ss;
	ss << "Clave: " << this->getClave() << endl << "Valor: "<< this->getValor() << endl;
	return ss.str();
}

Registro& Registro::operator =(const Registro & registro)
{
	const Registro& reg = dynamic_cast<const Registro&> (registro);

 	if (this == &reg)      // Same object?
 		return *this;      // Yes, so skip assignment, and just return *this.

 	this->clave = reg.clave;
	this->valor = reg.valor;
	return *this;
}
