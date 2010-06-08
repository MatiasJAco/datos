/*
 * PpmcTree.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMCTREE_H_
#define PPMCTREE_H_

#include "Ppmc.h"

class PpmcTree: public Ppmc {

private:

	/**
	 * Guarda en el Arbol la clave context y el valor value
	 * @param context Es la clave a guardar en la estructura
	 * @param value Es el valor a guardar en la estructura
	 * @return Devuelve true si lo guardo correctamente. En caso contrario devuelve false.
	 */
	bool saveContext(const char* context, std::string value);

	/**
	 * Busca en el Arbol la clave context y devuelve el valor value
	 * @param context Es la clave a buscar en la estructura
	 * @param character Es el caracter "dado character"
	 * @param value Es el valor de la clave (la probabilidad). Este valor lo devuelve
	 * @return Devuelve true si lo encontro. En caso contrario devuelve false.
	 */
	bool findContext(const char* context, char character, std::string & value);


public:

	PpmcTree();
	virtual ~PpmcTree();

};

#endif /* PPMCTREE_H_ */
