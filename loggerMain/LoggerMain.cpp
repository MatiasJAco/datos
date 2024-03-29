#include <iostream>
#include <sstream>
#include "../logic/input/StringInputData.h"
#include "../logic/logger/Logger.h"

using namespace std;

int main(int argc, const char* argv[]){
	//Logger* logger = new Logger();
	Logger* logger = Logger::Instance();

	if (argc == 1) {
		cout << "Comandos para usar el logger:" << endl;
		cout << "-B (Busca una cadena de caracteres)" << endl;
		cout << "-I (Ingresa una cadena de caracteres a la estructura" << endl;
		cout << "-S (Impresion de datos actuales de la estructura)" << endl;
		cout << "-h (Ayuda)" << endl;
		delete logger;
		return 0;
	} else if (argc == 2) { // Solo se permiten las operaciones S, y H.
		string operacion (argv[1]);
		if (operacion == "-S") {
			cout << "Impresion del estado actual:" << endl;
			logger->print();
			delete logger;
			return 0;
		} else if (operacion == "-h") {
			cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
			cout << "./loggerMain -I \"cadena de caracteres\"" << endl;
			cout << "./loggerMain -B \"cadena de caracteres\"" << endl;
			cout << "./loggerMain -S" << endl;
			delete logger;
			return 0;
		} else {
			cout << "Faltan parametros. Utilice \"./loggerMain -h\" para obtener mas ayuda. " << endl;
			delete logger;
			return 0;
		}
	}

	string operacion (argv[1]);
	string cadena (argv[2]);
	string cadena2 = ";" + cadena;

	if (operacion == "-B") {
		cout << "Buscando la cadena de caracteres " << cadena << "..." << endl;
		bool findResult = logger->findString(&cadena[0]);
		if (findResult == true) {
			cout << "Se encontro la cadena \"" << cadena  << "\"" << endl;
		} else {
			cout << "No se encontro la cadena \"" << cadena  << "\"" << endl;
		}
	} else if (operacion == "-I") {
		cout << "Ingresando la cadena de caracteres \"" << cadena  << "\"" << endl;
		logger->insert(&cadena2[0]);
		cout << "Se ingreso correctamente la cadena de caracteres \"" << cadena << "\"" << endl;
	} else if (operacion == "-S") {
		cout << "Impresion del estado actual:" << endl;
		logger->print();
	} else if (operacion == "-h") {
		cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
		cout << "./loggerMain -I \"cadena de caracteres\"" << endl;
		cout << "./loggerMain -B \"cadena de caracteres\"" << endl;
		cout << "./loggerMain -S" << endl;
	}
	delete logger;
	return 0;
}
