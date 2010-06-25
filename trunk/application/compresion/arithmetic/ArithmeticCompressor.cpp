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
	m_maxbits = (int)floor(log10(maxSymbols)/log10(2)+1);

	m_floor = 0;
	m_roof = maxSymbols;

	if (m_coder == COMPRESSOR)
		m_bitFile = new BitFile(WRITE_FILE);
	else
		m_bitFile = new BitFile(READ_FILE);

	m_overflow = new Bit[m_maxbits];
	m_bitFile->open(fileName);
}

ArithmeticCompressor::~ArithmeticCompressor() {

	delete m_overflow;

	m_bitFile->close();
	delete m_bitFile;
}

void ArithmeticCompressor::compress(short symbol,FrequencyTable & ft)
{
	m_floor = getFloor(symbol,ft);
	m_roof = getCeil(symbol,ft);

	normalize();

	emit();
}

short ArithmeticCompressor::decompress(FrequencyTable& ft)
{


	return 0;
}

void ArithmeticCompressor::normalize()
{
	int posBit = m_maxbits;

	// Si hay overflow (entre piso y techo).
	while (overflow()&&(posBit>0))
	{
		// Obtengo el primer bit y lo guardo.
		m_overflow[posBit] = (m_floor >> (m_maxbits-1))?ONE:ZERO;
		++m_counterOverflow;

		// Normalizo el piso y el techo
		m_floor = (m_floor << 1);
		m_roof = (m_roof << 1)|1;

		--posBit;
	}

	while (underflow())
	{
		int bitmask = (~0 >> (sizeof(m_floor)*SIZEBYTE -m_maxbits));
		// Incremento contador de underflow
		++m_counterUnderflow;

		// Normalizo el piso y el techo.
		m_floor = (m_floor << 1)&(bitmask >> 1);
		m_roof = (m_roof << 1)| (1<< (m_maxbits-1)|1);
	}
}

bool ArithmeticCompressor::emit()
{
	int posBit = m_maxbits;
	Bit bit;

	// Si hay algo en el contador de overflow;
	while (m_counterOverflow>0)
	{
		bit = m_overflow[posBit];
		m_bitFile->write(bit);

		while(m_counterUnderflow>0)
		{
			// Escribo el primer bit de overflow negado, en el archivo.
			if (bit&ONE)
				m_bitFile->write(ZERO);
			else
				m_bitFile->write(ONE);

			--m_counterUnderflow;
		}

		--posBit;
		--m_counterOverflow;
	}

	return true;
}

bool ArithmeticCompressor::overflow()
{
	bool bret = false;

	// Miro el primer bit.
	int posbits = m_maxbits-1;

	// si coinciden
	if (m_floor >> posbits == m_roof >> posbits)
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
	if ((m_floor >> posbits == 1)&&(m_roof >> posbits == 2))
		bret = true;

	return bret;
}

int ArithmeticCompressor::getFloor(short symbol,FrequencyTable& ft)
{
	// Piso truncado.
	int tfloor = 0;

	int sizeInterval = m_roof - m_floor +1;

	// el piso es en base al acumulado del caracter inmediatamente menor,
	// resto la frecuencia del mismo.
	double coef = (ft.getCumFrequency(symbol)-ft.getFrequency(symbol))/ft.getFrequencyTotal();
	tfloor = m_floor + (int)floor(coef*sizeInterval);

	return tfloor;
}

int ArithmeticCompressor::getCeil(short symbol,FrequencyTable& ft)
{
	// Techo truncado.
	int tceil = 0;

	int sizeInterval = m_roof - m_floor +1;

	// el piso es en base al acumulado del caracter.
	double coef = ft.getCumFrequency(symbol)/ft.getFrequencyTotal();
	tceil = m_floor + (int)floor(coef*sizeInterval)-1;

	return tceil;
}

short ArithmeticCompressor::getSymbol(int num,FrequencyTable& ft)
{
	return 0;
}

