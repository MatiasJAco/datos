/**
 * @file KeyInt.h
 *
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

	/// Constructor. Recibe un entero.
	KeyInt(int value);

	/// Constructor de copia.
	KeyInt(const KeyInt& key);

	/// Destructor.
	~KeyInt();

	/**
	 * Obtiene el tamaño del registro.
	 * \return El tamaño del registro.
	 */
	unsigned int getSize() const;

	/**
	 * Convierte el registro a una cadena de bytes.
	 * Convierte cada atributo mediante los metodos definidos en
	 * ByteConverter
	 * @param bytes cadena en la cual se serializan los atributos
	 * @return cadena resultante al serializar
	 * @see ByteConverter
	 */
	char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * @param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);

	//-----------Operators------------------------//
	/**
	 * Operador de asignacion.
	 * @param registro Registro de la misma clase contra el cual se hace la asignacion.
	 * @return referencia a Register
	 */
	Register& operator=(const Register& registro);

	/**
	 * Operador de comparacion de igualdad.
	 * Tiene sentido su definición para aquellos registros que tengan clave, como es el caso de
	 * KeyInt.
	 * El metodo no esta definido virtual puro. Para las clases que no lo implementan este
	 * metodo tira una excepcion.
	 * @param registro Registro de la misma clase contra el cual se hace la comparacion.
	 * @return TRUE si es igual, FALSE de lo contrario.
	 */
	bool operator==(const Register& registro)const;

	/**
	 * Operador de comparacion por menor.
	 * Tiene sentido su definición para aquellos registros que tengan clave.
	 * El metodo no esta definido virtual puro. Para las clases que no lo implementan este
	 * metodo tira una excepcion.
	 * @param registro Registro de la misma clase contra el cual se hace la comparacion.
	 * @return TRUE si es menor, FALSE de lo contrario.
	 */
	bool operator<(const Register& registro)const;

	/**
	 * Operador de comparacion por mayor.
	 * Tiene sentido su definición para aquellos registros que tengan clave.
	 * El metodo no esta definido virtual puro. Para las clases que no lo implementan este
	 * metodo tira una excepcion.
	 * @param registro Registro de la misma clase contra el cual se hace la comparacion.
	 * @return TRUE si es mayor, FALSE de lo contrario.
	 */
	bool operator>(const Register& registro)const;

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	void setFields(const Register& registro);

	/**
	 * Devuelve un string con el contenido del registro.
	 * Se debe definir en cada clase obligatoriamente, para
	 * ser utilizada por el operador << en Register
	 * @return string con la informacion contenida en el registro
	 * @see Register operator <<
	 */
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
