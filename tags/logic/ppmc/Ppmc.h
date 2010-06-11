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
 * Clase que modela el algoritmo de compresión de PPMC e implementa funciones comunes
 * para el PPMCHASH y PPMCTREE
 */
class Ppmc {
private:


protected:

	/**
	 * Lee el proximo caracter del archivo a comprimir. Maneja por dentro un
	 * buffer interno.
	 * @param result Es el resultado de la operación: 1 si es fin de archivo, 0 si pudo, o -1 si hubo algun problema.
	 * @return Retorna el caracter deseado.
	 */
	char readNextCharacter( int & result);

	/**
	 * Obtiene el String del contexto que se le pasa como parametro. Ej: "DIV", "IVI" para sizeOfContext 3.
	 * Es decir, busca desde actualPositionInFile para atras sizeOfContext cantidad de posiciones en el file
	 * y retorna ese string, para poder guardarlo en la estructura
	 * @param sizeOfContext Es el tamaño del contexto a buscar
	 * @param actualPositionInFile Es la posición actual del caracter que lei ultimo en el archivo
	 * @return Retorna el string del contexto con el tamaño deseado
	 */
	char* getStringContext(int sizeOfContext,int actualPositionInFile);


public:

	Ppmc();

	virtual ~Ppmc();

	/**
	 * Este metodo se encarga de la compresión.
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
