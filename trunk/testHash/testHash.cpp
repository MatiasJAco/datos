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
	//testTable();
	test2();
	return 0;
}
