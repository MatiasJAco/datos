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
	m_FirstBlockOffset=sizeof(unsigned int);
	m_blockSize=DEFAULT_BLOCK_SIZE;

}

File::~File()
{
	closeFile();
}

bool File::deleteBlock(const unsigned int blockNumber)
{
	return m_FreeBlockFile.pushFreeBlock(blockNumber);
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

	//Se abre el archivo en modo escritura unicamente para crearlo si no existe.
	//Si no existe y lo abro en modo lectura se presenta un error. El append se
	//agrega para que no trunque el archivo
	m_FileHandler.open (fileName.c_str(), ios::out|ios::binary|ios::app);
	m_FileSize =m_FileHandler.tellg();
	m_FileHandler.close();

	if(m_FreeBlockFile.open(m_FileName))
	{
		//Abro el archivo en modo lectura/escritura binaria
		m_FileHandler.open (fileName.c_str(),ios::in | ios::out| ios::binary);

		if(m_FileHandler.is_open()&&m_FreeBlockFile.open(m_FileName))
		{
			if(m_FileSize==0)
			{
				m_LastBlock=0;
				if(!SaveFileAttributes())
					throw "Error al salvar atributos";
			}
			else
				if(!LoadFileAttributes())
					throw "Error al cargar atributos";

			retVal=true;
		}
	}


	return retVal;
}

bool File::LoadFileAttributes()
{
	char *charBlockNum=new char[sizeof(m_LastBlock)];

	m_FileHandler.seekg (0, ios::beg);
	m_FileHandler.read(charBlockNum, sizeof(m_LastBlock));
	m_LastBlock=ByteConverter::bytesToUInt(charBlockNum);

	delete []charBlockNum;

	return true;
}

bool File::SaveFileAttributes()
{
	//Leo los primeros bytes del archivo para ver la cantidad de bloques en uso
	char * charBlockNum=new char[sizeof(m_LastBlock)];

	m_FileHandler.seekg (0, ios::beg);
	charBlockNum=ByteConverter::uIntToBytes(m_LastBlock,charBlockNum);
	m_FileHandler.write(charBlockNum, sizeof(m_LastBlock));

	//Libero la variable temporal
	delete []charBlockNum;

	return true;
}


Block *File::getNewBlock()
{
	Block *block=NULL;
	unsigned int blockNumber;

	if(!m_FreeBlockFile.popFreeBlock(blockNumber))
	{
		blockNumber=m_LastBlock;
		m_LastBlock++;
	}

	block=new Block(blockNumber, m_blockSize);

	return block;
}



Block *File::getBlock(const unsigned int blockNumber)
{
	Block *block=NULL;
	unsigned int offset;

	if(blockNumber<m_LastBlock&&m_FileHandler.is_open())
	{
		block=new Block(blockNumber, m_blockSize);
		offset=m_FirstBlockOffset+blockNumber*m_blockSize;

		char * blockStream= new char[m_blockSize];

		m_FileHandler.seekg (offset, ios::beg);
		m_FileHandler.read(blockStream, m_blockSize*sizeof(char));

		if(!block->deserialize(blockStream))
		{
			delete block;
			block=NULL;
		}

		delete [] blockStream;
	}

	return block;
}



bool File::closeFile()
{
	//Si esta abierto lo cierro
	if(m_FileHandler.is_open())
		m_FileHandler.close();

	return true;
}



bool File::saveBlock(Block * block)
{
	bool retVal = false;

	//Si el archivo esta abierto
	if(m_FileHandler.is_open())
	{
		unsigned int blockNumber;
		unsigned int offset;

		//Pido espacio para el stream temporal que voy a usar para convertir el nodo
		char * blockStream = new char[m_blockSize];

		//Convierto el nodo a un stream de chars
		block->serialize(blockStream);

		//Obtengo el numero del bloque
		blockNumber = block->getBlockNumber();

		//Calculo la posicion del bloque en el archivo, basandome en su numero de bloque
		//y saltandome los bytes que corresponden al header del archivo
		offset=m_FirstBlockOffset+blockNumber*m_blockSize;

		//Busco la posicion y escribo el bloque completo en disco.
		m_FileHandler.seekg (offset, ios::beg);
		m_FileHandler.read(blockStream, m_blockSize*sizeof(char));

		//Libero el stream temporal
		delete []blockStream;
		//digo que estuvo OK
		retVal=true;
	}

	return retVal;
}


