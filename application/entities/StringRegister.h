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

	Register& operator=(const Register& registro);

	/**
	 * Devuelve una instancia nueva de la clase.
	 * Se crea una nueva instancia del tipo especifico con new()
	 * Importante: Una vez que se termine de usar la instancia
	 * es necesario liberar la memoria mediante un delete.
	 * @throws bad_alloc en caso de error al asignar memoria
	 * @return Register * puntero a la instancia nueva
	 */
	Register * newInstance() const;


	char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);


	Register * getRegisterKey()const;

	std::string toString() const;

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	void setFields(const Register& registro);


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
