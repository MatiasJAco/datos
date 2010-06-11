/*
 * Register.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef REGISTER_H_
#define REGISTER_H_
#include <sstream>

/**
 * Clase de la cual derivan los registros.
 */
class Register
{
public:
	Register();
	virtual ~Register();

	/**
	 * Convierte a registro un stream pasado por parametro
	 */
	virtual	bool setValue(char * valor,unsigned int size)=0;

	/**
	 * Recupera el stream que corresponde a un Registro
	 */
	virtual char *getValue()=0;

	/**
	 * Obtiene el tamaño del Registro (en bytes)
	 */
	virtual unsigned int getSize()const =0 ;

	/**
	 * Carga el registro desde un stream
	 * @param stream stream de caracteres del cual se carga el registro
	 * @return true en caso de ok, false en caso contrario
	 */
	virtual bool deserialize(char * stream)=0;



protected:
	/**
	 * Stream que contiene los datos del registro
	 */
	char * m_value;
};

#endif /* REGISTER_H_ */
