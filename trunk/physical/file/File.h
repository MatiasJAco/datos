/*
 * File.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef FILE_H_
#define FILE_H_
#include "Block.h"
#include "FreeBlockFile.h"
#include <fstream>
#include <iostream>

/**
 * Clase encargada de realizar las operaciones del archivo en si
 *
 */
class File
{
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	File();
	~File();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Abre el archivo
	 */
	bool openFile(const std::string fileName);


	bool openFile(const std::string fileName, unsigned int blocksize);

	/**
	 * Crea una instancia de la clase Block, y le reserva un
	 * espacio en disco. Para encontrar la posicion del nuevo bloque
	 * se fija primero en la lista de Bloque liberados para ver si hay algun
	 * espacio libre, en caso contrario mete al final del archivo el bloque.
	 *
	 */
	Block *getNewBlock();

	/**
	 * Guarda el contenido del Bloque pasado por parametro a disco
	 */
	bool saveBlock(Block * bq);

	/**
	 * Elimina el Block de disco. Lo agrega a la lista de bloques libres
	 * para permitir reutilizar el espacio(en archivo no se realiza compactado
	 * de espacio por razones de eficiencia, ya que los archivos pueden ocupar
	 * mucho espacio
	 */
	bool deleteBlock(const unsigned int blockNumber);

	/**
	 * Se le pasa un numero de bloque, con eso calcula la posicion del bloque
	 * en disco, y crea una instancia de la clase Block con su contenido.
	 */
	Block *getBlock(const unsigned int blockNumber);

	/**
	 * Cierra el archivo, libera los FHS, etc
	 */
	bool closeFile();

private:
	bool SaveFileAttributes();

	bool LoadFileAttributes();


private:

	static const unsigned int DEFAULT_BLOCK_SIZE =512;
	/**
	 * Guarda el tamaño del bloque, es necesario para no andar laburando desde
	 * afuera con offsets a los bloques.
	 */
	unsigned int m_blockSize;

	unsigned int m_FileSize;

	unsigned int m_LastBlock;

	unsigned int m_FirstBlockOffset;

	/**
	 * FileHandler del archivo, se mantiene a lo largo de toda la vida de
	 * la clase File
	 */
	std::fstream m_FileHandler;

	std::string m_FileName;

	FreeBlockFile m_FreeBlockFile;

};

#endif /* FILE_H_ */
