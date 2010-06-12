#include <iostream>
#include <sstream>
#include "../logic/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/hash/Hash.h"
#include "../logic/md5/MD5.h"
#include "../logic/bigint/BigIntegerLibrary.hh"

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

StringInputData* createSid( std::string key,char * value){
	stringstream ss (stringstream::in | stringstream::out);
	ss.str(value);
	StringInputData* sid = new StringInputData();
	sid->setKey(key);
	sid->setValue(ss.str());
	return sid;
}

//TODO pablo - testhash - aca comente muchos tests para que compilen

//void testModify() {
//	Hash* hash = new Hash();
//	/* Se toma el dato que ingresa el usuario. */
//	char value[8] = "paytiti";
//	for (int i = 1; i<=70;i++){
//		StringInputData* sid = createSid(i,value);
//		hash->add(sid);
//		delete sid;
//	}
//
//	hash->print();
//	char newValue[15]= "______________";
//	bool result = hash->modify(12,newValue);
//	if (result==1)
//		cout<<endl<<"NO existe el sid"<<endl;
//	else if (result==-1)
//		cout<<endl<<"Hubo algun prob"<<endl;
//	else
//		cout<<endl<<"lo cambio!"<<endl;
//	hash->print();
//	delete hash;
//}

//void testDelete() {
//	Hash* hash = new Hash();
//	char value[8] = "paytiti";
//	char value2[5] = "pepe";
//	char value3[5] = "luis";
//
//	StringInputData* sid = createSid(22, value);
//	hash->add(sid);
//
//	StringInputData* sid2 = createSid(33, value2);
//	hash->add(sid2);
//
//	StringInputData* sid3 = createSid(44, value3);
//	hash->add(sid3);
//
//	hash->print();
//
//	hash->erase(22);
//
//	hash->print();
//	delete hash;
//}

//void tests() {
//	Hash* hash = new Hash();
//	hash->print();
//	/* Se toma el dato que ingresa el usuario. */
//	char value[8] = "paytiti";
//	for (int i = 1; i<=70;i++){
//		StringInputData* sid = createSid(i,value);
//		hash->add(sid);
//		delete sid;
//	}
//
//	hash->erase(70);
//	hash->erase(66);
//	hash->erase(30);
//	hash->erase(26);
//	hash->erase(22);
//	hash->erase(18);
//	hash->erase(14);
//	hash->erase(10);
//	hash->erase(6);
//	hash->erase(2);
//	hash->erase(34);
//	hash->erase(38);
//	hash->erase(42);
//	hash->erase(46);
//	hash->erase(50);
//	hash->erase(54);
//	hash->erase(58);
//	hash->erase(62);
//	hash->print();
//	delete hash;
//}

// IMPORTANTE !!!!!!!!!!!
// Para correr este ejemplo hay que eliminar manualmente los 3 archivos generados en los tests anteriores
// hash.bin    hash.bin.free  table.txt
void testEjemplo(){
	Hash* hash = new Hash();
	cout<< "Este proximo print deberia mostrar todas las cosas creadas pero vacias!\n"<<endl;
	hash->print();

	hash->add("123", "paytiti");
	hash->print();
	hash->erase("123");
	hash->print();

	char value[131] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

	//este es el maximo char[244] que puede entrar, sino pincha
	//char value[244] = "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012";

//	string value = "012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012";

	cout<< "+123\n"<<endl;
	hash->add("123",value);
	hash->print();

	cout<< "+915\n"<<endl;
	hash->add("915",value);
	hash->print();

	cout<< "+629\n"<<endl;
	hash->add("629",value);
	hash->print();

	cout<< "+411\n"<<endl;
	hash->add("411",value);
	hash->print();

	cout<< "+200\n"<<endl;
	hash->add("200",value);
	hash->print();

	cout<< "+863\n"<<endl;
	hash->add("863",value);
	hash->print();

	cout<< "-629\n"<<endl;
	hash->erase("629");
	hash->print();

	cout<< "+408\n"<<endl;
	hash->add("408",value);
	hash->print();

	cout<< "+34\n"<<endl;
	hash->add("34",value);
	hash->print();

	cout<< "+510\n"<<endl;
	hash->add("510",value);
	hash->print();

	cout<< "-863\n"<<endl;
	hash->erase("863");
	hash->print();

	cout<< "+775\n"<<endl;
	hash->add("775",value);
	hash->print();

	cout<<"modify value 123"<<endl;
	hash->modify("123","pepitooooooooo");
	hash->print();

	cout<<"pruebo el get de hash con 123"<<endl;
	StringInputData* sid = hash->get("123");
	if (sid != NULL) {
		cout << sid->toString() << endl;
	} else {
		cout << "No se encontro la clave 123 "<< endl;
	}

//////////////////
	//todo al sacarle el 775 y poner este , ver que no anda bien.. revisar!
//	cout<< "+1412080015\n"<<endl;
//	hash->add("1412080015",value);
//	hash->print();
//	hash->modify("1412080015","kkkkkkkkk");
//	hash->print();
/////////////////////////

//	cout<< "+1412080015\n"<<endl;
//	hash->add("1412080015",value);
//	hash->print();
//	hash->modify("1412080015","pepe");
//	hash->print();



	delete hash;
}

void testBug(){
	Hash* hash = new Hash();
	char value[8] = "paytiti";
	hash->add("12",value);
	hash->print();
	hash->erase("12");
	hash->print();
	delete hash;
}

/* Muestra la cadena que representa al numero, por pantalla. */
void testBigInt() {
	std::string s("0123456789012345678901234567890123456789012345678901234567890123");
	BigInteger f = stringToBigInteger(s);
	std::cout << f << std::endl;
}

/* Devuelve la cadena: 4d186321c1a7f0f354b297e8914ab240 */
void testMd5() {
	MD5 md5("hola");
	std::cout << md5.hexdigest() << std::endl;
}

// Aun sin terminar:
void testHashFunction() {
	MD5 md5("hola");
	std::string s(md5.hexdigest());
	std::cout << s << std::endl;
	int i = 0;

	std::string nueva = "";

	while(i < 32) {
		if (s.substr(i,1).compare("a") == 0) {
			nueva.append("10");
		} else if (s.substr(i,1).compare("b") == 0) {
			nueva.append("11");
		} else if (s.substr(i,1).compare("c") == 0) {
			nueva.append("12");
		} else if (s.substr(i,1).compare("d") == 0) {
			nueva.append("13");
		} else if (s.substr(i,1).compare("e") == 0) {
			nueva.append("14");
		} else if (s.substr(i,1).compare("f") == 0) {
			nueva.append("15");
		} else {
			nueva.append(s.substr(i,1));
		}

		i++;
	}
	std::cout << nueva << std::endl;

	BigInteger f = stringToBigInteger(nueva);
	std::cout << f << std::endl;
	BigInteger g = stringToBigInteger("4");
	std::cout << g << std::endl;
	std::cout << (f % g).toInt() << std::endl;
}

int main(int argc, const char* argv[]){
	//testTable();
	//testTable2();
	//testTable3();
	//testTable4();
	//testDelete();
	//tests();

	testEjemplo();
	//testBigInt();
	//testMd5();
	//testHashFunction();

	unsigned long long int mitest = 18446744073709551614 / 2;
	//cout <<mitest;
//	unsigned long int maximo = 4294967295; //este es el maximo 4294967295
//	cout <<maximo<<endl;


//	unsigned long int prueba = 4294967295 - 4294967295;
//	cout<<prueba<<endl;

	//	unsigned long long int supermax = 18446744073709551615; // maximo! 18446744073709551615 (longitud de 20)
	//	cout << supermax <<endl;

	//long double mydouble =  710000811000714080406040107000314051502120803061010050910010700/2;

//	cout << MD5("ivi")<<endl;
//
//	//HAY QUE SACARLE EL CERO ADELANTE si es que tiene
//	long double mydouble =  1105020005030501011204110211150910060810001412140604130909050506;
//	cout<<mydouble<<endl;
//
//	long double igual = 10*10*10*10*10*10*10*10*10*10*10*10*10*10*10*10*10*10;
//	cout<<igual<<endl;
//
//
//	  int n;
//	  n=70;
//	  cout << hex << n << endl;
//	  cout << dec << n << endl;






//	long double mydouble2 = 1234567890012345678901234567890123456789012345678901234567890123;
//	cout<<mydouble2<<endl;
//
//	long double resta = 1234567890012345678901234567890123456789012345678901234567890123 - 1234567890012345678901234567890123456789012345678901234567890120;
//	cout<<resta<<endl;


//	cout << MD5("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789")<<endl;
//  cout << MD5("D")<<endl;
//	cout << MD5("d")<<endl;
//	cout << MD5("di")<<endl;
//	cout << MD5("div")<<endl;
//	cout << MD5("ivi")<<endl;
//	cout << MD5("divi")<<endl;
//	cout << MD5("divi-+sd210ac98-.,<{°!#$%&/()=?")<<endl;


	//testBug();
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
