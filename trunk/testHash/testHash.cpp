#include <iostream>
#include <sstream>
#include "../common/hash/Table.h"
#include "../logic/input/StringInputData.h"
#include "../logic/hash/Hash.h"

using namespace std;

void test1() {
	Table myTable;
	myTable.createFile();
	int sizeOfTable = myTable.getSize();
	int listElementsTable[sizeOfTable];

	myTable.parse(listElementsTable);
	myTable.print(listElementsTable,sizeOfTable);

	myTable.modifyRegister(1,22);
	sizeOfTable = myTable.getSize();
	int listElementsTable2[sizeOfTable];
	myTable.parse(listElementsTable2);
	myTable.print(listElementsTable2,sizeOfTable);

	myTable.duplicate();
	sizeOfTable = myTable.getSize();
	int listElementsTable3[sizeOfTable];
	myTable.parse(listElementsTable3);
	myTable.print(listElementsTable3,sizeOfTable);

	myTable.duplicate();
	sizeOfTable = myTable.getSize();
	int listElementsTable4[sizeOfTable];
	myTable.parse(listElementsTable4);
	myTable.print(listElementsTable4,sizeOfTable);

	myTable.duplicate();
	sizeOfTable = myTable.getSize();
	int listElementsTable5[sizeOfTable];
	myTable.parse(listElementsTable5);
	myTable.print(listElementsTable5,sizeOfTable);

	/*myTable.modifyRegister(70,23);
	sizeOfTable = myTable.getSize();
	int listElementsTable6[sizeOfTable];
	myTable.parse(listElementsTable6);
	myTable.print(listElementsTable6,sizeOfTable);*/

	if (myTable.verifyAndDivide()!= 0)
		printf("\nno se puede dividir");
	else printf("\nSI se puede dividir");

	sizeOfTable = myTable.getSize();
	int listElementsTable7[sizeOfTable];
	myTable.parse(listElementsTable7);
	myTable.print(listElementsTable7,sizeOfTable);
}

void test2() {
	/* Se toma el dato que ingresa el usuario. */
	stringstream ss (stringstream::in | stringstream::out);
	ss.str("paytiti");
	StringInputData* sid = new StringInputData();
	sid->setKey(34);
	sid->setValue(ss);

	Hash* hash = new Hash();
	hash->add(sid);

}

int main(){
	//test1();
	test2();
	return 0;
}
