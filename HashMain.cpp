#include <iostream>
#include <sstream>
#include "../logic/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/hash/Hash.h"

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
	string aux (";");

	int separator = claveValor.find(aux);
	int separator2 = claveValor.find(")");

	int clave = atoi(claveValor.substr(1, separator).c_str());
	string valor = claveValor.substr(separator+1, separator2 - separator - 1);

	if (operacion == "-B") {
		cout << "Buscando la clave " << clave << "..." << endl;
		StringInputData* sid = hash->get(clave);
		if (sid != NULL) {
			cout << sid->toString() << endl;
		} else {
			cout << "No se encontro la clave " << clave << endl;
		}
	} else if (operacion == "-I") {
		cout << "Ingresando la clave " << clave << " con el valor " << valor << "..." << endl;
		int addResult = hash->add(clave, valor);
		if (addResult == 0) {
			cout << "Se agrego correctamente la clave " << clave << endl;
		} else if (addResult == 1) {
			cout << "No se agrego la clave " << clave << " pues ya existia."<< endl;
		} else {
			cout << "Se produjo un error al ingresar la clave " << clave << endl;
		}
	} else if (operacion == "-M") {
		cout << "Modificando el valor de la clave " << clave << " por " << valor << "..." << endl;
		int modifyResult = hash->modify(clave, valor);
		if (modifyResult == 0) {
			cout << "Se modifico correctamente el valor de la clave " << clave << endl;
		} else if (modifyResult == 1) {
			cout << "No se modifico el valor de la clave " << clave << " pues no existia la misma."<< endl;
		} else {
			cout << "Se produjo un error al modificar el valor de la clave " << clave << endl;
		}
	} else if (operacion == "-Q") {
		cout << "Quitando el dato representado por la clave " << clave << "..." << endl;
		int eraseResult = hash->erase(clave);
		if (eraseResult == 0) {
			cout << "Se elimino correctamente la clave " << clave << endl;
		} else if (eraseResult == 1) {
			cout << "No se elimino la clave " << clave << " pues no existia la misma."<< endl;
		} else {
			cout << "Se produjo un error al eliminar la clave " << clave << endl;
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
