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

#include <math.h>

class ArithmeticCompressor {

public:
	typedef enum {COMPRESSOR,DECOMPRESSOR} Coder;

public:
	/**
	 * Constructor compresor.
	 * @param coder		Tipo de codificador. Compresor o descompresor.
	 * @param fileName	Nombre del archivo comprimido.
	 * 					Si coder = COMPRESSOR entonces se trata del archivo de salida,
	 * 					Si coder = DECOMPRESSOR entonces se trata del archivo de entrada.
	 * @param maxbits	Precision. Maxima cantidad de bits para la representacion de un simbolo.
	 */
	ArithmeticCompressor(Coder coder,const std::string fileName,unsigned int maxbits);

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

	/// Emite los bits a la salida.
	// 	PROBABLEMENTE CAMBIAR EL PROTOTIPO DE ESTE METODO.
	bool emit();

// Para el manejo de los intervalos de la compresion.
private:
	/**
	 * Devuelve el piso que corresponde a un simbolo determinado dentro del intervalo.
	 * @param symbol	Simbolo.
	 * @param ft		Tabla de frecuencias
	 * @return Piso del simbolo.
	 */
	int getFloorSymbol(short symbol,FrequencyTable& ft);
	/**
	 * Devuelve el techo que corresponde a un simbolo determinado dentro del intervalo.
	 * @param symbol	Simbolo.
	 * @param ft		Tabla de frecuencias
	 * @return Techo del simbolo.
	 */
	int getRoofSymbol(short symbol,FrequencyTable& ft);

	/**
	 * Devuelve el simbolo que esta asociado al numero dentro de un intervalo.
	 * @param num	Numero dentro del intervalo
	 * @param ft	Tabla de frecuencias
	 * @return Simbolo asociado al numero.
	 */
	int getSymbol(int num,FrequencyTable& ft);

	// Normaliza el piso y el techo
	void normalize();

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
	int m_roof;

	/// Contiene los bits de overflow
	short m_bitsOverflow;

	/// Contador de underflow.
	short m_counterUnderflow;
};

#endif /* ARITHMETICCOMPRESSOR_H_ */
