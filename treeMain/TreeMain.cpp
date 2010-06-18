#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "../logic/input/StringInputData.h"
#include "../logic/structures/tree/BPlusTree.h"
#include "../logic/exceptions/BPlusTreeException.h"

using namespace std;

int main(int argc, const char* argv[]){
	StringInputData data("4","paytiti");
	BPlusTree* bPlusTree = new BPlusTree("arbol.dat",92,0.5,data);

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

	//TODO pablo - TreeMain - comente todo esto para que compile
//	int clave = atoi(claveValor.substr(1, separator).c_str());
//	string valor = claveValor.substr(separator+1, separator2 - separator - 1);
//
//	if (operacion == "-B") {
//
//		cout << "Buscando la clave " << clave << "..." << endl;
//		StringInputData sid (clave,"");
//		StringInputData sid2 (0,"");
//		bool findResult = false;
//
//		try
//		{
//			findResult = bPlusTree->find(sid, sid2);
//		}
//		catch(BPlusTreeException e)
//		{
//			cout << e.what() << endl;
//		}
//
//		if (findResult == true) {
//			cout << "Clave :" << sid2.getKey() <<  endl;
//			cout << "Valor :" << sid2.getValue() <<  endl;
//		} else
//		{
//			cout << "No se encontro la clave " << clave << endl;
//		}
//	}
//	else
//		if (operacion == "-I") {
//
//		cout << "Ingresando la clave " << clave << " con el valor " << valor << "..." << endl;
//		StringInputData sid (clave, valor);
//		bool insertResult = false;
//
//		try {
//			insertResult = bPlusTree->insert(sid);
//		}
//		catch(BPlusTreeException e)
//		{
//			cout << e.what()<< endl;
//		}
//
//		if (insertResult == true) {
//			cout << "Se agrego correctamente la clave " << clave << endl;
//		} else {
//			cout << "No se agrego la clave " << clave << ". Verifique si la misma ya existia." << endl;
//		}
//
//	} else
//		if (operacion == "-M") {
//
//		cout << "Modificando el valor de la clave " << clave << " por " << valor << "..." << endl;
//		StringInputData sid (clave, "");
//		StringInputData sid2 (clave, valor);
//		bool modifyResult = false;
//		try
//		{
//			modifyResult = bPlusTree->modify(sid, sid2);
//		}
//		catch(BPlusTreeException e)
//		{
//			//cout << e.what() << endl;
//			cout << "No se modifico el valor pues la clave no existe" << endl;
//		}
//
//		if (modifyResult == true) {
//			cout << "Se modifico correctamente el valor de la clave " << clave << endl;
//		}
//	}
//	else
//		if (operacion == "-Q") {
//
//		cout << "Quitando el dato representado por la clave " << clave << "..." << endl;
//		StringInputData sid (clave, "");
//		bool eraseResult = false;
//		try{
//				eraseResult = bPlusTree->remove(sid);
//		}
//		catch(BPlusTreeException e)
//		{
//			cout << e.what() << endl;
//		}
//
//		if (eraseResult == true) {
//			cout << "Se elimino correctamente la clave " << clave << endl;
//		} else {
//			cout << "No se elimino la clave " << clave << " . Verifique que la clave exista." << endl;
//		}
//
//	}
//	else if (operacion == "-S") {
//
//		cout << "Impresion del estado actual:" << endl;
//		StringInputData data;
//		bPlusTree->showTree(data);
//
//	}
//	else if (operacion == "-h") {
//
//		cout << "Ayuda - Algunos ejemplos de ejecucion:" << endl;
//		cout << "./treeMain -I \"(12;paytiti)\"" << endl;
//		cout << "./treeMain -B \"(12;)\"" << endl;
//		cout << "./treeMain -M \"(12;pepe)\"" << endl;
//		cout << "./treeMain -Q \"(12;)\"" << endl;
//		cout << "./treeMain -S" << endl;
//	}
	delete bPlusTree;
	return 0;
}
