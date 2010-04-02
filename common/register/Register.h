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
	virtual unsigned int getSize() const = 0;


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



	virtual bool operator==(const Register& registro)const = 0;

	virtual bool operator<(const Register& registro)const = 0;

	virtual bool operator>(const Register& registro)const = 0;

	virtual std::string toString() const = 0;

};

std::ostream& operator <<  (std::ostream& os,const Register& reg);

std::istream& operator >> (std::istream& is,const Register& reg);

////< Para usarlo en sets de stl
class RegisterCmp{

public:
	  bool operator() (const Register& r1, const Register& r2) const
	  {
		  return r1 < r2;
	  }

};

#endif /* REGISTER_H_ */
