/*
 * SequentialFile.cpp
 *
 *  Created on: 11/06/2010
 *      Author: alex
 */

#include "SequentialFile.h"

using namespace std;

SequentialFile::SequentialFile(accessModeEnum mode) {

	m_AccessMode = mode;
	m_InputType = TEXT;
	m_BufferSize = DEFAULT_BUFFER_SIZE;
	m_Buffer = NULL;
	m_CurrentPos =0;

}

SequentialFile::~SequentialFile() {
	close();

}

bool SequentialFile::close()
{
	bool retVal;

	//Si el modo del archivo es escritura, hago un flush
	if(m_AccessMode == WRITE_FILE)
		writeBuffer();

	if(m_FileHandler.is_open())
		m_FileHandler.close();

	if(m_Buffer!=NULL)
		delete m_Buffer;

	m_Buffer=NULL;

	return retVal;
}

bool SequentialFile::open(const std::string fileName)
{
	bool retVal=false;

	//Si ya estaba abierto lo cierro
	if(m_FileHandler.is_open())
		m_FileHandler.close();

	//Me guardo el nombre del archivo
	m_FileName=fileName;

	//Se abre el archivo en modo escritura unicamente para crearlo si no existe.
	//Si no existe y lo abro en modo lectura se presenta un error. El append se
	//agrega para que no trunque el archivo
	m_FileHandler.open (fileName.c_str(), ios::out|ios::binary|ios::app);
	m_FileSize =m_FileHandler.tellg();
	m_FileHandler.close();

	ios_base::openmode flag;

	//Si es de lectura o lectura/escritura
	if(m_AccessMode != WRITE_FILE)
		flag=ios::in;

	//Si es de escritura o lectura/escritura
	if(m_AccessMode != READ_FILE)
		flag=ios::out|ios::app;

	if(m_InputType==BINARY)
		flag|ios::binary;

	//Abro el archivo en modo lectura/escritura binaria
	m_FileHandler.open (fileName.c_str(),flag);

	if(!m_FileHandler.is_open())
		throw PhysicalException(PhysicalException::ERROR_OPENING_FILE);


	//Si existe el buffer lo elimino
	if(m_Buffer != NULL)
		delete [] m_Buffer;


	m_Buffer = new char[m_BufferSize];
	m_CurrentPos=0;

	if(m_AccessMode==READ_FILE)
		fillBuffer();

	return retVal;
}

bool SequentialFile::writeHeader()
{
	bool retVal=false;
	return retVal;
}


char SequentialFile::readChar()
{
	char  retChar;

	readNChar(&retChar,1);

	return retChar;
}

void SequentialFile::readNChar(char * stream, unsigned int ammount)
{
	if(m_AccessMode == WRITE_FILE)
		throw  PhysicalException(PhysicalException::INVALID_FILE_OPERATION);

	if(stream == NULL)
		throw  PhysicalException(PhysicalException::NULL_POINTER);

	unsigned int i;

	for(i=0; i < ammount; i++)
	{
		if(m_CurrentPos >= m_BufferSize)
		{
			fillBuffer();
			m_CurrentPos =0;
		}

		stream[i] = m_Buffer[m_CurrentPos];
		m_CurrentPos++;
	}


}

void SequentialFile::writeNChar(const char *stream, unsigned int ammount)
{
	if(m_AccessMode == READ_FILE)
		throw  PhysicalException(PhysicalException::INVALID_FILE_OPERATION);

	if(stream == NULL)
		throw  PhysicalException(PhysicalException::NULL_POINTER);



	unsigned int i;

	for(i=0; i < ammount; i++)
	{
		if(m_CurrentPos >= m_BufferSize)
		{
			writeBuffer();
			m_CurrentPos =0;
		}

		m_Buffer[m_CurrentPos]= stream[i];

		m_CurrentPos++;
	}

}

void SequentialFile::fillBuffer()
{
	m_FileHandler.read(m_Buffer, m_BufferSize*sizeof(char));
}

void SequentialFile::writeBuffer()
{
	m_FileHandler.write(m_Buffer, m_CurrentPos*sizeof(char));
}


bool SequentialFile::readHeader()
{
	bool retVal=false;
	return retVal;
}

accessModeEnum SequentialFile::getAccessMode() const
{
    return m_AccessMode;
}

unsigned int SequentialFile::getBufferSize() const
{
    return m_BufferSize;
}

dataTypeEnum SequentialFile::getInputType() const
{
    return m_InputType;
}

void SequentialFile::setAccessMode(accessModeEnum AccessMode)
{
    this->m_AccessMode = AccessMode;
}

void SequentialFile::setBufferSize(unsigned int BufferSize)
{
    this->m_BufferSize = BufferSize;
}

void SequentialFile::setInputType(dataTypeEnum InputType)
{
    this->m_InputType = InputType;
}




