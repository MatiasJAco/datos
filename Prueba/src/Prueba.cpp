#include <iostream>
using std::cerr;
using std::endl;
using std::ios;

#include <fstream>
using std::fstream;

#include <cstdlib>
using std::exit; // exit function prototype

#include <string>
using std::string;

#include <stdio.h>
#include <string.h>

#include "../application/entities/KeyInt.h"
#include "../application/entities/StringRegister.h"

/**
 * Este método devuelve el valor de la función de hash.
 * TODO hacer que en vez de 123, vaya la clave que contiene KeyInt
 */
int hash(int tamanioTabla, KeyInt key)
{
	return 123 % tamanioTabla;
}

/**
 * TODO: Este método indica si existe una clave en el archivo de la organización directa.
 */
bool existe(KeyInt keyInt)
{
	return false;
}

/**
 * Método que agrega un registro a un bloque del archivo de la organización directa.
 */
void insertar(StringRegister stringRegister)
{
	fstream outCredit("credit.dat", ios::out | ios::binary);

    // exit program if fstream cannot open file
    if (!outCredit)
    {
        cerr << "File could not be opened." << endl;
        exit(1);
     }

     // seek position in file of user-specified record
     // TODO reemplazar "0" por el número de registro relativo
     outCredit.seekp(0 * sizeof(StringRegister));

     // write user-specified information in file
     outCredit.write(reinterpret_cast< const char * >(&stringRegister),sizeof(StringRegister));
}

int main()
{
	KeyInt regkey(45);
	StringRegister stringRegister(regkey,"Hola");
	insertar(stringRegister);
	return 0;
}
