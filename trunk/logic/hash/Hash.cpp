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
	this->hashFile = new BlockFile();
	this->hashFile->open("./hash.bin", 512);
}

Hash::~Hash() {
	// TODO Auto-generated destructor stub
}

void Hash::add(StringInputData* sid) {
	int hashTableSize = this->hashTable->getSize();
	int key = sid->getKey();
	int blockPositionInTable = key % hashTableSize;
	unsigned int bucketNumber = this->hashTable->getNumberOfBucketInHash(blockPositionInTable);
	cout << "Key: " << key << " Size: " << hashTableSize << " Position: " << blockPositionInTable << " Bucket number: " << bucketNumber << endl;

	VarRegister* varRegister = new VarRegister();
	varRegister->setValue((char*)sid->getValue().c_str(), sid->getValue().size()+1);

	/* Se intenta obtener el bloque desde el disco: */
	Block* block = this->hashFile->getBlock(bucketNumber);

	/* Si no encuentra el bloque del archivo en donde debería ir la clave, crea el bucket junto a su respectivo bloque: */
	if (block == NULL) {
		this->buckets.push_back(Bucket(bucketNumber, hashTableSize));

		Block* block = this->hashFile->getNewBlock();
		block->addRegister(*varRegister);
		this->hashFile->saveBlock(block);
	} else {
		/* Si el bloque posee suficiente espacio para guardar un registro más, lo guarda: */
		if (block->getRemainingSpace() >= varRegister->getDiskSize()) {
			block->addRegister(*varRegister);
			this->hashFile->saveBlock(block);
		} else { /* En caso contrario, se duplica la tabla y se guarda el registro en un bloque nuevo. */
			list<Bucket>::iterator bucket = this->buckets.begin();
			bool found = false;
			while((!found) && (bucket != this->buckets.end())) {
				if (bucket->getNumber() == bucketNumber) {
					bucket->setDepth(2); // TODO ver que valor vá acá.
				}
				found = true;
				bucket++;
			}
			//TODO completar qué hacer al dar de alta cuando se duplica la tabla.
		}
	}
}

StringInputData* Hash::get(int key) {
	int size = this->hashTable->getSize();
	int blockPositionInTable = key % size;
	int blockNumber = this->hashTable->getNumberOfBucketInHash(blockPositionInTable);

	/* Obtendrá el registro que tiene el dato deseado. */
	//file.getRegister(blockNumber);
	return new StringInputData();
}
