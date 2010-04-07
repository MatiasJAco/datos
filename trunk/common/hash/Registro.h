/*
 * Registro.h
 *
 *  Created on: 27/03/2010
 *      Author: Adrián Bernardi
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_

#include <iostream>
#include <sstream>
using namespace std;

/**
 * Class Registro
 * Esta clase encapsula un registro de un archivo. El registro es identificado por una clave, y posee un contenido llamado "valor".
 */
class Registro {

private:

	int clave;
	string valor;

public:
	Registro(int clave, string valor);
	~Registro();

	/**
	 * Devuelve el tamaño en bytes que va a tener el registro en disco
	 * Es la suma de todos los atributos que se escriben a disco
	 * mas la informacion de control
	 */
	unsigned int getSize() const;

	/**
	 * Devuelve la clave del registro.
	 * @return La clave que identifica al registro
	 */
    int getClave() const;

    /**
     * Devuelve el contenido propio del registro.
     * @return El contenido del registro
     */
    string getValor() const;

    /**
	 * Devuelve un string con el contenido del registro.
	 * @return string con la informacion contenida en el registro
	 */
	std::string toString() const;

	Registro& operator =(const Registro & registro);
};

#endif /* REGISTRO_H_ */
