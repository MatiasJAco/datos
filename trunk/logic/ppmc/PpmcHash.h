/*
 * PpmcHash.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMCHASH_H_
#define PPMCHASH_H_

#include "Ppmc.h"
#include "../logic/hash/Hash.h"

class PpmcHash: public Ppmc {

private:

	/* El hash se usa para guardar las tablas de estadisticas del algoritmo de compresion. */
	Hash* hash;

	/**
	 * Guarda en el Hash la clave context y el valor value
	 * @param context Es la clave a guardar en la estructura
	 * @param value Es el valor a guardar en la estructura
	 * @return Devuelve 0 si pudo guardar el contexto, o un numero distinto de cero en caso de no poder.
	 */
	int saveContext(const char* context, std::string value);

	/**
	 * Busca en el Hash la clave context y devuelve el valor value
	 * @param context Es la clave a buscar en la estructura
	 * @param character Es el caracter "dado character"
	 * @param value Es el valor de la clave (la probabilidad). Este valor lo devuelve
	 * @return Devuelve true si lo encontro. En caso contrario devuelve false.
	 */
	bool findContext(const char* context, char character, std::string & value);

public:
	PpmcHash();
	virtual ~PpmcHash();

	/**
	 * Este metodo crea un nuevo contexto y lo guarda.
	 * @param context Es una cadena que representa el contexto.
	 * @param letter Es la letra leida luego del contexto.
	 * @return Devuelve 0 si se pudo crear y guardar el contexto o un numero distinto a 0 si hubo un error.
	 */
	int generateContext(std::string context, std::string letter);

	/**
	 * Convierte una cadena a mayusculas.
	 * @param s La cadena a pasar a mayusculas.
	 */
	void stoupper(std::string& s);

	/**
	 * Este metodo devuelve el numero que le corresponde a una letra.
	 * @param letter Es la letra sobre la cual se quiere averiguar su numero.
	 * @return Devuelve el numero correspondiente de la letra.
	 * 		   Por ejemplo, para la A seria el 0, para la E seria el 4.
	 */
	int getNumberForLetter(std::string letter);

	/**
	 * Este metodo se encarga de la compresión.
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param context Es el número de contexto con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool compress(std::string path,int context);

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
