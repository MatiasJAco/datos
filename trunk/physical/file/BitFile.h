/*
 * BitFile.h
 *
 *  Created on: 14/06/2010
 *      Author: kira
 */

#ifndef BITFILE_H_
#define BITFILE_H_

#include "SequentialFile.h"

typedef enum {ONE,ZERO} Bit;

class BitFile{

public:

	/// Constructor con modo de acceso al archivo.
	BitFile(accessModeEnum type);

	/// Destructor
	virtual ~BitFile();

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
	 * Escribe un bit en el archivo.
	 * @param bit a escribir.
	 */
	void write(Bit bit)throw (PhysicalException);

	/**
	 * Lee del archivo un bit.
	 * @return bit leido.
	 */
	Bit read() throw (PhysicalException);


private:

	// Escribe en el archivo un bit uno.
	void writeBitOne() throw (PhysicalException);

	// Escribe en el archivo un bit cero.
	void writeBitZero()throw (PhysicalException);

	// Lee de a un buffer
	void readBuffer() throw (PhysicalException);

	// Limpia el buffer
	bool clearBuffer();


private:
	// Usa buffer del tamaño de un byte. (ARCHIVOS ASCII).
	static const unsigned int SIZE_BUFFER = sizeof(char);

private:
	// Archivo de bytes (char)
	SequentialFile* m_byteFile;

	// Buffer maximo de 4 bytes.(Implementacion para 1 byte)
	int m_buffer;

	// Posicion del siguiente bit
	int m_posBit;

};

#endif /* BITFILE_H_ */
