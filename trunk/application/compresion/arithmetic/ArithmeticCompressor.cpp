/*
 * ArithmeticCompressor.cpp
 *
 *  Created on: 16/06/2010
 *      Author: kira
 */

#include "ArithmeticCompressor.h"

ArithmeticCompressor::ArithmeticCompressor(Coder coder,const std::string fileName,unsigned int maxSymbols)
{
	m_coder = coder;
	m_maxbits = (int)floor(log10(maxSymbols-1)/log10(2)+1);
	bitmask = (int)pow(2,m_maxbits)-1; // Maximo numero que se puede representar.

	m_floor = 0;
	m_ceil = bitmask;

	m_counterUnderflow = 0;

	if (m_coder == COMPRESSOR)
		m_bitFile = new BitFile(WRITE_FILE);
	else
		m_bitFile = new BitFile(READ_FILE);

	m_bitFile->open(fileName);

	if (m_coder == DECOMPRESSOR)
	{
		Bit* bits = new Bit[m_maxbits];
		m_bitFile->readNBits(bits,m_maxbits);
		m_number = ByteConverter::bitsToInt(bits,m_maxbits);
		delete [] bits;
	}
}

ArithmeticCompressor::~ArithmeticCompressor() {

	m_bitFile->close();
	delete m_bitFile;
}

void ArithmeticCompressor::compress(short symbol,FrequencyTable & ft)
{
	int newFloor = getFloor(symbol,ft);
	int newCeil = getCeil(symbol,ft);

	m_floor = newFloor;
	m_ceil = newCeil;

	encode();
}

short ArithmeticCompressor::decompress(FrequencyTable& ft)
{
	short symbol = getSymbol(m_number,ft);

	if (symbol != EOF_CHAR)
	{
		// Actualizo el piso y el techo.
		int newFloor = getFloor(symbol,ft);
		int newCeil = getCeil(symbol,ft);

		m_floor = newFloor;
		m_ceil = newCeil;

		decode();
	}

	return symbol;
}


void ArithmeticCompressor::normalize(StateBits sb)
{
	// Si se llama a normalizar el overflow y hay overflow
	if ((sb == OVERFLOW_BITS)&&overflow())
	{
		// Normalizo el piso y el techo
		m_floor = (m_floor << 1)&bitmask;
		m_ceil = ((m_ceil << 1)|1)&bitmask;
	}

	// Si se llama a normalizar el underflow y hay underflow.
	if ((sb == UNDERFLOW_BITS)&&underflow())
	{
		// Normalizo el piso y el techo.
		m_floor = (m_floor << 1)&(bitmask >> 1);
		m_ceil = ((m_ceil<< 1)&bitmask)|(1<< (m_maxbits-1));
		m_ceil = m_ceil|1;
	}
}

bool ArithmeticCompressor::encode()
{
	Bit bit;

	while (overflow())
	{
		// Obtengo el primer bit y lo emito.
		bit = (m_floor >> (m_maxbits-1))?ONE:ZERO;
		m_bitFile->write(bit);

		while (m_counterUnderflow>0)
		{
			// Escribo el primer bit de overflow negado, en el archivo.
			if (bit&ONE)
				m_bitFile->write(ZERO);
			else
				m_bitFile->write(ONE);

			--m_counterUnderflow;
		}

		normalize(OVERFLOW_BITS);
	}

	while (underflow())
	{
		// Incremento contador de underflow.
		++m_counterUnderflow;

		// Normalizo piso y techo
		normalize(UNDERFLOW_BITS);
	}

	return true;
}

bool ArithmeticCompressor::decode()
{
	Bit bit;

	while (overflow())
	{
		normalize(OVERFLOW_BITS);

		// Quito 1 bit del inicio y leo un bit mas del archivo.
		m_number = (m_number<<1)&bitmask;
		bit = m_bitFile->read();

		if (bit&ONE)
			m_number = m_number|1;
	}

	while (underflow())
	{
		normalize(UNDERFLOW_BITS);

		// Quito el segundo bit y leo un bit mas del archivo.
		m_number = ((m_number<< 1)&bitmask)|(1<< (m_maxbits-1));
		bit = m_bitFile->read();

		if (bit&ONE)
			m_number = m_number|1;
	}

	return true;
}

bool ArithmeticCompressor::overflow()
{
	bool bret = false;

	// Miro el primer bit.
	int posbits = m_maxbits-1;

	// si coinciden
	if (m_floor >> posbits == m_ceil >> posbits)
	{
		bret = true;
	}

	return bret;
}

bool ArithmeticCompressor::underflow()
{
	bool bret = false;

	// Miro los dos primeros bits
	int posbits = m_maxbits-2;

	// Si piso = 01... y techo = 10...
	if ((m_floor >> posbits == 1)&&(m_ceil >> posbits == 2))
		bret = true;

	return bret;
}

int ArithmeticCompressor::getFloor(short symbol,FrequencyTable& ft)
{
	// Piso truncado.
	int tfloor = 0;

	int sizeInterval = m_ceil - m_floor +1;

	// el piso es en base al acumulado del caracter inmediatamente menor,
	// resto la frecuencia del mismo.
	double coef = (double)(ft.getCumFrequency(symbol)-ft.getFrequency(symbol))/ft.getFrequencyTotal();
	tfloor = m_floor + (int)floor(coef*sizeInterval);

	return tfloor;
}

int ArithmeticCompressor::getCeil(short symbol,FrequencyTable& ft)
{
	// Techo truncado.
	int tceil = 0;

	int sizeInterval = m_ceil - m_floor +1;

	// el piso es en base al acumulado del caracter.
	double coef = (double)ft.getCumFrequency(symbol)/ft.getFrequencyTotal();
	tceil = m_floor + (int)floor(coef*sizeInterval)-1;

	return tceil;
}

short ArithmeticCompressor::getSymbol(int num,FrequencyTable& ft)
{
	short symbol = UNDEFINED_CHAR;

	int sizeInterval = m_ceil - m_floor +1;

	double coef = (double)(num-m_floor+1)/sizeInterval;
	unsigned long freq = floor(ft.getFrequencyTotal()*coef);

	symbol = ft.getChar(freq);

	return symbol;
}
