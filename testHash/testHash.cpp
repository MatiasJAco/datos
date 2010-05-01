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

//	hash->erase(11);
	hash->erase(22);

	hash->print();
}

void tests() {
	Hash* hash = new Hash();
	/* Se toma el dato que ingresa el usuario. */
	char value[8] = "paytiti";
	for (int i = 1; i<=61;i++){
		StringInputData* sid = createSid(i,value);
		hash->add(sid);
		delete sid;
	}
//	hash->print();
	for (int i = 62; i<=70;i++){
		StringInputData* sid = createSid(i,value);
		hash->add(sid);
		delete sid;
	}

//	hash->print();
	//@return int Retorna 1 si el sid no existe;0 si fue cambiado; -1 si hubo algun problema
//	char newValue[15]= "______________";
//	bool result = hash->modify(12,newValue);
//	if (result==1)
//		cout<<endl<<"NO existe el sid"<<endl;
//	else if (result==-1)
//		cout<<endl<<"Hubo algun prob"<<endl;
//	else
//			cout<<endl<<"lo cambio!"<<endl;


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
}





int main(){
	//testTable();
	//testTable2();
	//testTable3();
	//testTable4();
	//testDelete();
	tests();
	printf("\npaso test!");

	return 0;
}
