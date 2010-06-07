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
private:




public:

	Ppmc();

	virtual ~Ppmc();

	/**
	 * Este metodo se encarga de la compresión
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param context Es el número de contexto con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	bool compress(std::string path,int context);

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
};
#endif /* PPMC_H_ */
