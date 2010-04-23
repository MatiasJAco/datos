/*
 * BlockFile.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef BLOCK_FILE_H_
#define BLOCK_FILE_H_
#include "Block.h"
#include "FreeBlockFile.h"
#include "File.h"
#include <fstream>
#include <iostream>

/**
 * Archivo compuesto por bloques.
 * Es el encargado de crear bloques y escribirlos a disco
 *
 */
class BlockFile:public File
{
public:

	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	BlockFile();
	~BlockFile();

	//-------------------------METODOS-----------------------------------//

	//-------------------------OPEN/CLOSE--------------------------------//
	/**
	 * Abre el archivo. Si no existe se crea.
	 * @param fileName nombre del archivo.
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool open(const std::string fileName);

	/**
	 * Abre el archivo y asigna el tamaño de bloque. Si no existe se crea.
	 * @param fileName nombre del archivo.
	 * @param blocksize tamaño de los bloques del archivo
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool open(const std::string fileName, unsigned int blocksize);

	/**
	 * Cierra el archivo, libera los FD, escribe la info de control a
	 * disco antes de cerrar el archivo
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool close();

	//-------------------------BLOCKS----------------------------------//
	/**
	 * Crea una instancia de la clase Block, y le reserva un
	 * espacio en disco. Para encontrar la posicion del nuevo bloque
	 * se fija primero en la lista de Bloque liberados para ver si hay algun
	 * espacio libre, en caso contrario mete al final del archivo el bloque.
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el bloque creado
	 * Los bloques arrancan del 1 en adelante.
	 * @return Block *  Bloque nuevo.Devuelve NULL en caso de error
	 *
	 */
	Block *getNewBlock();

	/**
	 * Guarda el contenido del Bloque pasado por parametro a disco
	 * @param bq bloque a guardar en disco
	 * @return bool true en caso de exito false en caso contrario
	 */
	bool saveBlock(Block * bq);

	/**
	 * Elimina el Block de disco. Lo agrega a la lista de bloques libres
	 * para permitir reutilizar el espacio(en archivo no se realiza compactado
	 * de espacio por razones de eficiencia, ya que los archivos pueden ocupar
	 * mucho espacio
	 * @param blockNumber numero del bloque a eliminar
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool deleteBlock(const unsigned int blockNumber);

	/**
	 * Se le pasa un numero de bloque, con eso calcula la posicion del bloque
	 * en disco, y crea una instancia de la clase Block con su contenido.
	 * Solamente sirve para bloques que ya estan en disco, para bloques nuevos
	 * usar getNewBlock().
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el bloque creado
	 * @param blockNumber numero del bloque a buscar
	 * @return Block * el bloque recuperado. NULL en caso de no encontrarse o
	 * 			presentarse error
	 * @see getNewBlock()
	 */
	Block *getBlock(const unsigned int blockNumber);



private:
	//-----------------------------Headers-----------------------------//
	/**
	 * Escribe la informacion de control del archivo en disco
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool writeHeader();

	/**
	 * Lee la informacion de control del archivo de disco
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool readHeader();


private:

	static const unsigned int DEFAULT_BLOCK_SIZE =512;
	/**
	 * Guarda el tamaÃ±o del bloque, es necesario para no andar laburando desde
	 * afuera con offsets a los bloques.
	 */
	unsigned int m_blockSize;

	/**
	 * Numero del ultimo bloque.
	 */
	unsigned int m_LastBlock;

	/**
	 * Offset debido al header que se agrega en el archivo.
	 * Si se agrega un elemento nuevo al header hay que modificar
	 * el calculo de esta variable
	 */
	unsigned int m_FirstBlockOffset;

	/**
	 * Archivo que contiene los bloques libres, a fin de reutilizar espacio.
	 * Antes de poner un bloque nuevo al final se pregunta si este archivo
	 * tiene algun bloque para usar.
	 */
	FreeBlockFile m_FreeBlockFile;

};

#endif /* FILE_H_ */
