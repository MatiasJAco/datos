/*
 * PpmcHash.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMCHASH_H_
#define PPMCHASH_H_

#include "Ppmc.h"
#include "../logic/structures/hash/Hash.h"

/**
 * Clase que modela el algoritmo de compresión de PPMC con almacenamiento de la tabla en un Hash
 * usando metodos comunes implementados en la clase padre PPMC
 */
class PpmcHash: public Ppmc {

private:

	/* El hash se usa para guardar las tablas de estadisticas del algoritmo de compresion. */
	Hash* hash;

	/**
	 * Este metodo se usa recursivamente para ir emitiendo la compresion.
	 */
	void ppmcEmitter(std::string context, char character, int actualContextNumber, int maxContext);

public:
	PpmcHash();
	virtual ~PpmcHash();

	/**
	 * Este metodo se encarga de la compresión.
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param maxContext Es el número de contexto máximo con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool compress(std::string path,int maxContext);

	/**
	 * Este metodo se encarga de la decompresión
	 * @param path Es el path donde se encuentra el archivo a decomprimir.
	 * @return Devuelve true si decomprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool deCompress(const std::string & path);

	/**
	 * Este metodo muestra las estadisticas de la compresión
	 */
	virtual void getStatistics();
};

#endif /* PPMCHASH_H_ */
