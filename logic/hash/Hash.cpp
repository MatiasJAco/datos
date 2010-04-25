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
	this->inicializeHashFile();
}

Hash::~Hash() {
	// TODO Auto-generated destructor stub
}

StringInputData* Hash::get(int key) {
	int size = this->hashTable->getSize();
	int blockPositionInTable = key % size;
	int blockNumber = this->hashTable->getNumberOfBucketInHash(blockPositionInTable);

	/* Obtendrá el registro que tiene el dato deseado. */
	//file.getRegister(blockNumber);
	return new StringInputData();
}

void Hash::inicializeHashFile(){
	int depth=1;
	VarRegister* varRegister = new VarRegister();
	varRegister->setValue((char*)&depth, sizeof(depth));
	Block* block = this->hashFile->getNewBlock();
	block->addRegister(*varRegister);
	this->hashFile->saveBlock(block);
	delete block;
	delete varRegister;
}


int Hash::calculateHashFunction(StringInputData* sid) {
	return 	sid->getKey() % this->hashTable->getSize();
}

int Hash::getNumberOfBucket(StringInputData* sid) {
	//incremento en uno el valor porque el metodo getBlock() no acepta ceros (0)
	int result = 1;
	result += this->hashTable->getNumberOfBucketInHash(calculateHashFunction(sid));
	return result;
}

bool Hash::existsElement(StringInputData* sid) {
	unsigned int bucketNumber = this->getNumberOfBucket(sid);
	Bucket* bucket = new Bucket(this->hashFile->getBlock(bucketNumber));
	return bucket->existsRegister(sid->getKey());
}

int Hash::add(StringInputData* sid) {
	//TODO: por ahora solo llama al add del bucket. Ver si falta algo mas

	// Verifico unicidad
	if (existsElement(sid)){
		return 1;
	}

	unsigned int bucketNumber = this->getNumberOfBucket(sid);


	// Se obtiene el bloque desde el disco
	Block* block = this->hashFile->getBlock(bucketNumber);
	if (block == NULL) {
		printf("Hubo un error al intentar leer un bloque que no existia");
		return -1;
	}

	Bucket* bucket = new Bucket(block);
	//agregar td al bloque en el 1er reg del block

	//si se pudo agregar en el bucket lo guardo
	if ( bucket->add(sid) ){
		this->hashFile->saveBlock(bucket->getBlock());
	}
	else{  //hubo desborde



	}

	delete bucket;

	return 0;
}


void Hash::print(){

	//TODO: Faltar implementar este metodo en el BlockFile
	//this->hashFile->print();

}
