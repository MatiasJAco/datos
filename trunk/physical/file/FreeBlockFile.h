/*
 * FreeBlockFile.h
 *
 *  Created on: 15/04/2010
 *      Author: alex
 */

#ifndef FREEBLOCKFILE_H_
#define FREEBLOCKFILE_H_
#include <iostream>
#include <fstream>
#include "FixedRegister.h"
#include "../utils/ByteConverter.h"

/**
 * Clase encargada de manejar los bloques libres para nuestro archivo.
 * Guarda una pila con los bloques liberados en disco
 * Los bloques se almacenan como unsigned int
 * Se guarda internamente la cantidad de bloques libres dentro del archivo
 * TODO ver si hacer truncate
 */
class FreeBlockFile
{
public:
	FreeBlockFile();
	~FreeBlockFile();

	/**
	 * Abre el archivo de bloques libres
	 * @param filename nombre archivo = <filename>.free
	 * @return bool false en caso de error, true en caso ok
	 */
	bool open(const std::string filename);

	/**
	 * Cierra el archivo
	 * @return bool true siempre (esta por uniformidad)
	 */
	bool close();

	/**
	 * Pongo un numero de bloque al final del archivo
	 * Incrementa el contador de bloques
	 * @param numblock valor a ingresar
	 * @return bool true en caso ok false en fallo
	 */
	bool pushFreeBlock(const unsigned int numblock);

	/**
	 * Recupera el ultimo valor del archivo, en caso que no haya valores que devolver
	 * retorna false. Decrementa el contador de elementos. No reduce el tamaño del archivo
	 * @param numblock variable en la cual se devuelve el valor de numero de bloque
	 * @return bool true si recupero ok, false en caso de error o no haber elementos
	 */
	bool popFreeBlock(unsigned int &numblock);


	void showFreeNodes();

private:

	/**
	 * Lee del archivo el numero de bloques
	 * @param blockCount cantidad de bloques en el archivo de bloques libres
	 * @return bool true si esta ok false caso contrario
	 */
	bool readBlockCount(unsigned int & blockCount);
	/**
	 * Escribe en el archivo el numero de bloques
	 * @param blockCount cantidad de bloques en el archivo de bloques libres
	 * @return bool true si esta ok false caso contrario
	 */
	bool writeBlockCount(const unsigned int blockCount);


private:

	/**
	 * FH del archivo
	 */
	std::fstream m_FileHandler;

	/**
	 * Nombre del archivo
	 */
	std::string m_FileName;

	/**
	 * Tamaño fisico del archivo
	 */
	unsigned int m_fileSize;

	/**
	 * Cantidad de bloques en el archivo de bloques libres
	 */
	unsigned int m_BlockCount;

	/**
	 * Tamaño que ocupa cada uno de los registros de bloque libre
	 */
	unsigned int m_registerSize;

};

#endif /* FREEBLOCKFILE_H_ */
