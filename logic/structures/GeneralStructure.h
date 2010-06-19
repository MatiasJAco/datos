/*
 * GeneralStructure.h
 *
 *  Created on: Jun 18, 2010
 *      Author: pablolisio
 */

#ifndef GENERALSTRUCTURE_H_
#define GENERALSTRUCTURE_H_

#include "../input/StringInputData.h"
#include "../exceptions/ManagerException.h"

class GeneralStructure {
public:
	GeneralStructure();
	virtual ~GeneralStructure();


    /*----------------------------------------------------------*/
	/*-------------PRIMITIVAS de las ESTRUCTURAS----------------*/
	/*----------------------------------------------------------*/

	/**
	 * Agrega un elemento nuevo al archivo de la estructura.
	 * @param clave Es la clave del dato a ingresar.
	 * @param valor Es el valor del dato a ingrear.
	 * @return true si la operación fue exitosa
	 */
	virtual bool insert(std::string clave, std::string valor) throw (ManagerException) = 0;

	/**
	 * Verifica si existe un dato en un bloque. El dato está identificado por la clave que se pasa por parámetro.
	 * @param key Es la clave del dato que se desea hallar.
	 * @return true si ya existe en el HashFile la clave pasada por parametro
	 */
	virtual bool existsElement(std::string key) = 0;

	/**
	 * Busca y retorna un elemento dado su clave.
	 * @param key Es la clave del dato a buscar
	 * @param data Es el StringInputData que representa al dato que contiene la clave a buscar
	 * @return true si la operación fue exitosa
	 */
	virtual bool find(std::string key, InputData & data) throw (ManagerException) = 0;

	/**
	 * Cambia el valor de un key pasado por parámetro.
	 * @param key Es el key al cual se le cambiará el valor.
	 * @param newValue Es el valor nuevo que tomara la clave pasada por parametro.
	 * @return true si la operación fue exitosa
	 */
	virtual bool modify(std::string key, std::string newValue) throw (ManagerException) = 0;

	/**
	 * Elimina el dato, cuya clave es la pasada por parametro.
	 * @param key Es la clave del dato que se desea borrar.
	 * @return true si la operacion fue exitosa
	 */
	virtual bool remove(std::string key) throw (ManagerException) = 0;

	/**
	 * Imprime la estructura por pantalla.
	 */
	virtual void print() = 0;
};

#endif /* GENERALSTRUCTURE_H_ */
