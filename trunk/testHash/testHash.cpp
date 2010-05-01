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
	delete hash;
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
	hash->print();
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
	hash->erase(62);
	hash->print();
	delete hash;
}

// IMPORTANTE !!!!!!!!!!!
// Para correr este ejemplo hay que eliminar manualmente los 3 archivos generados en los tests anteriores
// hash.bin    hash.bin.free  table.txt
void testEjemplo(){
	Hash* hash = new Hash();
	cout<< "Este proximo print deberia mostrar todas las cosas creadas pero vacias!\n"<<endl;
	hash->print();

	char value[131] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

	cout<< "+123\n"<<endl;
	StringInputData* sid123 = createSid(123,value);
	hash->add(sid123);
	delete sid123;
	hash->print();

	cout<< "+915\n"<<endl;
	StringInputData* sid915 = createSid(915,value);
	hash->add(sid915);
	delete sid915;
	hash->print();

	cout<< "+629\n"<<endl;
	StringInputData* sid629 = createSid(629,value);
	hash->add(sid629);
	delete sid629;
	hash->print();

	cout<< "+411\n"<<endl;
	StringInputData* sid411 = createSid(411,value);
	hash->add(sid411);
	delete sid411;
	hash->print();

	cout<< "+200\n"<<endl;
	StringInputData* sid200 = createSid(200,value);
	hash->add(sid200);
	delete sid200;
	hash->print();

	cout<< "+863\n"<<endl;
	StringInputData* sid863 = createSid(863,value);
	hash->add(sid863);
	delete sid863;
	hash->print();

	cout<< "-629\n"<<endl;
	hash->erase(629);
	hash->print();

	cout<< "+408\n"<<endl;
	StringInputData* sid408 = createSid(408,value);
	hash->add(sid408);
	delete sid408;
	hash->print();

	cout<< "+34\n"<<endl;
	StringInputData* sid34 = createSid(34,value);
	hash->add(sid34);
	delete sid34;
	hash->print();

	cout<< "+510\n"<<endl;
	StringInputData* sid510 = createSid(510,value);
	hash->add(sid510);
	delete sid510;
	hash->print();

	cout<< "+863\n"<<endl;
	hash->erase(863);
	hash->print();

	cout<< "+775\n"<<endl;
	StringInputData* sid775 = createSid(775,value);
	hash->add(sid775);
	delete sid775;
	hash->print();


	delete hash;
}

int main(int argc, const char* argv[]){
	//testTable();
	//testTable2();
	//testTable3();
	//testTable4();
	//testDelete();
	//tests();

	testEjemplo();
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
