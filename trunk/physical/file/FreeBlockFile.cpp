/*
 * FreeBlockFile.cpp
 *
 *  Created on: 15/04/2010
 *      Author: alex
 */

#include "FreeBlockFile.h"


using namespace std;

FreeBlockFile::FreeBlockFile() {
	m_FileSize=0;
	m_BlockCount=0;
	m_registerSize=sizeof(unsigned int);
}

FreeBlockFile::~FreeBlockFile()
{
	close();
}


bool FreeBlockFile::open(const std::string filename)
{
	bool retVal=true;

	m_FileName=filename+".free";

	//Si estaba abierto lo cierro
	if(m_FileHandler.is_open())
		m_FileHandler.close();


	//Abro en modo out inicialmente para crear el archivo si no existe
	//pongo append para que la posicion apunte al final
	//obtengo el tamaño del archivo
	m_FileHandler.clear();
	m_FileHandler.open (m_FileName.c_str(), ios::out|ios::binary|ios::app);
	m_FileSize =m_FileHandler.tellg();
	m_FileHandler.close();

	//Abro en modo lectura/escritura binaria
	m_FileHandler.clear();
	m_FileHandler.open (m_FileName.c_str(), ios::out|ios::in|ios::binary);

	//Me fijo si lo abrio exitosamente
	if(m_FileHandler.is_open())
	{
		//Si es la primera vez que se abre tomo que la cant de bloques es 0
		if(m_FileSize==0)
		{
			m_BlockCount=0;
			retVal=writeHeader(m_BlockCount);
		}
		//Si no es la primera vez que se abre leo la cantidad de bloques del archivo
		else
		{
			retVal=readHeader(m_BlockCount);
		}
	}
	else
		retVal=false;


	return retVal;

}


bool FreeBlockFile::readHeader()
{
	return readHeader(m_BlockCount);
}

bool FreeBlockFile::writeHeader()
{
	return writeHeader(m_BlockCount);
}


bool FreeBlockFile::readHeader(unsigned int &blockCount)
{
	char *charBlockNum=new char[sizeof(blockCount)];

	m_FileHandler.seekg (0, ios::beg);
	m_FileHandler.read(charBlockNum, sizeof(blockCount));
	blockCount=ByteConverter::bytesToUInt(charBlockNum);

	delete []charBlockNum;

	return true;
}


bool FreeBlockFile::writeHeader(const unsigned int blockCount )
{
	//Leo los primeros bytes del archivo para ver la cantidad de bloques en uso
	char * charBlockNum=new char[sizeof(blockCount)];

	m_FileHandler.seekg (0, ios::beg);
	charBlockNum=ByteConverter::uIntToBytes(blockCount,charBlockNum);
	m_FileHandler.write(charBlockNum, sizeof(blockCount));

	//Libero la variable temporal
	delete []charBlockNum;

	return true;
}

bool FreeBlockFile::pushFreeBlock(const unsigned int numblock)
{
	bool retVal=false;

	//Si el archivo esta abierto
	if(m_FileHandler.is_open())
	{
		//Aumenta la cantidad de elementos
		unsigned int tmpblockCount=m_BlockCount+1;

		//Grabo en disco la cant de bloques
		if(writeHeader(tmpblockCount))
		{
			//Grabo el dato en la posicion del ultimo bloque
			unsigned int offset =m_BlockCount*m_registerSize+sizeof(m_BlockCount);

			//Me paro en el ultimo registro
			m_FileHandler.seekg (offset, ios::beg);

			FixedRegister reg((char*)&numblock, sizeof(unsigned int));

			char * charStream = reg.getValue();
			unsigned int charStreamSize = reg.getSize();

			m_FileHandler.write(charStream, charStreamSize);

			//Chequeo si hubo error
			if(!m_FileHandler.bad())
				retVal=true;

			delete [] charStream;
			m_BlockCount=tmpblockCount;

		}


	}

	return retVal;
}


bool FreeBlockFile::popFreeBlock(unsigned int & numblock)
{
	bool retVal=true;

	//Si esta abierto y hay bloques
	if(m_FileHandler.is_open()&&m_BlockCount>0)
	{
		//Pongo en una variable temporal la cantidad de bloques
		//que va a quedar. Si fallo al intentar escribirla

		unsigned int tmpblockCount=m_BlockCount-1;

		//Escribo al archivo la cant de bloques que va a quedar
		if(writeHeader(tmpblockCount))
		{
			//Tomo el ultimo bloque
			char * charStream=new char[m_registerSize];
			unsigned int offset=(tmpblockCount)*m_registerSize+sizeof(m_BlockCount);

			m_FileHandler.seekg (offset, ios::beg);

			m_FileHandler.read(charStream, m_registerSize);

			numblock=ByteConverter::bytesToUInt(charStream);

			m_BlockCount=tmpblockCount;
			delete []charStream;

		}
		//Si hubo error al escribir en disco la cantidad de bloques
		else
		{
			retVal=false;
		}

	}
	else
		retVal=false;

	return retVal;
}


void FreeBlockFile::showFreeNodes()
{
	readHeader(m_BlockCount);
	cout << "Cantidad de bloques:"<<m_BlockCount<<endl;
	cout << "Bloques:"<<endl;

	unsigned int i;
	char * charStream=new char[m_BlockCount*m_registerSize];
	m_FileHandler.seekg (sizeof(m_BlockCount), ios::beg);

	m_FileHandler.read(charStream, m_BlockCount*m_registerSize);

	for(i=0; i<m_BlockCount; i++)
	{
		cout <<ByteConverter::bytesToUInt(&charStream[i*m_registerSize])<<",";
	}
	delete [] charStream;
	cout <<endl;
}


bool FreeBlockFile::close()
{
	bool retVal=true;

	if(m_FileHandler.is_open())
	{
		m_FileHandler.close();

		if(resize(m_BlockCount*m_registerSize+sizeof(m_BlockCount)))
			retVal =true;
	}

	m_FileSize=0;
	m_BlockCount=0;

	return retVal;
}


