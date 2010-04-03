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


	/**
	 * Devuelve un string con el contenido del registro
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

	//	virtual Register& operator=(const Register& registro) = 0;

};

/**
 * Operador << saca el contenido del Register en un stream, con los contenidos
 * para esto emplea el metodo toString().
 * Esta funcion se emplea principalmente para pruebas.
 * @see toString()
 */

std::ostream& operator <<  (std::ostream& os,const Register& reg);

//TODO ME PARE QUE NO VA
std::istream& operator >> (std::istream& is,const Register& reg);


#endif /* REGISTER_H_ */
