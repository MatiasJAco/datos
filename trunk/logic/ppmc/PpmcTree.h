/*
 * PpmcTree.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMCTREE_H_
#define PPMCTREE_H_

#include "Ppmc.h"
#include "../logic/input/StringInputData.h"
#include "../logic/structures/tree/BPlusTree.h"
#include "stdlib.h"


/**
 * Clase que modela el algoritmo de compresión de PPMC con almacenamiento de la tabla en un Arbol
 * usando metodos comunes implementados en la clase padre PPMC
 */
class PpmcTree: public Ppmc {

private:
	/* El arbol que se usa para guardar las tablas de estadisticas del algoritmo de compresion. */
		BPlusTree* tree;

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
	/**
	* Guarda en el arbol un nuevo contexto.
	* @param context Es el nombre del contexto. Por ejemplo "DIV".
	* @return Devuelve 0 si pudo guardar el contexto, o un numero distinto de cero en caso de no poder.
	*/
	int createContext(std::string context);

	/**
	* Busca si existe la letra del contexto dado, en la tabla del PPMC (que está guardada en el arbol).
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

	//Muestra por pantalla la estructura que contiene los contextos.
	//TODO Se usa para debugging, ver si se deja al final.
	void showContexts();

	PpmcTree();
	virtual ~PpmcTree();

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

#endif /* PPMCTREE_H_ */
