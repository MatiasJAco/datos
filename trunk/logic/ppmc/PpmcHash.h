/*
 * PpmcHash.h
 *
 *  Created on: Jun 24, 2010
 *      Author: pablolisio
 */

#ifndef PPMCHASH_H_
#define PPMCHASH_H_

#include "Ppmc.h"

class PpmcHash: public Ppmc {
public:
	PpmcHash(GeneralStructure* generalStructure);
	virtual ~PpmcHash();



private:
	/**
	 * Agrega un elemento nuevo al archivo de la estructura.
	 * @param clave Es la clave del dato a ingresar.
	 * @param valor Es el valor del dato a ingrear.
	 * @return true si la operación fue exitosa
	 */
	bool insertInStructure(std::string clave, std::string valor) throw (ManagerException);

	/**
	 * Verifica si existe un dato en un bloque. El dato está identificado por la clave que se pasa por parámetro.
	 * @param key Es la clave del dato que se desea hallar.
	 * @return true si ya existe en el HashFile la clave pasada por parametro
	 */
	bool existsElementInStructure(std::string key);

	/**
	 * Busca y retorna un elemento dado su clave.
	 * @param key Es la clave del dato a buscar
	 * @param data Es el StringInputData que representa al dato que contiene la clave a buscar
	 * @return true si la operación fue exitosa
	 */
	bool findInStructure(std::string key, InputData & data) throw (ManagerException);

	/**
	 * Cambia el valor de un key pasado por parámetro.
	 * @param key Es el key al cual se le cambiará el valor.
	 * @param newValue Es el valor nuevo que tomara la clave pasada por parametro.
	 * @return true si la operación fue exitosa
	 */
	bool modifyInStructure(std::string key, std::string newValue) throw (ManagerException);

	/**
	 * Elimina el dato, cuya clave es la pasada por parametro.
	 * @param key Es la clave del dato que se desea borrar.
	 * @return true si la operacion fue exitosa
	 */
	bool removeInStructure(std::string key) throw (ManagerException);

	/**
	 * Imprime la estructura por pantalla.
	 */
	void printStructure();

	/**
	 * Elimina los archivos generados por el hash o el arbol.
	 */
	bool deleteGeneratedFilesInStructure();
};

#endif /* PPMCHASH_H_ */
