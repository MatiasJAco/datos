#include <iostream>
#include <sstream>
#include "../logic/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/hash/Hash.h"

using namespace std;

void testTable() {
	Table myTable;
	myTable.createFile();

	myTable.print();

	myTable.modifyRegister(1,22);
	myTable.print();

	myTable.duplicate();
	myTable.print();

	myTable.duplicate();
	myTable.print();

	myTable.duplicate();
	myTable.print();

	/*myTable.modifyRegister(70,23);
	myTable.print();*/

	if (myTable.verifyAndDivide()!= 0)
		printf("\nno se puede dividir");
	else printf("\nSI se puede dividir");

	myTable.print();
}

void testTable2(){
	Table myTable;
	myTable.createFile();
	myTable.print();
	myTable.changeFirstTimeInTable(24,444);
	myTable.print();
}

void testTable3(){
	Table myTable;
	myTable.createFile();
	myTable.print();
	int result = myTable.verifyJumps(1,2);
	printf("\nRESULT : %i",result);
}


void testTable4(){
	Table myTable;
	myTable.createFile();
	myTable.print();
	myTable.jumpAndReplace(6,5,23);
	myTable.print();
}

StringInputData* createSid( int key,char * value){
	stringstream ss (stringstream::in | stringstream::out);
	ss.str(value);
	StringInputData* sid = new StringInputData();
	sid->setKey(key);
	sid->setValue(ss.str());
	return sid;
}

void testModify() {
	Hash* hash = new Hash();
	/* Se toma el dato que ingresa el usuario. */
	char value[8] = "paytiti";
	for (int i = 1; i<=70;i++){
		StringInputData* sid = createSid(i,value);
		hash->add(sid);
		delete sid;
	}

	hash->print();
	char newValue[15]= "______________";
	bool result = hash->modify(12,newValue);
	if (result==1)
		cout<<endl<<"NO existe el sid"<<endl;
	else if (result==-1)
		cout<<endl<<"Hubo algun prob"<<endl;
	else
		cout<<endl<<"lo cambio!"<<endl;
	hash->print();
}

void testDelete() {
	Hash* hash = new Hash();
	char value[8] = "paytiti";
	char value2[5] = "pepe";
	char value3[5] = "luis";

	StringInputData* sid = createSid(22, value);
	hash->add(sid);

	StringInputData* sid2 = createSid(33, value2);
	hash->add(sid2);

	StringInputData* sid3 = createSid(44, value3);
	hash->add(sid3);

	hash->print();

	hash->erase(22);

	hash->print();
	delete hash;
}

void tests() {
	Hash* hash = new Hash();
	/* Se toma el dato que ingresa el usuario. */
	char value[8] = "paytiti";
	for (int i = 1; i<=70;i++){
		StringInputData* sid = createSid(i,value);
		hash->add(sid);
		delete sid;
	}

	hash->erase(70);
	hash->erase(66);
	hash->erase(30);
	hash->erase(26);
	hash->erase(22);
	hash->erase(18);
	hash->erase(14);
	hash->erase(10);
	hash->erase(6);
	hash->erase(2);
	hash->erase(34);
	hash->erase(38);
	hash->erase(42);
	hash->erase(46);
	hash->erase(50);
	hash->erase(54);
	hash->erase(58);

	hash->print();
	hash->erase(62);
	hash->print();
	delete hash;
}

int main(int argc, const char* argv[]){
	//testTable();
	//testTable2();
	//testTable3();
	//testTable4();
	//testDelete();
	tests();
	//cout << "paso test!" << endl;

//	Hash* hash = new Hash();
//
//	if (argc == 1 || argc == 2) {
//		cout << "Comandos para usar el hash:" << endl;
//		cout << "-B (Busca una clave)" << endl;
//		cout << "-I (Ingresa un dato a la estructura" << endl;
//		cout << "-M (Modifica un dato existente de la estructura)" << endl;
//		cout << "-Q (Quita un dato de la estructura)" << endl;
//		cout << "-S (Impresion de datos actuales de la estructura)" << endl;
//		cout << "-h (Ayuda)" << endl;
//		return 0;
//	}
//
//	string operacion (argv[1]);
//	string claveString (argv[2]);
//	string valor (argv[3]);
//	//string aux (";");
//
//	//int separator = claveValor.find(aux);
//
//	//int clave = atoi(claveValor.substr(0,separator).c_str());
//	//string valor = claveValor.substr(separator+1,claveValor.size());
//
//	int clave = atoi(claveString.c_str());
//	if (operacion == "-B") {
//		cout << "Buscando la clave " << clave << "..." << endl;
//		StringInputData* sid = hash->get(clave);
//		if (sid != NULL) {
//			cout << sid->toString() << endl;
//		} else {
//			cout << "No se encontro la clave " << clave << endl;
//		}
//	} else if (operacion == "-I") {
//		cout << "Ingresando la clave" << clave << " con el valor " << valor << "..." << endl;
//		int addResult = hash->add(clave, valor);
//		if (addResult == 0) {
//			cout << "Se agrego correctamente la clave " << clave << endl;
//		} else if (addResult == 1) {
//			cout << "No se agrego la clave " << clave << " pues ya existia."<< endl;
//		} else {
//			cout << "Se produjo un error al ingresar la clave " << clave << endl;
//		}
//	} else if (operacion == "-M") {
//		cout << "Modificando el valor de la clave" << clave << " por " << valor << "..." << endl;
//		int modifyResult = hash->modify(clave, valor);
//		if (modifyResult == 0) {
//			cout << "Se modifico correctamente el valor de la clave " << clave << endl;
//		} else if (modifyResult == 1) {
//			cout << "No se modifico el valor de la clave " << clave << " pues no existia la misma."<< endl;
//		} else {
//			cout << "Se produjo un error al modificar el valor de la clave " << clave << endl;
//		}
//	} else if (operacion == "-Q") {
//		cout << "Quitando el dato representado por la clave " << clave << "..." << endl;
//		int eraseResult = hash->erase(clave);
//		if (eraseResult == 0) {
//			cout << "Se elimino correctamente la clave " << clave << endl;
//		} else if (eraseResult == 1) {
//			cout << "No se elimino la clave " << clave << " pues no existia la misma."<< endl;
//		} else {
//			cout << "Se produjo un error al eliminar la clave " << clave << endl;
//		}
//	} else if (operacion == "-S") {
//		cout << "Impresion del estado actual:" << endl;
//		hash->print();
//	} else if (operacion == "-h") {
//		cout << "Ayuda" << endl;
//	}
//	delete hash;
	return 0;
}
