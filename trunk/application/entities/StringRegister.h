/**
 * @file StringRegister.h
 *
 *
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

	/// Constructor de copia
	StringRegister(const StringRegister& reg);

	/**
	 * Constructor que recibe los dos datos que identifican a StringRegister
	 * @param clave Clave de tipo Int
	 * @param tstring Parametro de tipo string.
	 */
	StringRegister(KeyInt clave,std::string tstring);

	///Destructor
	 ~StringRegister();

	 /// Devuelve el tamaño en bytes del registro.
	 unsigned int getSize() const;

	 /// Operador de asignación.
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

	/**
	 * Obtiene la clave del register.
	 * Tiene sentido su definición para aquellos registros que tengan clave, como es el caso de
	 * RegistroConcreto.
	 * En caso de que el elemento no tenga una Key este metodo no se redefine.
	 * Para las clases que no lo implementan este metodo tira excepcion.
	 * En las clases que lo implementan este metodo crea una nueva clave mediante new por
	 * lo cual el manejo de memoria por el llamado a este metodo queda a cargo del usuario.
	 */
	Register * getRegisterKey()const;

	/**
	 * Devuelve un string con el contenido del registro
	 * Se debe definir en cada clase obligatoriamente, para
	 * ser utilizada por el operador << en Register
	 * @return string con la informacion contenida en el registro
	 * @see Register operator <<
	 */
	std::string toString() const;

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	void setFields(const Register& registro);

	/// Devuelve la clave del registro, que pertenece al tipo KeyInt.
    KeyInt getClave() const
    {
        return m_clave;
    }

    /// Devuelve el string que forma parte del registro.
    std::string getString() const
    {
        return m_string;
    }

    /// Modifica la clave del registro.
    void setClave(KeyInt clave)
    {
        this->m_clave = clave;
    }

    /// Modifica el string del registro.
    void setString(std::string string)
    {
        this->m_string = string;
    }



};

#endif /* STRINGREGISTER_H_ */
