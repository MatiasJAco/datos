/**
 * @file Register.h
 * @author MCM
 * @date 26-03-2010
 */

#ifndef REGISTER_H_
#define REGISTER_H_

#include <iostream>
#include <typeinfo>
#include <exception>
/**
 * Clase abstracta para el mapeo de datos en disco
 */
class Register {

public:

	//---------------Constructor/Destructor-------//
	/// El constructor
	Register();

	/** El destructor */
	virtual ~Register();

	/**
	 * Obtiene el tamaño del registro.
	 * \return El tamaño del registro.
	 */
	virtual unsigned int getSize() const = 0;

	//-------------Serialize/Deserialize----------//
	/**
	 * Serializa el registro en bytes.
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	virtual char* serialize(char* bytes) const = 0;

	/**
	 * Transforma la cadena de bytes a un registro.
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	virtual void deserialize(const char* bytes) = 0;


	/**
	 * Devuelve un string con el contenido del registro.
	 * Se debe definir en cada clase obligatoriamente, para
	 * ser utilizada por el operador << en Register
	 * @return string con la informacion contenida en el registro
	 * @see Register operator <<
	 */
	virtual std::string toString() const = 0;

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
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	virtual void setFields(const Register& registro) = 0;

	//------------------Operators------------------------//
	//	virtual Register& operator=(const Register& registro) = 0;

	/**
	 * Operador de comparacion de igualdad.
	 * Tiene sentido su definición para aquellos registros que tengan clave.
	 * El metodo no esta definido virtual puro. Para las clases que no lo implementan este
	 * metodo tira una excepcion.
	 * @param registro Registro de la misma clase contra el cual se hace la comparacion.
	 * @return TRUE si es igual, FALSE de lo contrario.
	 */
	virtual bool operator==(const Register& registro)const;

	/**
	 * Operador de comparacion por menor.
	 * Tiene sentido su definición para aquellos registros que tengan clave.
	 * El metodo no esta definido virtual puro. Para las clases que no lo implementan este
	 * metodo tira una excepcion.
	 * @param registro Registro de la misma clase contra el cual se hace la comparacion.
	 * @return TRUE si es menor, FALSE de lo contrario.
	 */
	virtual bool operator<(const Register& registro)const;

	/**
	 * Operador de comparacion por mayor.
	 * Tiene sentido su definición para aquellos registros que tengan clave.
	 * El metodo no esta definido virtual puro. Para las clases que no lo implementan este
	 * metodo tira una excepcion.
	 * @param registro Registro de la misma clase contra el cual se hace la comparacion.
	 * @return TRUE si es mayor, FALSE de lo contrario.
	 */
	virtual bool operator>(const Register& registro)const;

	/**
	 * Obtiene la clave del register.
	 * Tiene sentido su definición para aquellos registros que tengan clave.
	 * En caso de que el elemento no tenga una Key este metodo no se redefine.
	 * Para las clases que no lo implementan este metodo tira excepcion.
	 * En las clases que lo implementan este metodo crea una nueva clave mediante new por
	 * lo cual el manejo de memoria por el llamado a este metodo queda a cargo del usuario.
	 */
	virtual Register * getRegisterKey()const;

};


/**
 * @class RegisterComparator
 * Clase que me provee de una callback de comparacion, utilizada en containers de stl
 */
class RegisterComparator
{
public:
	/**
	 * Operador function_callback
	 * Utilizada en containers de stl, por ejemplo map, para comparar por menor
	 * a dos registros.
	 * @see Register
	 */
	bool operator() (Register* reg1,Register* reg2)
	{
		return ((*reg1) < (*reg2));
	}
};


/** @related Register
 * Operador << saca el contenido del Register en un stream, con los contenidos
 * para esto emplea el metodo toString().
 * Esta funcion se emplea principalmente para pruebas.
 * @see toString()
 */

std::ostream& operator <<  (std::ostream& os,const Register& reg);

/**
 * TODO NO IMPLEMENTADA
 */
std::istream& operator >> (std::istream& is,const Register& reg);


#endif /* REGISTER_H_ */
