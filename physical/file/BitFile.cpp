/*
 * BitFile.cpp
 *
 *  Created on: 14/06/2010
 *      Author: kira
 */

#include "BitFile.h"

BitFile::BitFile(accessModeEnum type) {
	m_byteFile = new SequentialFile(type);

	if (type == WRITE_FILE)
		clearBuffer();
	else
		readBuffer();
}

BitFile::~BitFile() {
	delete m_byteFile;
}


bool BitFile::open(const std::string fileName)
{
	return m_byteFile->open(fileName);
}


bool BitFile::close()
{
	return m_byteFile->close();
}

void BitFile::write(Bit bit) throw (PhysicalException)
{
	if (bit&ONE)
		writeBitOne();
	else
		writeBitZero();
}

Bit BitFile::read() throw (PhysicalException)
{
	Bit bit = ZERO;

	if (m_posBit == 0)
	{
		if (m_buffer&1)
			bit = ONE;
		readBuffer();
	}
	else
	{
		if (m_buffer&(1 << m_posBit))
			bit = ONE;
		m_posBit--;
	}

	return bit;
}


void BitFile::readBuffer() throw (PhysicalException)
{
	m_buffer = m_byteFile->readChar();
	m_posBit = SIZE_BUFFER-1;
}

bool BitFile::clearBuffer()
{
	bool bret = true;

	m_buffer = 0;
	m_posBit = SIZE_BUFFER-1;

	return bret;
}


void BitFile::writeBitOne() throw (PhysicalException)
{
	if (m_posBit == 0)
	{
		m_byteFile->writeChar((char)(m_buffer+1));
		clearBuffer();
	}
	else
	{
		m_buffer = (m_buffer+1)<< 1;
		m_posBit--;
	}
}



void BitFile::writeBitZero() throw (PhysicalException)
{
	if (m_posBit == 0)
	{
		m_byteFile->writeChar((char)m_buffer);
		clearBuffer();
	}
	else
	{
		m_buffer = m_buffer << 1;
		m_posBit--;
	}
}



