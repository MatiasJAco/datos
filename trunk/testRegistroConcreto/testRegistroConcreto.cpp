/*
 * main.cpp
 *
 *  Created on: 26/03/2010
 *      Author: kira
 */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <iostream>

#include "../common/utils/ByteConverter.h"
#include "../application/entities/RegistroConcreto.h"

using namespace std;

int main(int argc, char *argv[])
{

//	double dd = 10.5;
//	float df = 20.5;
//	int i = 8;
//
//	char* cdd = (char*)malloc(sizeof(double));
//	char* cdf = (char*)malloc(sizeof(float));
//	char* ci = (char*)malloc(sizeof(int));
//
//	cdd = ByteConverter::doubleToBytes(dd,cdd);
//	cdf = ByteConverter::floatToBytes(df,cdf);
//	ci = ByteConverter::intToBytes(i,ci);
//
//	double convdd = 0;
//	float convdf = 0;
//	int convi = 0;
//
//	convdd = ByteConverter::bytesToDouble(cdd);
//	convdf = ByteConverter::bytesToFloat(cdf);
//	convi = ByteConverter::bytesToInt(ci);
//
//	cout << "Double: " << convdd << std::endl;
//	cout << "Float: " << convdf << std::endl;
//	cout << "Int: " << convi << std::endl;
//
//	free(cdd);
//	free(cdf);
//	free(ci);
	try{
		RegistroConcreto reg(10,11.2,12.33,"Hola");
		RegistroConcreto reg2;

		char * bytes;
		unsigned int size = reg.getSize();

		bytes = new char[size];
		reg.serialize(bytes);


		reg2.deserialize(bytes);
		cout << reg2<<endl;

		delete[] bytes;
	}
	catch(char const *e)
	{
		cout << e<<endl;
	}


	return 0;
}
