/*
 * RegistroConcreto.h
 *
 *  Created on: 27/03/2010
 *      Author: kira
 */

#ifndef REGISTROCONCRETO_H_
#define REGISTROCONCRETO_H_

#include "../../common/register/Register.h"
#include "KeyInt.h"
#include "../../common/utils/ByteConverter.h"

#include <iostream>
#include <sstream>

/**
 * Class RegistroConcreto
 * Ejemplo de creacion de registro. Se crean atributos de cada uno de los tipos
 * que se pueden convertir a bytes para demostrar la funcionalidad.
 * El guardado a disco se debe efectuar fuera de esta clase, escribiendo la salida
 * del serialize(). La principal funcion de las clases derivadas de Register es
 * implementar la logica del serializado a bytes, de manera de simplemente escribir
 * un array de bytes en disco.
 * @see Register.
 */
class RegistroConcreto: public Register {

private:

	/** Se agrego el atributro clave que es del tipo Key.
	* Para un registro que tenga una clave hay que definir una clase derivada de Key
	* Esto se hace pq dentro del arbol vamos a tener muchos registros que solo tengan clave
	* (para los nodos internos)
	**/
	KeyInt m_clave;

	/**
	 * Contenido del registro
	 */
	int m_int;
	double m_double;
	float m_float;
	std::string m_string;

public:
	//-----------------------Constructor/Destructor---------------//
	RegistroConcreto(){};

	RegistroConcreto(const RegistroConcreto& reg);

	RegistroConcreto(KeyInt clave,int tint,double tdouble,float tfloat,std::string tstring);
	~RegistroConcreto();


	/**
	 * Devuelve el tamaño en bytes que va a tener el registro en disco
	 * Es la suma de todos los atributos que se escriben a disco
	 * mas la informacion de control
	 * @see ByteConverter
	 */
	unsigned int getSize() const;

	/**
	 * Devuelve un string con el contenido del registro
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



	Register& operator=(const Register& registro);

	//---------------Serialize/Deserialize-------//
	/**
	 * Convierte el registro a una cadena de bytes.
	 * Convierte cada atributo mediante los metodos definidos en
	 * ByteConverter
	 * @param char* bytes cadena en la cual se serializan los atributos
	 * @return char* cadena resultante al serializar
	 * @see ByteConverter
	 */
	char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);

	// -----------------Get/Set----------------------//
    int getClave() const
    {
        return m_int;
    }

    double getDouble() const
    {
        return m_double;
    }

    float getFloat() const
    {
        return m_float;
    }

    std::string getString() const
    {
        return m_string;
    }

    void setClave(int m_clave)
    {
        this->m_int = m_clave;
    }

    void setDouble(double m_double)
    {
        this->m_double = m_double;
    }

    void setFloat(float m_float)
    {
        this->m_float = m_float;
    }

    void setString(std::string m_string)
    {
        this->m_string = m_string;
    }
    //-----------------------------------------------
};



#endif /* REGISTROCONCRETO_H_ */
