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

/**
 * Clase que modela el algoritmo de compresión de PPMC con almacenamiento de la tabla en un Hash
 * usando metodos comunes implementados en la clase padre PPMC
 */
class PpmcHash: public Ppmc {

private:

	/* El hash se usa para guardar las tablas de estadisticas del algoritmo de compresion. */
	Hash* hash;

	/**
	 * Convierte una cadena a mayusculas.
	 * @param s La cadena a pasar a mayusculas.
	 */
	void stoupper(std::string& s);

public:
	PpmcHash();
	virtual ~PpmcHash();

	/**
	 * Guarda en el Hash un nuevo contexto.
	 * @param context Es el nombre del contexto. Por ejemplo "DIV".
	 * @return Devuelve 0 si pudo guardar el contexto, o un numero distinto de cero en caso de no poder.
	 */
	int createContext(std::string context);

	/**
	 * Busca si existe la letra del contexto dado, en la tabla del PPMC (que está guardada en el Hash).
	 * @param context Es el contexto a buscar en la tabla de estadisticas del PPMC.
	 * @param character Es el caracter a encontrar en el contexto pasado por parámetro.
	 * @return Devuelve true si lo encontro. En caso contrario devuelve false.
	 */
	bool existsCharacterInContext(std::string context, std::string character);

	/**
	 * Este método agrega un caracter a un contexto.
	 * @param context Es el contexto sobre el cual se agrega el caracter pasado por parámetro.
	 * @param character Es el caracter que se desea agregar al contexto pasado por parámetro.
	 * @return Devuelve 0 si pudo agregar el caracter al contexto, o un número distinto de cero si no pudo.
	 */
	int addCharacterToContext(std::string context, std::string character);

	/**
	 * Aumenta en 1 la ocurrencia del caracter pasado por parámetro, en el contexto pasado por parámetro.
	 * @param character El caracter cuya frecuencia se aumentará en 1.
	 * @param context El contexto en el cual se aumentará la frecuencia del caracter.
	 * @return Devuelve 0 si pudo aumentar la ocurrencia del caracter, o un número distinto de cero si no pudo.
	 */
	int increaseFrequency(std::string context, std::string character);

	/**
	 * Devuelve la cantidad de ocurrencias de un caracter en un contexto.
	 * @param context Es el contexto sobre el cual busca las ocurrencias del caracter dado por parámetro.
	 * @param character Es el caracter al cual se le cuentan las ocurrencias.
	 * @return Devuelve la cantidad de ocurrencias de un caracter en el contexto dado por parámetro.
	 */
	int getCharacterOccurrences(std::string context, std::string character);

	/**
	 * Devuelve la cantidad total de ocurrencias de un contexto.
	 * @param context Es el contexto sobre el cual se pide la cantidad de occurencias que hubo.
	 * @return Devuelve la cantidad total de ocurrencias del contexto pasado por parámetro.
	 */
	int getTotalOccurencesFromContext(std::string context);

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
