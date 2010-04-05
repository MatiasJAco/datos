/*
 * KeyInt.h
 *
 *  Created on: 02/04/2010
 *      Author: kira
 */

#ifndef KEYINT_H_
#define KEYINT_H_

#include "../../common/utils/ByteConverter.h"
#include "../../common/register/Register.h"

#include <sstream>

/**
 * Class KeyInt
 * Implementacion de Key utilizando una clave tipo entero.
 * @see Register
 */
class KeyInt: public Register {

private:
	int m_value;

public:
	KeyInt();

	KeyInt(int value);

	KeyInt(const KeyInt& key);

	~KeyInt();

	/**
	 * Obtiene el tamaño del registro.
	 * \return El tamaño del registro.
	 */
	unsigned int getSize() const;

	/**
	 * Serializa el registro en bytes
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	char* serialize(char* bytes) const;
	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);

	Register& operator=(const Register& registro);

	bool operator==(const Register& registro)const;

	bool operator<(const Register& registro)const;

	bool operator>(const Register& registro)const;

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	void setFields(const Register& registro);


	std::string toString() const;

	/**
	 * Devuelve una instancia nueva de la clase.
	 * Se crea una nueva instancia del tipo especifico con new()
	 * Importante: Una vez que se termine de usar la instancia
	 * es necesario liberar la memoria mediante un delete.
	 * @throws bad_alloc en caso de error al asignar memoria
	 * @return Register * puntero a la instancia nueva
	 */
	Register * newInstance()const;

};

#endif /* KEYINT_H_ */
