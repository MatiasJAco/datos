/*
 * File.h
 *
 *  Created on: 22/04/2010
 *      Author: alex
 */
#ifndef FILE_H_
#define FILE_H_

#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>

/**
 * Clase abstracta de la cual derivan los archivos
 * Provee una interfaz basica para los distintos tipos de archivos
 */
class File
{
public:
	File();
	virtual ~File();

	/**
	 * Abre el archivo. Si no existe se crea.
	 * @param fileName nombre del archivo.
	 * @return bool true en caso de exito, false en caso contrario
	 */
	virtual bool open(const std::string fileName)=0;

	/**
	 * Cierra el archivo, libera los FD, etc
	 * @return bool true en caso de exito, false en caso contrario
	 */
	virtual bool close()=0;

	/**
	 * Corta la longitud del archivo
	 * @return true en caso de ok, false en caso contrario
	 */
	bool resize(unsigned int size);

	/**
	 * Elimina el archivo.
	 * @return true en caso de ok, false en caso contrario
	 */
	virtual bool deleteFile();


protected:
	//-----------------------------Headers-----------------------------//
	/**
	 * Escribe la informacion de control del archivo en disco
	 * @return bool true en caso de exito, false en caso contrario
	 */
	virtual bool writeHeader()=0;

	/**
	 * Lee la informacion de control del archivo de disco
	 * @return bool true en caso de exito, false en caso contrario
	 */
	virtual bool readHeader()=0;

protected:
	/**
	 * FileHandler del archivo, se mantiene a lo largo de toda la vida de
	 * la clase BlockFile
	 */
	std::fstream m_FileHandler;

	/**
	 * Nombre del archivo
	 */
	std::string m_FileName;

	/**
	 * Tamaño fisico del archivo
	 */
	unsigned int m_FileSize;
};

#endif /* FILE_H_ */
