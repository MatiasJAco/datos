#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "../logic/input/StringInputData.h"
#include "../logic/structures/tree/BPlusTree.h"
#include "../logic/exceptions/BPlusTreeException.h"

using namespace std;

int main(int argc, const char* argv[]){
	BPlusTree* bPlusTree = new BPlusTree("arbol.dat",92,0.5);

	if (argc == 1) {
		cout << "Comandos para usar el arbol:" << endl;
		cout << "-B (Busca una clave)" << endl;
		cout << "-I (Ingresa un dato a la estructura" << endl;
		cout << "-M (Modifica un dato existente de la estructura)" << endl;
		cout << "-Q (Quita un dato de la estructura)" << endl;
		cout << "-S (Impresion de datos actuales de la estructura)" << endl;
		cout << "-h (Ayuda)" << endl;
		delete bPlusTree;
		return 0;
	}
	else
		if (argc == 2) { // Solo se permiten las operaciones S, y H.
		string operacion (argv[1]);

		if (operacion == "-S") {

			cout << "Impresion del estado actual:" << endl;

			bPlusTree->print();
			delete bPlusTree;
			return 0;

		}
		else
			if (operacion == "-h") {
			cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
			cout << "./treeMain -I \"(12;paytiti)\"" << endl;
			cout << "./treeMain -B \"(12;)\"" << endl;
			cout << "./treeMain -M \"(12;pepe)\"" << endl;
			cout << "./treeMain -Q \"(12;)\"" << endl;
			cout << "./treeMain -S" << endl;
			delete bPlusTree;
			return 0;

		} else
			{
			cout << "Faltan parametros. Utilice \"./treeMain -h\" para obtener mas ayuda. " << endl;
			delete bPlusTree;
			return 0;
		}
	}

	string operacion (argv[1]);
	string claveValor (argv[2]);
	string aux (";");

	int separator = claveValor.find(aux);
	int separator2 = claveValor.find(")");

	string clave = claveValor.substr(1, separator);
	string valor = claveValor.substr(separator+1, separator2 - separator - 1);

	if (operacion == "-B") {

		cout << "Buscando la clave " << clave << "..." << endl;

		StringInputData sidResult ("","");
		bool findResult = false;
		try
		{
			findResult = bPlusTree->find(clave, sidResult);
		}
		catch(BPlusTreeException e)
		{
			cout << e.what() << endl;
		}

		if (findResult) {
			cout << "Clave :" << sidResult.getKey() <<  endl;
			cout << "Valor :" << sidResult.getValue() <<  endl;
		} else
		{
			cout << "No se encontro la clave." << clave << endl;
		}
	}
	else
		if (operacion == "-I") {

		cout << "Ingresando la clave " << clave << " con el valor " << valor << "..." << endl;
		bool insertResult = false;

		try {
			insertResult = bPlusTree->insert(clave, valor);
		}
		catch(BPlusTreeException e)
		{
			cout << e.what()<< endl;
		}

		if (insertResult) {
			cout << "Se agrego correctamente la clave " << clave << endl;
		} else {
			cout << "No se agrego la clave " << clave << "." << endl;
		}

	} else
		if (operacion == "-M") {

		cout << "Modificando el valor de la clave " << clave << " por " << valor << "..." << endl;

		bool modifyResult = false;
		try
		{
			modifyResult = bPlusTree->modify(clave,valor);
		}
		catch(BPlusTreeException e)
		{
			cout << e.what() << endl;
		}

		if (modifyResult) {
			cout << "Se modifico correctamente el valor de la clave " << clave << endl;
		}
		else {
			cout << "No se modifico el valor pues la clave no existe" << endl;
		}
	}
	else
		if (operacion == "-Q") {

		cout << "Quitando el dato representado por la clave " << clave << "..." << endl;

		bool eraseResult = false;
		try{
				eraseResult = bPlusTree->remove(clave);
		}
		catch(BPlusTreeException e)
		{
			cout << e.what() << endl;
		}

		if (eraseResult) {
			cout << "Se elimino correctamente la clave " << clave << endl;
		} else {
			cout << "No se elimino la clave " << clave << "." << endl;
		}

	}
	else if (operacion == "-S") {

		cout << "Impresion del estado actual:" << endl;
		bPlusTree->print();

	}
	else if (operacion == "-h") {

		cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
		cout << "./treeMain -I \"(12;paytiti)\"" << endl;
		cout << "./treeMain -B \"(12;)\"" << endl;
		cout << "./treeMain -M \"(12;pepe)\"" << endl;
		cout << "./treeMain -Q \"(12;)\"" << endl;
		cout << "./treeMain -S" << endl;
	}
	delete bPlusTree;
	return 0;
}
