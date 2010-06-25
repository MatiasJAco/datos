/*
 * testLogger.cpp
 *
 *  Created on: 06/04/2010
 *      Author: matias
 */

using namespace std;
#include "../logic/logger/Logger.h"

int main(int argc, char *argv[]){

	//Logger*MiLogger=new Logger();
	Logger *MiLogger = Logger::Instance();

	MiLogger->imprimir_ayuda();

	string cadenaAIngresar1="(1;valor1)";
	string cadenaAIngresar2="(2;valor2)";
	string cadenaAIngresar3="(;valor3)";

	MiLogger->ingresar(&cadenaAIngresar1[0]);
	MiLogger->ingresar(&cadenaAIngresar2[0]);
	MiLogger->ingresar(&cadenaAIngresar3[0]);

	//string CadenaABuscar1("2010");
	string CadenaABuscar1("valor4");
	string CadenaABuscar2("valor2");

	bool encontrado = MiLogger->buscar_cadena(&CadenaABuscar1[0]);
	if (!encontrado) {
		cout << "Cadena no encontrada" << endl;
	}
	bool encontrado2 = MiLogger->buscar_cadena(&CadenaABuscar2[0]);
	if (encontrado2) {
		cout << "Cadena encontrada" << endl;
	}

	MiLogger->recorrer_log();



	return 0;
};
