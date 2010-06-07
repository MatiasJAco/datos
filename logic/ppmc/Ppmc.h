/*
 * Ppmc.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMC_H_
#define PPMC_H_
#include <iostream>
/**
 * Clase que modela el algoritmo de compresión de PPMC.
 */
class Ppmc {
protected:

	void getPepe();


public:

	Ppmc();

	virtual ~Ppmc();

	/**
	 * Este metodo se encarga de la compresión
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param context Es el número de contexto con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool compress(std::string path,int context) = 0;

	/**
	 * Este metodo se encarga de la decompresión
	 * @param path Es el path donde se encuentra el archivo a decomprimir.
	 * @return Devuelve true si decomprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool deCompress(const std::string & path) = 0;

	/**
	 * Este metodo muestra las estadisticas de la compresión
	 */
	virtual void getStatistics() = 0;
};
#endif /* PPMC_H_ */
