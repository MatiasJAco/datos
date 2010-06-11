/**
 * ByteConverter.cpp
 *
 *  Created on: 26/03/2010
 *      Author: kira
 */

#include "ByteConverter.h"

using namespace std;

int ByteConverter::bytesToInt(const char *bytes)
{
	int entero = 0;
	if(bytes!=NULL)
	{
		memcpy(&entero,bytes,sizeof(int));
	}

	return entero;
}

long ByteConverter::bytesToLong(const char *bytes)
{
	long entero = 0;

	if(bytes!=NULL)
	{
		memcpy(&entero,bytes,sizeof(long));
	}
	return entero;
}

double ByteConverter::bytesToDouble(const char *bytes)
{
	double decimald = 0;
	if(bytes!=NULL)
	{
		memcpy(&decimald,bytes,sizeof(double));
	}

	return decimald;
}


float ByteConverter::bytesToFloat(const char *bytes)
{
	float decimalf = 0;
	if(bytes!=NULL)
	{
		memcpy(&decimalf,bytes,sizeof(float));
	}
	return decimalf;
}



char *ByteConverter::intToBytes(const int entero, char *bytes)
{
	memcpy(bytes,&entero,sizeof(int));
	return bytes;
}

char *ByteConverter::doubleToBytes(const double decimald, char *bytes)
{
	memcpy(bytes,&decimald,sizeof(double));
	return bytes;
}


char *ByteConverter::floatToBytes(const float decimalf, char *bytes)
{
	memcpy(bytes,&decimalf,sizeof(decimalf));
	return bytes;
}


char *ByteConverter::stringToBytes(const std::string str, char *bytes)
{
	int size_str = str.size();

	const char* c_str = str.c_str();
	memcpy(bytes,c_str,size_str*sizeof(char)+1);

	return bytes;
}



char *ByteConverter::uIntToBytes(const unsigned int entero, char *bytes)
{
	memcpy(bytes,&entero,sizeof(unsigned int));
	return bytes;
}

unsigned int ByteConverter::bytesToUInt(const char *bytes)
{
	unsigned int entero = 0;
	if(bytes!=NULL)
	{
		memcpy(&entero,bytes,sizeof(unsigned int));
	}

	return entero;
}

std::string ByteConverter::bytesToString(const char *bytes)
{
	string str="";
	if(bytes!=NULL)
	{
		unsigned int size_str =strlen(bytes)+1;

		char* c_str = new char[size_str+sizeof(unsigned int)];
		memcpy(c_str,bytes,size_str*sizeof(char));


		str = c_str;

		delete[] c_str;
	}

	return str;
}

void ByteConverter::printHexa(char *stream, unsigned int size)
{
	int fin =size;
	for(int i=0; i<fin; i++)
	{
	        if (i%2==0)
	        cout << " ";
	        cout << setfill('0') << setw(2) << hex << ((0x00FF)&(unsigned int)
	stream[i]);
	        cout.flush();
	}
}










