/*
 * BitFile.h
 *
 *  Created on: 14/06/2010
 *      Author: kira
 */

#ifndef BITFILE_H_
#define BITFILE_H_

#include <bitset>
#include "SequentialFile.h"
#include "../utils/ByteConverter.h"

/**
 * Clase para el manejo de escritura y lectura de bits sobre un archivo.
 *
 */
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
	 * Escribe una tira de bits en el archivo.
	 * @param bits Tira de bits a escribir.
	 * @param nbits Cantidad de bits en la tira.
	 * @return TRUE en caso de exito. FALSE de lo contrario.
	 */
	bool writeNBits(Bit bits[],int nbits)throw (PhysicalException);

	/**
	 * Lee del archivo un bit.
	 * @return bit leido.
	 */
	Bit read() throw (PhysicalException);

	/**
	 * Lee una tira de bits y lo guarda en el arreglo pasado por param.
	 * @param bits Tira de bits donde se guarda el arreglo levantado al leer.
	 * @param nbits Cantidad de bits a leer.
	 * @return TRUE en caso de exito. FALSE de lo contrario.
	 */
	bool readNBits(Bit bits[],int nbits) throw (PhysicalException);



private:

	// Escribe en el archivo un bit uno.
	void writeBitOne() throw (PhysicalException);

	// Escribe en el archivo un bit cero.
	void writeBitZero()throw (PhysicalException);

	// Lee el buffer.
	void readBuffer() throw (PhysicalException);

	// Limpia el buffer
	bool clearBuffer();


private:
	// Usa buffer del tamaño de un byte (8 bits). (ARCHIVOS ASCII).
	static const int SIZE_BUFFER = 8;

private:
	// Archivo de bytes (char)
	SequentialFile* m_byteFile;

	// Buffer maximo de 4 bytes.(Implementacion para 1 byte)
	int m_buffer;

	// Posicion del siguiente bit
	int m_posBit;

};

#endif /* BITFILE_H_ */
