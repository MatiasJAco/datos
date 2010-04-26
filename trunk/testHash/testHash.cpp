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

void testAdd() {
	/* Se toma el dato que ingresa el usuario. */
	stringstream ss (stringstream::in | stringstream::out);
	ss.str("paytiti");
	StringInputData* sid = new StringInputData();
	sid->setKey(34);
	sid->setValue(ss.str());

	Hash* hash = new Hash();
	hash->add(sid);
	hash->print();

}

int main(){
	//testTable();
	//testTable2();
	//testTable3();
	testAdd();
	printf("paso!");
	return 0;
}
