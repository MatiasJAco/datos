/*
 * File.cpp
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#include "File.h"
using namespace std;

File::File()
{
	m_blockSize=0;
}

File::~File()
{
	closeFile();
}

bool File::deleteBlock(const unsigned int blockNumber)
{
	return true;
}

bool File::openFile(const std::string fileName, unsigned int blocksize)
{
	m_blockSize=blocksize;
	return openFile(fileName);
}

bool File::openFile(const std::string fileName)
{
	bool retVal=false;

	//Si ya estaba abierto lo cierro
	if(m_FileHandler.is_open())
		m_FileHandler.close();

	//Me guardo el nombre del archivo
	m_FileName=fileName;

	//Abro el archivo en modo lectura/escritura binaria
	m_FileHandler.open (fileName.c_str(),ios::in | ios::out | ios::binary);

	//Me fijo si lo abrio exitosamente
	if(m_FileHandler.is_open())
		retVal=true;

	m_FileHandler.put('a');
	return retVal;
}



Block File::getNewBlock()
{
	Block e(3);
	return e;
}



Block File::getBlock(const unsigned int blockNumber)
{
	Block e(3);
	return e;
}



bool File::closeFile()
{
	if(!m_FileHandler.is_open())
		m_FileHandler.close();

	return true;
}



bool File::saveBlock(Block & bq)
{
	return true;
}


