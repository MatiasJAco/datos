#include <iostream>
#include <sstream>
#include "../logic/structures/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/structures/hash/Hash.h"
#include "../logic/ppmc/md5/MD5.h"
#include "../logic/ppmc/bigint/BigIntegerLibrary.hh"
#include "../logic/ppmc/PpmcHash.h"

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

void testModify() {
	Hash* hash = new Hash();
	/* Se toma el dato que ingresa el usuario. */
	std::string valor = "paytiti";
	for (int i = 1; i<=5;i++){
		std::string clave;
		std::stringstream aux;
		aux << i;
		clave = aux.str();

		hash->insert(clave,valor);
	}

	hash->print();
	std::string newValue= "______________";
	try {
		hash->modify("3",newValue);
		hash->print();
		cout<<endl<< "TUVO QUE HABER MODIFICADO LA CLAVE 3"<<endl;
	}
	catch (HashException e){
		cout<<endl<< e.what()<<endl;
	}

	delete hash;
}

void testDelete() {
	Hash* hash = new Hash();

	hash->insert("1","paytiti");
	hash->insert("2","pepe");
	hash->insert("3","luis");

	hash->print();

	hash->remove("2");

	hash->print();
	delete hash;
}

void tests() {
	Hash* hash = new Hash();
	hash->print();
	/* Se toma el dato que ingresa el usuario. */
	std::string valor = "paytiti";
	for (int i = 1; i<=70;i++){
		std::string clave;
		std::stringstream aux;
		aux << i;
		clave = aux.str();
		hash->insert(clave,valor);
	}

	hash->remove("70");
	hash->remove("66");
	hash->remove("30");
	hash->remove("26");
	hash->remove("22");
	hash->remove("18");
	hash->remove("14");
	hash->remove("10");
	hash->remove("6");
	hash->remove("2");
	hash->remove("34");
	hash->remove("38");
	hash->remove("42");
	hash->remove("46");
	hash->remove("50");
	hash->remove("54");
	hash->remove("58");
	hash->remove("62");
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

	hash->insert("123", "paytiti");
	hash->print();
	hash->remove("123");
	hash->print();

	char value[131] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";

	cout<< "+123\n"<<endl;
	hash->insert("123",value);
	hash->print();


	//Ejemplo de como catchear una excepcion para el hash
//	try{
//		hash->insert("123",value);
//	}
//	catch(HashException &e)
//	{
//		cout << e.what() << endl;
//	}


	cout<< "+915\n"<<endl;
	hash->insert("915",value);
	hash->print();

	cout<< "+629\n"<<endl;
	hash->insert("629",value);
	hash->print();

	cout<< "+411\n"<<endl;
	hash->insert("411",value);
	hash->print();

	cout<< "+200\n"<<endl;
	hash->insert("200",value);
	hash->print();

	cout<< "+863\n"<<endl;
	hash->insert("863",value);
	hash->print();

	cout<< "-629\n"<<endl;
	hash->remove("629");
	hash->print();

	cout<< "+408\n"<<endl;
	hash->insert("408",value);
	hash->print();

	cout<< "+34\n"<<endl;
	hash->insert("34",value);
	hash->print();

	cout<< "+510\n"<<endl;
	hash->insert("510",value);
	hash->print();

	cout<< "-863\n"<<endl;
	hash->remove("863");
	hash->print();

	cout<< "+775\n"<<endl;
	hash->insert("775",value);
	hash->print();

	cout<<"modify value 123"<<endl;
	hash->modify("123","pepitooooooooo");
	hash->print();

	cout<<"pruebo el find de hash con 123"<<endl;
	StringInputData sid;
	try{
		hash->find("123",sid);
		cout << sid.toString() << endl;
	}
	catch (HashException e) {
		cout<< e.what()<<endl;
	}

	delete hash;
}

void testBug(){
	Hash* hash = new Hash();
	char value[8] = "paytiti";
	hash->insert("12",value);
	hash->print();
	hash->remove("12");
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

/* El resultado debe dar:
 * ======================
 * md5:  4d186321c1a7f0f354b297e8914ab240
 * bigint: 413010806030201120110071500150305041102090714080901041011020400
 * bigint mod 6 = 4 */
void testHashFunction() {
	MD5 md5("paytiti");
	std::string s(md5.hexdigest());
	std::cout << s << std::endl;
	int i = 0;
	std::string nueva = "";

	while(i < 32) {
		if (s.substr(i,1).compare("0") == 0) {
			nueva.append("00");
		} else if (s.substr(i,1).compare("1") == 0) {
			nueva.append("01");
		} else if (s.substr(i,1).compare("2") == 0) {
			nueva.append("02");
		} else if (s.substr(i,1).compare("3") == 0) {
			nueva.append("03");
		} else if (s.substr(i,1).compare("4") == 0) {
			nueva.append("04");
		} else if (s.substr(i,1).compare("5") == 0) {
			nueva.append("05");
		} else if (s.substr(i,1).compare("6") == 0) {
			nueva.append("06");
		} else if (s.substr(i,1).compare("7") == 0) {
			nueva.append("07");
		} else if (s.substr(i,1).compare("8") == 0) {
			nueva.append("08");
		} else if (s.substr(i,1).compare("9") == 0) {
			nueva.append("09");
		} else if (s.substr(i,1).compare("a") == 0) {
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
	BigInteger g = stringToBigInteger("6");
	std::cout << g << std::endl;
	std::cout << (f % g).toInt() << std::endl;
}

/* Guarda el contexto "ABC" con la letra "A" y el Escape. Ambos tienen 1 ocurrencia. */
void testPpmc1() {
	PpmcHash* ppmcHash = new PpmcHash();
	ppmcHash->createContext("ABC");
	ppmcHash->addCharacterToContext("ABC","A");

	/* Busca cantidad de ocurrencias de "A" y de ESCAPE en el contexto "ABC". */
	if ((ppmcHash->getCharacterOccurrences("ABC","A") == 1) && (ppmcHash->getCharacterOccurrences("ABC","*") == 1)) {
		std::cout << "ok test ppmc 1" << std::endl;
	} else {
		std::cout << "fallo test ppmc 1" << std::endl;
	}
}

/* Guarda el contexto "ABC". Letra "A": 11 ocurrencias. Escape: 1 ocurrencia. */
void testPpmc2() {
	PpmcHash* ppmcHash = new PpmcHash();
	ppmcHash->createContext("ABC");
	ppmcHash->addCharacterToContext("ABC","A");
	for (int i = 0; i < 10; i++) {
		ppmcHash->increaseFrequency("ABC","A");
	}
	/* Busca cantidad de ocurrencias de "A" y de ESCAPE en el contexto "ABC". */
	if ((ppmcHash->getCharacterOccurrences("ABC","A") == 11) && (ppmcHash->getCharacterOccurrences("ABC","*") == 1)) {
		std::cout << "ok test ppmc 2" << std::endl;
	} else {
		std::cout << "fallo test ppmc 2" << std::endl;
	}
}

/* Crea contexto "ABC". Verifica que el caracter "A" no exista. */
void testPpmc3() {
	PpmcHash* ppmcHash = new PpmcHash();
	ppmcHash->createContext("ABC");

	if (!ppmcHash->existsCharacterInContext("ABC","A")) {
		std::cout << "ok test ppmc 3" << std::endl;
	} else {
		std::cout << "fallo test ppmc 3" << std::endl;
	}
}

/* Crea contexto "ABC". Carga el caracter "X" y verifica que exista el mismo. */
void testPpmc4() {
	PpmcHash* ppmcHash = new PpmcHash();
	ppmcHash->createContext("ABC");
	ppmcHash->addCharacterToContext("ABC","X");

	if (ppmcHash->existsCharacterInContext("ABC","X")) {
		std::cout << "ok test ppmc 4" << std::endl;
	} else {
		std::cout << "fallo test ppmc 4" << std::endl;
	}
}

/* Crea contexto "ABC" con 2 caracteres ("A" y el "B") con 1 ocurrencia cada uno. */
void testPpmc5() {
	PpmcHash* ppmcHash = new PpmcHash();
	ppmcHash->createContext("ABC");
	ppmcHash->addCharacterToContext("ABC","A");
	ppmcHash->addCharacterToContext("ABC","B");

	if ((ppmcHash->existsCharacterInContext("ABC","A")) && (ppmcHash->existsCharacterInContext("ABC","B"))) {
		std::cout << "ok test ppmc 5" << std::endl;
	} else {
		std::cout << "fallo test ppmc 5" << std::endl;
	}
}

/* Crea contexto "ABC". Carga los caracteres "A" y el "B" con 1 ocurrencia cada uno. */
void testPpmc6() {
	PpmcHash* ppmcHash = new PpmcHash();
	ppmcHash->createContext("ABC");
	ppmcHash->addCharacterToContext("ABC","A");
	ppmcHash->addCharacterToContext("ABC","B");
	ppmcHash->increaseFrequency("ABC","A");
	ppmcHash->increaseFrequency("ABC","B");
	ppmcHash->increaseFrequency("ABC","B");

	if ((ppmcHash->getCharacterOccurrences("ABC","A") == 2) && (ppmcHash->getCharacterOccurrences("ABC","B") == 3) && (ppmcHash->getTotalOccurencesFromContext("ABC") == 6)) {
		std::cout << "ok test ppmc 6" << std::endl;
	} else {
		std::cout << "fallo test ppmc 6" << std::endl;
	}
}

int main(int argc, const char* argv[]){
	//testTable();
	//testTable2();
	//testTable3();
	//testTable4();
	//testDelete();
	//tests();
	testEjemplo();
	//testModify();
	//testBigInt();
	//testMd5();
	//testHashFunction();

	//testPpmc1();
	//testPpmc2();
	//testPpmc3();
	//testPpmc4();
	//testPpmc5();
	//testPpmc6();

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
//		StringInputData* sid = hash->(clave);
//		if (sid != NULL) {
//			cout << sid->toString() << endl;
//		} else {
//			cout << "No se encontro la clave " << clave << endl;
//		}
//	} else if (operacion == "-I") {
//		cout << "Ingresando la clave" << clave << " con el valor " << valor << "..." << endl;
//		int addResult = hash->insert(clave, valor);
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
//		int eraseResult = hash->remove(clave);
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
