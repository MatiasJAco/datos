#include <iostream>
#include <sstream>
#include "../common/hash/Table.h"
#include "../logic/input/StringInputData.h"
using namespace std;

int main(){
	stringstream ss (stringstream::in | stringstream::out);
	ss.str("paytiti");
	StringInputData* sid = new StringInputData();
	sid->setKey(34);
	sid->setValue(ss);
	sid->getKey();

	Table myTable;
	myTable.createFile();
	int sizeOfTable = myTable.getSize();
	int listElementsTable[sizeOfTable];

	myTable.parse(listElementsTable);
	myTable.print(listElementsTable,sizeOfTable);

	myTable.modifyRegister(2,50);
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

	myTable.modifyRegister(70,23);
	sizeOfTable = myTable.getSize();
	int listElementsTable6[sizeOfTable];
	myTable.parse(listElementsTable6);
	myTable.print(listElementsTable6,sizeOfTable);

	return 0;
}
