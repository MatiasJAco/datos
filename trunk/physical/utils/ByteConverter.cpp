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

	memcpy(&entero,bytes,sizeof(int));

	return entero;
}

long ByteConverter::bytesToLong(const char *bytes)
{
	long entero = 0;

	memcpy(&entero,bytes,sizeof(long));

	return entero;
}

double ByteConverter::bytesToDouble(const char *bytes)
{
	double decimald = 0;

	memcpy(&decimald,bytes,sizeof(double));

	return decimald;
}


float ByteConverter::bytesToFloat(const char *bytes)
{
	float decimalf = 0;

	memcpy(&decimalf,bytes,sizeof(float));

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
	memcpy(bytes,&size_str,sizeof(int));
	bytes+=sizeof(size_str);

	const char* c_str = str.c_str();
	memcpy(bytes,c_str,size_str*sizeof(char));

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

	memcpy(&entero,bytes,sizeof(unsigned int));

	return entero;
}

std::string ByteConverter::bytesToString(const char *bytes)
{
	string str;
	unsigned int size_str =strlen(bytes)+1;

	char* c_str = new char[size_str];
	memcpy(c_str,bytes,size_str*sizeof(char));


	str = c_str;

	delete[] c_str;

	return str;
}








