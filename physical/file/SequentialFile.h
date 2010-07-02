/*
 * SequentialFile.h
 *
 *  Created on: 11/06/2010
 *      Author: alex
 */

#ifndef SECUENCIALFILE_H_
#define SECUENCIALFILE_H_
#include <fstream>

#include "../Exception/PhysicalException.h"
#include "File.h"

typedef enum {BINARY, TEXT} dataTypeEnum;
typedef enum {READ_FILE, WRITE_FILE} accessModeEnum;
typedef enum {APPEND_FILE, TRUNCATE_FILE} writeEnum;
/**
 * Implementacion de un archivo secuencial con un buffer interno para realizar operaciones,
 * para reducir la cantidad de operaciones de disco
 */
class SequentialFile: public File {


public:
	static const int DEFAULT_BUFFER_SIZE = 65536;

	SequentialFile(accessModeEnum type);
	virtual ~SequentialFile();

	/**
	 * Abre el archivo. Si no existe se crea.
	 * @param fileName nombre del archivo.
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool open(const std::string fileName);

	/**
	 * Cierra el archivo, libera los FD, etc
	 * @return bool true en caso de exito, false en caso contrario
	 */
	bool close();

	/**
	 * Lee un caracter desde el archivo y lo devuelve
	 * @return char el caracter leido
	 * @throws PhysicalException en caso de error
	 */
	char readChar();

	/**
	 * Lee un caracter desde el archivo y lo devuelve
	 * @return char el caracter leido
	 * @throws PhysicalException en caso de error
	 */
	char readChar(bool &didRead);

	/**
	 * Lee N caracteres desde el archivo
	 * @param stream puntero al array de caracteres en los que se va a guardar lo que se lee. tiene que tener espacio asignado desde afuera
	 * @param ammount cantidad de caracteres a leer
	 * @throws PhysicalException en caso de un error al pasar algun parametro incorrecto
	 */
	bool readNChar(char * stream,unsigned int ammount);

	/**
	 * Escribe un caracter en el archivo
	 * @param c caracter a escribir
	 * @throws PhysicalException en caso de error
	 */
	void writeChar(char c);

	/**
	 * Escribe N caracteres en el archivo.
	 * @param stream puntero al array de caracteres que se va a escribir en el archivo. tiene que tener espacio asignado desde afuera
	 * @param ammount cantidad de caracteres a escribir
	 * @throws PhysicalException en caso de error
	 */
	void writeNChar(const char * c, unsigned int ammount);


	//------------------------------GET/SET---------------------------//
	accessModeEnum getAccessMode() const;

	unsigned int getBufferSize() const;

	dataTypeEnum getInputType() const;

	void setAccessMode(accessModeEnum AccessMode);

	void setBufferSize(unsigned int BufferSize);

	void setInputType(dataTypeEnum InputType);

	void setOverwriteMode(writeEnum mode );

protected:
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

	/**
	 * Carga el buffer con el contenido del archivo
	 */
	void fillBuffer();

	/**
	 * Escribe el contenido del bufer en el archivo, escribe solo hasta m_CurrentPos
	 */
	void writeBuffer();


private:

	/**
	 * Tipo de informacion(binario/texto)
	 */
	dataTypeEnum m_InputType;

	/**
	 * Forma de acceso del archivo (Lectura/Escritura)
	 */
	accessModeEnum m_AccessMode;

	/**
	 * Buffer de caracteres
	 */
	char * m_Buffer;

	/**
	 * Posicion actual dentro del buffer
	 */
	unsigned int m_CurrentPos;

	/**
	 *
	 */
	writeEnum m_doTruncate;

	/**
	 * Tama�o del buffer
	 */
	unsigned int m_BufferSize;

	unsigned int m_AmmountRead;
};

#endif /* SECUENCIALFILE_H_ */
