/*
 * Key.h
 *
 *  Created on: 02/04/2010
 *      Author: kira
 */

#ifndef KEY_H_
#define KEY_H_

#include "Register.h"
/**
 * Class Key
 * Se define esta clase para diferenciar los registros que contienen alguna informacion
 * de aquellos registros que unicamente se usan para direccionar.
 * Esto es de particular utilidad en el arbol B+ ya que los nodos internos solamente contienen
 * las claves.
 * Aquellos registros que contienen informacion que deba ser direccionada deben tener una clave
 * @see Register
 *
 */
class Key: public Register {
public:
	Key();
	virtual ~Key();

	/**
	 * Obtiene el tamaño del registro.
	 * \return El tamaño del registro.
	 */
	virtual unsigned int getSize() const = 0;


	/**
	 * Devuelve una instancia nueva de la clase.
	 * Se crea una nueva instancia del tipo especifico con new()
	 * Importante: Una vez que se termine de usar la instancia
	 * es necesario liberar la memoria mediante un delete.
	 * @throws bad_alloc en caso de error al asignar memoria
	 * @return Register * puntero a la instancia nueva
	 */
	virtual Register * newInstance() const = 0;

	/**
	 * Serializa el registro en bytes
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	virtual char* serialize(char* bytes) const = 0;
	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	virtual void deserialize(const char* bytes) = 0;

	//---------------Operators--------------------//
	//TODO REVISAR, NO FUNCIONA
//	virtual Register& operator=(const Register& registro) = 0;

	virtual bool operator==(const Register& registro)const = 0;

	virtual bool operator<(const Register& registro)const = 0;

	virtual bool operator>(const Register& registro)const = 0;

	virtual std::string toString() const = 0;

};

#endif /* KEY_H_ */
