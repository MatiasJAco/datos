/*
 * ArithmeticCompressor.h
 *
 *  Created on: 16/06/2010
 *      Author: kira
 */

#ifndef ARITHMETICCOMPRESSOR_H_
#define ARITHMETICCOMPRESSOR_H_

#include "../../../physical/file/BitFile.h"
#include "../common/FrequencyTable.h"

#include <cmath>

class ArithmeticCompressor {

public:
	typedef enum {COMPRESSOR,DECOMPRESSOR} Coder;

private:
	//Tamaño en bits de un byte.
	static const unsigned int SIZEBYTE = 8;
	typedef enum {OVERFLOW_BITS,UNDERFLOW_BITS} StateBits;

public:
	/**
	 * Constructor compresor.
	 * @param coder		Tipo de codificador. Compresor o descompresor.
	 * @param fileName	Nombre del archivo comprimido.
	 * 					Si coder = COMPRESSOR entonces se trata del archivo de salida,
	 * 					Si coder = DECOMPRESSOR entonces se trata del archivo de entrada.
	 * @param maxsymbols Precision. Maxima cantidad de simbolos posible.
	 */
	ArithmeticCompressor(Coder coder,const std::string fileName,unsigned int maxsymbols);

	/// Destructor
	virtual ~ArithmeticCompressor();

	/**
	 * Comprime un simbolo determinado, emitiendo el resultado en el archivo de salida.
	 * @param symbol	Simbolo a comprimir.
	 * @param ft		Tabla de frecuencias de simbolos.
	 */
	void compress(short symbol,FrequencyTable& ft);

	/**
	 * Descomprime el archivo de entrada, devolviendo el simbolo correspondiente a la descompresion.
	 * @param ft		Tabla de frecuencias de simbolos.
	 * @return Simbolo resultado de la descompresion.
	 */
	short decompress(FrequencyTable& ft);

private:

	/// Detecta si hubo overflow y guarda los bits de overflow.
	bool overflow();

	/// Detecta si hubo underflow y setea el contador.
	bool underflow();

	/// Codifica los simbolos y emite los bits a la salida.
	bool encode();

	/// Lee bits de la compresion y lo decodifica.
	bool decode();

// Para el manejo de los intervalos de la compresion.
private:
	/**
	 * Devuelve el piso que corresponde a un simbolo determinado dentro del intervalo.
	 * @param symbol	Simbolo.
	 * @param ft		Tabla de frecuencias
	 * @return Piso del simbolo.
	 */
	int getFloor(short symbol,FrequencyTable& ft);
	/**
	 * Devuelve el techo que corresponde a un simbolo determinado dentro del intervalo.
	 * @param symbol	Simbolo.
	 * @param ft		Tabla de frecuencias
	 * @return Techo del simbolo.
	 */
	int getCeil(short symbol,FrequencyTable& ft);

	/**
	 * Devuelve el simbolo que esta asociado al numero dentro de un intervalo.
	 * @param num	Numero dentro del intervalo
	 * @param ft	Tabla de frecuencias
	 * @return Simbolo asociado al numero.
	 */
	short getSymbol(int num,FrequencyTable& ft);

	// Normaliza el piso y el techo
	void normalize(StateBits sb);

// Atributos
private:
	// Archivo a comprimir o archivo comprimido segun Coder.
	BitFile* m_bitFile;

	// Tipo de codificador: Compresor, descompresor.
	Coder m_coder;

	//Cantidad de bits para la maxima representacion de un simbolo.
	unsigned int m_maxbits;

	// Para el manejo de intervalos de la compresion: piso y techo.
	int m_floor;
	int m_ceil;

	// Numero comprimido
	int m_number;

	// Bits de overflow
//	Bit* m_overflow;

	// Contador de overflow;
//	short m_counterOverflow;

	/// Contador de underflow.
	short m_counterUnderflow;
//	short m_nextCounterUnderflow;

	// Mascara de bits en uno segun maxbits.
	int bitmask;


};

#endif /* ARITHMETICCOMPRESSOR_H_ */
