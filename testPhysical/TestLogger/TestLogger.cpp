/*
 * TestLogger.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: adrian
 */

#include "TestLogger.h"

TestLogger::TestLogger() {
}

TestLogger::~TestLogger() {
}

void TestLogger::testLogger() {
	Logger *MiLogger = Logger::Instance();

	MiLogger->printHelp();

	std::string cadenaAIngresar1="(1;valor1)";
	std::string cadenaAIngresar2="(2;valor2)";
	std::string cadenaAIngresar3="(;valor3)";

	MiLogger->insert(&cadenaAIngresar1[0]);
	MiLogger->insert(&cadenaAIngresar2[0]);
	MiLogger->insert(&cadenaAIngresar3[0]);

	std::string CadenaABuscar1("valor4");
	std::string CadenaABuscar2("valor2");

	bool encontrado = MiLogger->findString(&CadenaABuscar1[0]);
	if (!encontrado) {
		std::cout << "Cadena no encontrada" << std::endl;
	}
	bool encontrado2 = MiLogger->findString(&CadenaABuscar2[0]);
	if (encontrado2) {
		std::cout << "Cadena encontrada" << std::endl;
	}

	MiLogger->print();
}
