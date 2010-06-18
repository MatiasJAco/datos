#include <iostream>
#include <sstream>
#include "../logic/structures/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/structures/hash/Hash.h"

using namespace std;

int main(int argc, const char* argv[]){
	Hash* hash = new Hash();

	if (argc == 1) {
		cout << "Comandos para usar el hash:" << endl;
		cout << "-B (Busca una clave)" << endl;
		cout << "-I (Ingresa un dato a la estructura" << endl;
		cout << "-M (Modifica un dato existente de la estructura)" << endl;
		cout << "-Q (Quita un dato de la estructura)" << endl;
		cout << "-S (Impresion de datos actuales de la estructura)" << endl;
		cout << "-h (Ayuda)" << endl;
		delete hash;
		return 0;
	} else if (argc == 2) { // Solo se permiten las operaciones S, y H.
		string operacion (argv[1]);
		if (operacion == "-S") {
			cout << "Impresion del estado actual:" << endl;
			hash->print();
			delete hash;
			return 0;
		} else if (operacion == "-h") {
			cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
			cout << "./hashMain -I \"(12;paytiti)\"" << endl;
			cout << "./hashMain -B \"(12;)\"" << endl;
			cout << "./hashMain -M \"(12;pepe)\"" << endl;
			cout << "./hashMain -Q \"(12;)\"" << endl;
			cout << "./hashMain -S" << endl;
			delete hash;
			return 0;
		} else {
			cout << "Faltan parametros. Utilice \"./hashMain -h\" para obtener mas ayuda. " << endl;
			delete hash;
			return 0;
		}
	}

	string operacion (argv[1]);
	string claveValor (argv[2]);

	int separator = claveValor.find(";");
	int separator2 = claveValor.find(")");

	string clave = claveValor.substr(1, separator);
	string valor = claveValor.substr(separator+1, separator2 - separator - 1);

	if (operacion == "-B") {
		cout << "Buscando la clave " << clave << "..." << endl;
		bool result = false;
		StringInputData sid;
		try{
			result=hash->find(clave,sid);
		}
		catch(HashException &e){
			cout << e.what() << clave << endl;
		}
		if (result) {
			cout << sid.toString() << endl;
		} else {
			cout << "No se encontro la clave " << clave << "." << endl;
		}
	} else if (operacion == "-I") {
		cout << "Ingresando la clave " << clave << " con el valor " << valor << "..." << endl;
		bool result = false;
		try{
			result=hash->insert(clave, valor);
		}
		catch(HashException &e)
		{
			cout << e.what() << clave << endl;
		}
		if (result) {
			cout << "Se agrego correctamente la clave " << clave << endl;
		} else {
			cout << "No se agrego la clave " << clave << "." << endl;
		}

	} else if (operacion == "-M") {
		cout << "Modificando el valor de la clave " << clave << " por " << valor << "..." << endl;
		bool result = false;
		try{
			result=hash->modify(clave, valor);
		}
		catch(HashException &e)
		{
			cout << e.what() << clave << endl;
		}
		if (result) {
			cout << "Se modifico correctamente el valor de la clave " << clave << endl;
		} else {
			cout << "No se modifico la clave " << clave << "." << endl;
		}
	} else if (operacion == "-Q") {
		cout << "Quitando el dato representado por la clave " << clave << "..." << endl;
		bool result = false;
		try{
			result=hash->remove(clave);
		}
		catch(HashException &e)
		{
			cout << e.what() << clave << endl;
		}
		if (result) {
			cout << "Se elimino correctamente la clave " << clave << endl;
		} else {
			cout << "No se elimino la clave " << clave << "." << endl;
		}
	} else if (operacion == "-S") {
		cout << "Impresion del estado actual:" << endl;
		hash->print();
	} else if (operacion == "-h") {
		cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
		cout << "./hashMain -I \"(12;paytiti)\"" << endl;
		cout << "./hashMain -B \"(12;)\"" << endl;
		cout << "./hashMain -M \"(12;pepe)\"" << endl;
		cout << "./hashMain -Q \"(12;)\"" << endl;
		cout << "./hashMain -S" << endl;
	}
	delete hash;
	return 0;
}
