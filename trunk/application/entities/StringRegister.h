/*
 * StringRegister.h
 *
 *  Created on: 02/04/2010
 *      Author: kira
 */

#ifndef STRINGREGISTER_H_
#define STRINGREGISTER_H_

#include "../../common/register/Register.h"
#include "KeyInt.h"
#include "../../common/utils/ByteConverter.h"

#include <iostream>
#include <sstream>

/**
 * Class StringRegister
 * Tipo de registro que consta de una clave int y un string.
 *
 * @see Register, @see KeyInt
 */
class StringRegister: public Register {

	//Atributos
private:

	KeyInt m_clave;
	std::string m_string;

public:
	//-------------Constructor/Destructor------//
	StringRegister(){};

	StringRegister(const StringRegister& reg);

	StringRegister(KeyInt clave,std::string tstring);
	 ~StringRegister();

	unsigned int getSize() const;

	char* serialize(char* bytes) const;

	/**
	 * Transfo0rma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);

	std::string toString() const;

	Register& operator=(const Register& registro);

	bool operator==(const Register& registro) const	;

	bool operator<(const Register& registro) const;

	bool operator>(const Register& registro) const;

    KeyInt getClave() const
    {
        return m_clave;
    }

    std::string getString() const
    {
        return m_string;
    }

    void setClave(KeyInt clave)
    {
        this->m_clave = clave;
    }

    void setString(std::string string)
    {
        this->m_string = string;
    }



};

#endif /* STRINGREGISTER_H_ */
