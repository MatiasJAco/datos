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
 * Clase que modela el algoritmo de compresión de PPMC e implementa funciones comunes
 * para el PPMCHASH y PPMCTREE
 */
class Ppmc {
private:
	GeneralStructure * generalStructure;

protected:

	/**
	 * Obtiene el String del contexto que se le pasa como parametro. Ej: "DIV", "IVI" para sizeOfContext 3.
	 * Es decir, busca desde actualPositionInFile para atras sizeOfContext cantidad de posiciones en el file
	 * y retorna ese string, para poder guardarlo en la estructura
	 * @param sizeOfContext Es el tamaño del contexto a buscar
	 * @param actualPositionInFile Es la posición actual del caracter que lei ultimo en el archivo
	 * @return Retorna el string del contexto con el tamaño deseado
	 */
	char* getStringContext(int sizeOfContext,int actualPositionInFile);
	//TODO: ver si no hay que borrar este metodo getStringContexts

public:

	//Ppmc();

	Ppmc(GeneralStructure* generalStructure);

	virtual ~Ppmc();

	/**
	 * Este metodo se encarga de la compresión.
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param maxContext Es el número de contexto máximo con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool compress(std::string path,int maxContext) = 0;

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




	/**
	 * Guarda en la estructura un nuevo contexto.
	 * @param context Es el nombre del contexto. Por ejemplo "DIV".
	 * @return Devuelve 0 si pudo guardar el contexto, o un numero distinto de cero en caso de no poder.
	 */
	int createContext(std::string context);

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
	 * Busca si existe la letra del contexto dado, en la tabla del PPMC (que está guardada en la estructura).
	 * @param context Es el contexto a buscar en la tabla de estadisticas del PPMC.
	 * @param character Es el caracter a encontrar en el contexto pasado por parámetro.
	 * @return Devuelve true si lo encontro. En caso contrario devuelve false.
	 */
	bool existsCharacterInContext(std::string context, std::string character);


private:

	/**
	 * Convierte una cadena a mayusculas.
	 * @param s La cadena a pasar a mayusculas.
	 */
	void stoupper(std::string& s);

};
#endif /* PPMC_H_ */
