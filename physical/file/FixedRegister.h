/*
 * FixedRegister.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef FIXEDREGISTER_H_
#define FIXEDREGISTER_H_
#include "Register.h"
#include <sstream>
#include <cstring>
#include <iostream>

/**
 * Registros de longitud fija. No se persiste la longitud a disco
 * Siempre hay que indicar la longitud desde afuera
 */
class FixedRegister: public Register
{
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	FixedRegister();
	/**
	 * Constructor
	 * @param size fija el tamaño del registro
	 */
	FixedRegister(const unsigned int size);

	/**
	 * Constructor
	 * @param value valor del registro
	 * @param size fija el tamaño del registro
	 */
	FixedRegister(char * value,const unsigned int size);
	~FixedRegister();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Convierte a registro un stream pasado por parametro
	 * @param valor stream a convertir en registro
	 * @param size tamano del registro
	 * @return bool true en caso de exito
	 */
	bool setValue(char * valor,unsigned int size);

	/**
	 * Recupera el stream que corresponde a un Registro
	 * @return char * stream con el contenido del registro.
	 */
	char * getValue();

	/**
	 * Obtiene el tamaÃ±o del Registro (en bytes)
	 * @return unsigned int tamano del registro
	 */
	unsigned int getSize()const;

	/**
	 * Carga el registro desde un stream
	 * @param stream stream de caracteres del cual se carga el registro
	 * @return true en caso de ok, false en caso contrario
	 */

	bool deserialize(char * stream);


private:

	/**
	 * Tamaño del registro
	 */
	unsigned int m_size;
};

#endif /* FIXEDREGISTER_H_ */
