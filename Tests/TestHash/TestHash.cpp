/*
 * TestHash.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: adrian
 */

#include "TestHash.h"

TestHash::TestHash() {
}

TestHash::~TestHash() {
}

void TestHash::testStringInputData(){
	StringInputData *fixture = new StringInputData();

	std::string key = "3";
	string value = "algo";

	fixture->setKey(key);
	fixture->setValue(value);

	char* streamData = new char[fixture->size()];

	fixture->toStream(streamData);

	StringInputData data;
	data.toData(streamData);

	cout << "new key "<<data.getKey()<<endl;
	cout << "new data "<<data.getValue()<<endl;

	bool eqkey = key==data.getKey();
	bool eqvalue = value==data.getValue();

	if (!eqkey)
		cout << "fallo en key"<< endl;
	else
		cout << "ok en key" << endl;

	if (!eqvalue)
		cout << "fallo en value" << endl;
	else
		cout << "ok en value" << endl;
}

void TestHash::testTable() {
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

void TestHash::testTable2(){
	Table myTable;
	myTable.createFile();
	myTable.print();
	myTable.changeFirstTimeInTable(24,444);
	myTable.print();
}

void TestHash::testTable3(){
	Table myTable;
	myTable.createFile();
	myTable.print();
	int result = myTable.verifyJumps(1,2);
	printf("\nRESULT : %i",result);
}

void TestHash::testTable4(){
	Table myTable;
	myTable.createFile();
	myTable.print();
	myTable.jumpAndReplace(6,5,23);
	myTable.print();
}

void TestHash::testModifyHash() {
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

void TestHash::testRemoveHash() {
	Hash* hash = new Hash();
	hash->insert("1","paytiti");
	hash->insert("2","pepe");
	hash->insert("3","luis");
	hash->print();
	hash->remove("2");
	hash->print();
	delete hash;
}

void TestHash::testRemoveHash2() {
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
void TestHash::testEjemplo(){
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
	hash->deleteGeneratedFiles();
	delete hash;
}

void TestHash::testGetKeys() {
	Hash* hash = new Hash();
	char value[131] = "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
	hash->insert("123",value);
	hash->insert("915",value);
	hash->insert("629",value);
	hash->insert("411",value);
	hash->insert("200",value);
	hash->insert("863",value);
	hash->remove("629");
	hash->insert("408",value);
	hash->insert("34",value);
	hash->insert("510",value);
	hash->remove("863");
	hash->insert("775",value);
	list<std::string> keys = hash->getKeys();
	std::string key = "";

	while (!keys.empty()) {
		key = keys.back();
		keys.pop_back();
		std::cout << "Key: " << key << std::endl;
	}
	hash->deleteGeneratedFiles();
	delete hash;
}

/* Muestra la cadena que representa al numero, por pantalla. */
void TestHash::testBigInt() {
	std::string s("0123456789012345678901234567890123456789012345678901234567890123");
	BigInteger f = stringToBigInteger(s);
	std::cout << f << std::endl;
}

/* Devuelve la cadena: 4d186321c1a7f0f354b297e8914ab240 */
void TestHash::testMd5() {
	MD5 md5("hola");
	std::cout << md5.hexdigest() << std::endl;
}

/* El resultado debe dar:
 * ======================
 * md5:  4d186321c1a7f0f354b297e8914ab240
 * bigint: 413010806030201120110071500150305041102090714080901041011020400
 * bigint mod 6 = 4 */
void TestHash::testHashFunction() {
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


void TestHash::testFreqTable()
{
        FrequencyTable *ft;
        FrequencyTable *ft2;
        FrequencyTable *ft3;
        FrequencyTable ft4;
        string serial, deserial;

        ft = new FrequencyTable();
        ft2 = new FrequencyTable();
        ft3 = new FrequencyTable();

        ft->setFrequency('a',2);
        ft->setFrequency('d',3);
        ft->setFrequency('c',4);
        ft->setFrequency('b',5);
        ft->setFrequency('/',5);
        ft->setFrequency('\\',7);
        ft->setFrequency(258,1000);
        ft->setFrequency(EOF_CHAR,5);
        ft->setFrequency(ESC_CHAR,5);

        ft->increaseFrequency('c',4);
        ft->increaseFrequency(ESC_CHAR,2);

        ft3->setFrequency('b',2);
        ft3->setFrequency('\\',2);
        ft3->setFrequency('j',2);
        ft3->setFrequency(ESC_CHAR,5);

        serial = ft->toString();

        cout << serial<<endl;

        ft2->deserialize(serial);
        ft2->increaseFrequency(ESC_CHAR,4);

        cout << ft2->toString()<<endl;


        cout<<"cum frec "<< ft->getCumFrequency('c')<<endl;
        cout<<"cum frec2 "<< ft->getCumFrequency('j')<<endl;
        cout<< "frec "<<ft->getFrequency('c')<<endl;
        cout<< "frec2 "<<ft->getFrequency('j')<<endl;
        cout <<"char"<< (char) 98<<endl;
        cout <<"esc char"<<ft2->getFrequency(ESC_CHAR)<<endl;
        cout <<"total1"<< ft->getFrequencyTotal()<<endl;
        cout <<"total2"<< ft2->getFrequencyTotal()<<endl;

        //ft->excludeFromTable(*ft2);

        ft4 = ft->excludeFromTable(*ft3);

        cout << "ft4 " << ft4.toString()<<endl;


        delete ft;
        delete ft2;
        delete ft3;
}

void TestHash::testBugRaro() {
	Hash* hash = new Hash();
	hash->insert("1", "50-1/257-1");
	StringInputData* sid2 = new StringInputData();
	hash->find("1", *sid2);

	std::cout << sid2->toString() << std::endl;
	delete sid2;
}

void TestHash::testPpmcHashComprimir() {
	std::string path = "./archivoAComprimir.txt";
	int maxContext = 5;//--------------------------------------------------CAMBIAR ACA EL contexto!!

	std::string previousCompressionFile = "archivoAComprimir.txt";
	previousCompressionFile.append(".ppmc");
	stringstream ss;
	ss << maxContext;
	previousCompressionFile.append(ss.str());

	std::remove(previousCompressionFile.c_str());
	GeneralStructure* hash = new Hash();
	Ppmc* ppmcHash = new PpmcHash(hash);
	ppmcHash->compress(path, maxContext);
	hash->deleteGeneratedFiles();
	delete ppmcHash;
}

void TestHash::testPpmcHashDescomprimir() {
	std::remove("archivoAComprimirDescomprimido.txt");
	GeneralStructure* hash = new Hash();
	Ppmc* ppmcHash = new PpmcHash(hash);
	ppmcHash->deCompress("./archivoAComprimir.txt.ppmc5");//---------------CAMBIAR ACA EL NUMERITO .ppmc"3"!!!
	hash->deleteGeneratedFiles();
	delete ppmcHash;
	delete hash;
}
