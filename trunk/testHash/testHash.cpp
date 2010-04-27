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

void testAdd() {
	Hash* hash = new Hash();

	/* Se toma el dato que ingresa el usuario. */
	int key = 34;
	char value1[8] = "paytiti";
	StringInputData* sid1 = createSid(key,value1);

	key = 5;
	char value2[5] = "pepe";
	StringInputData* sid2 = createSid(key,value2);


	hash->add(sid1);
	//hash->add(sid2);
	hash->print();
	delete sid1;
	delete sid2;
}

int main(){
	//testTable();
	//testTable2();
	//testTable3();
	//testTable4();

	testAdd();
	printf("\npaso test!");

	return 0;
}
