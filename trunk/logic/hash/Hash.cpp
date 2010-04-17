/*
 * Hash.cpp
 *
 *  Created on: Apr 16, 2010
 *      Author: Adrián Bernardi
 */

#include "Hash.h"
#include <sstream>
#include <iostream>
#include "../../logic/input/StringInputData.h"

Hash::Hash() {
	this->hashTable->createFile();
}

Hash::~Hash() {
	// TODO Auto-generated destructor stub
}

void Hash::add(StringInputData* sid) {
	int size = this->hashTable->getSize();
	int key = sid->getKey();
	int blockPositionInTable = key % size;
	int blockNumber = this->hashTable->getNumberOfBucketInHash(blockPositionInTable);
	cout << "Key: " << key << " Size: " << size << " Position: " << blockPositionInTable << " Block number: " << blockNumber << endl;

	/* Guardará el dato ingresado por el usuario en el bloque "blockNumber". */
	//file.saveRegister(sid, blockNumber);
}
