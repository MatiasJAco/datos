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
	bool retVal=true;

	//Si ya estaba abierto lo cierro
	if(m_FileHandler.is_open())
		m_FileHandler.close();

	//Me guardo el nombre del archivo
	m_FileName=fileName;

	//Se abre el archivo en modo escritura unicamente para crearlo si no existe.
	//Si no existe y lo abro en modo lectura se presenta un error. El append se
	//agrega para que no trunque el archivo
	m_FileHandler.open (fileName.c_str(), ios::out|ios::binary|ios::app);
	m_FileHandler.close();

	if(!m_FreeBlockFile.open(m_FileName))
	{
		retVal=false;
	}

	//Abro el archivo en modo lectura/escritura binaria
	m_FileHandler.open (fileName.c_str(),ios::in | ios::out| ios::binary);

	if(!m_FreeBlockFile.open(m_FileName))
		retVal=false;

	//Me fijo si lo abrio exitosamente
	if(!m_FileHandler.is_open())
		retVal=false;



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
	if(m_FileHandler.is_open())
		m_FileHandler.close();

	return true;
}



bool File::saveBlock(Block & bq)
{
	return true;
}


