/*
 * testPhysical.cpp
 *
 *  Created on: 13/04/2010
 *      Author: alex
 */
#include "../physical/file/VarRegister.h"
#include "../physical/utils/ByteConverter.h"
#include <sstream>

using namespace std;

int main()
{
	VarRegister *varR = new VarRegister();

	long longVar=123443232434;
	long longVar2;
	int intVar=123455666;
	int intVar2;
	string stringVar ="tu madre!";
	string stringVar2;

	char * streamVar;

	//Se pasa la direccion del valor casteada a puntero a char
	varR->setValue((char*)&longVar, sizeof(longVar));
	streamVar = varR->getValue();

	longVar2=ByteConverter::bytesToLong(streamVar);

	if(longVar!=longVar2)
	{
		cout <<"long1 "<<longVar<<",long2 "<<longVar2<<endl;
		cout << "Error en registro longs"<<endl;
	}


	delete streamVar;


	varR->setValue((char*)&intVar, sizeof(intVar));
	streamVar = varR->getValue();

	intVar2=ByteConverter::bytesToInt(streamVar);

	if(intVar!=intVar2)
	{
		cout <<"int1 "<<intVar<<",intg2 "<<intVar2<<endl;
		cout << "Error en registro int"<<endl;
	}


	delete streamVar;


	varR->setValue((char*)stringVar.c_str(), stringVar.size());
	streamVar = varR->getValue();

	stringVar2=ByteConverter::bytesToString(streamVar);

	if(stringVar!=stringVar2)
	{
		cout <<"string1 "<<stringVar<<",string2 "<<stringVar2<<endl;
		cout << "Error en registro string"<<endl;
	}


	delete streamVar;

	delete varR;

	return 0;
}
