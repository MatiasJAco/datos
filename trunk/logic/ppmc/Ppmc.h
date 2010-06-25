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
#include "../../application/compresion/common/FrequencyTable.h"
#include "../../application/compresion/arithmetic/ArithmeticCompressor.h"

/**
 * Clase que modela el algoritmo de compresión de PPMC.
 */
class Ppmc {

private:
	/// Default del caracter del contexto 0
	static const std::string ZERO_CONTEXT;
	static const std::string MINUS_ONE_CONTEXT;

protected:
	GeneralStructure* generalStructure; // Puede ser un hash, o un arbol.
	FrequencyTable* minusOneCtxtFreqTable; // Contexto -1.

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
	 * Este metodo obtiene una tabla de frecuencias, dado un contexto.
	 * @param stringContext Es el contexto para el cual se quiere obtener su tabla de frecuencias.
	 * @param newRead Indica si se acaba de leer un nuevo caracter o si se esta retrocediendo en contextos
	 * @return Devuelve la tabla de frecuencias del contexto pasado por parámetro.
	 */
	FrequencyTable* getFrequencyTable(std::string stringContext,bool newRead);

	/**
	 * Este metodo se usa recursivamente para ir emitiendo la compresion.
	 * @param context Es el contexto en donde quiero emitir
	 * @param character Es el caracter que quiero emitir
	 * @param actualContextNumber Es el numero de contexto actual
	 * @param maxContext Es el maximo contexto para la compresion
	 * @param newRead Indica si se acaba de leer un nuevo caracter o si se esta retrocediendo en contextos
	 */
	void ppmcCompressionEmitter(std::string context, char character, int actualContextNumber, int maxContext,bool newRead);

	/**
	 * Este metodo se usa recursivamente para ir actualizando las tablas de frecuencia
	 * @param context Es el contexto en donde quiero emitir
	 * @param character Es el caracter que quiero emitir
	 * @param actualContextNumber Es el numero de contexto actual
	 * @param maxContext Es el maximo contexto para la compresion
	 */
	void updateFrequencyTables(std::string context, char character, int actualContextNumber, int maxContext);

protected:

	/**
	 * Agrega un elemento nuevo al archivo de la estructura.
	 * @param clave Es la clave del dato a ingresar.
	 * @param valor Es el valor del dato a ingrear.
	 * @return true si la operación fue exitosa
	 */
	virtual bool insertInStructure(std::string clave, std::string valor) throw (ManagerException) = 0;

	/**
	 * Verifica si existe un dato en un bloque. El dato está identificado por la clave que se pasa por parámetro.
	 * @param key Es la clave del dato que se desea hallar.
	 * @return true si ya existe en el HashFile la clave pasada por parametro
	 */
	virtual bool existsElementInStructure(std::string key) = 0;

	/**
	 * Busca y retorna un elemento dado su clave.
	 * @param key Es la clave del dato a buscar
	 * @param data Es el StringInputData que representa al dato que contiene la clave a buscar
	 * @return true si la operación fue exitosa
	 */
	virtual bool findInStructure(std::string key, InputData & data) throw (ManagerException) = 0;

	/**
	 * Cambia el valor de un key pasado por parámetro.
	 * @param key Es el key al cual se le cambiará el valor.
	 * @param newValue Es el valor nuevo que tomara la clave pasada por parametro.
	 * @return true si la operación fue exitosa
	 */
	virtual bool modifyInStructure(std::string key, std::string newValue) throw (ManagerException) = 0;

	/**
	 * Elimina el dato, cuya clave es la pasada por parametro.
	 * @param key Es la clave del dato que se desea borrar.
	 * @return true si la operacion fue exitosa
	 */
	virtual bool removeInStructure(std::string key) throw (ManagerException) = 0;

	/**
	* Busca y retorna un elemento dado su clave, en caso del arbol aprovechando sequence set.
	* @param key Es la clave del dato a buscar
	* @param data Es el StringInputData que representa al dato que contiene la clave a buscar
	* @return true si la operación fue exitosa
	*/
	virtual bool getNextContext(std::string key, InputData & data) throw (ManagerException);
};
#endif /* PPMC_H_ */
