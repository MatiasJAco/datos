/*
 * Ppmc.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMC_H_
#define PPMC_H_

#include <iostream>
#include "stdlib.h"
#include "../logic/structures/GeneralStructure.h"
#include "../logic/exceptions/ManagerException.h"

/**
 * Clase que modela el algoritmo de compresión de PPMC.
 */
class Ppmc {

private:
	GeneralStructure* generalStructure; // Puede ser un hash, o un arbol.

public:

	Ppmc(GeneralStructure* generalStructure);

	virtual ~Ppmc();

	/**
	 * Este metodo se encarga de la compresión.
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param maxContext Es el número de contexto máximo con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	bool compress(std::string path,int maxContext);

	/**
	 * Este metodo se encarga de la decompresión
	 * @param path Es el path donde se encuentra el archivo a decomprimir.
	 * @return Devuelve true si decomprimio correctamente. En caso contrario devuelve false.
	 */
	bool deCompress(const std::string & path);

	/**
	 * Este metodo muestra las estadisticas de la compresión
	 */
	void getStatistics();

private:

	/**
	 * Este metodo se usa recursivamente para ir emitiendo la compresion.
	 */
	void ppmcEmitter(std::string context, char character, int actualContextNumber, int maxContext);

};
#endif /* PPMC_H_ */
