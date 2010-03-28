/**
 * \file Registro.h
 * \author MCM
 * \date 26-03-2010
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include <iostream>
#include <typeinfo>
/**
 * Clase abstracta para el mapeo de datos en disco
 */
class Register {

public:

	/// El constructor
	Register();
	/** El destructor */
	virtual ~Register();

	/**
	 * Obtiene el tamaño del registro.
	 * \return El tamaño del registro.
	 */
	virtual unsigned int getSize()=0;


	/**
	 * Serializa el registro en bytes
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	virtual char* serialize(char* bytes) = 0;

	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	virtual void deserialize(const char* bytes) = 0;



	virtual bool operator==(Register& registro) = 0;

	virtual bool operator<(Register& registro) = 0;

	virtual bool operator>(Register& registro) = 0;

	virtual std::string toString() = 0;

};

std::ostream& operator << (std::ostream& os, Register& reg);

std::istream& operator >> (std::istream& is,Register& reg);

#endif /* REGISTER_H_ */
