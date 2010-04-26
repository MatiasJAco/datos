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
	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Bucket* bucket = new Bucket(this->hashFile->getBlock(bucketNumber));
	if (bucket->existsRegister(key)) {
		VarRegister varRegister = bucket->getRegister(key);
		StringInputData* stringInputData = new StringInputData();
		stringInputData->toData(varRegister.getValue());
		return stringInputData;
	}
	return NULL;
}

void Hash::inicializeHashFile(){
	createNewBlock(1);
}

int Hash::calculateHashFunction(int key) {
	return key % this->hashTable->getSize();
}

int Hash::getNumberOfBucket(int key) {
	//incremento en uno el valor porque el metodo getBlock() no acepta ceros (0)
	int result = 1;
	result += this->hashTable->getNumberOfBucketInHash(calculateHashFunction(key));
	return result;
}

bool Hash::existsElement(StringInputData* sid) {
	unsigned int bucketNumber = this->getNumberOfBucket(sid->getKey());
	Bucket* bucket = new Bucket(this->hashFile->getBlock(bucketNumber));
	bool result = bucket->existsRegister(sid->getKey());
	delete bucket;
	return result;
}

int Hash::reHash(Bucket* bucket) {
	VarRegister varRegister;
	bucket->getBlock()->restartCounter();

	while (bucket->getBlock()->hasNextRegister()) {
		varRegister = bucket->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		this->add(sid);
		bucket->getBlock()->deleteRegister();
	}
	return -1;
}

int Hash::createNewBlock(int depth){
	VarRegister* varRegister = new VarRegister();
	varRegister->setValue(depth);
	Block* block = this->hashFile->getNewBlock();
	block->addRegister(*varRegister);
	this->hashFile->saveBlock(block);
	int bloqueNuevo = block->getBlockNumber();
	delete block;
	delete varRegister;
	return bloqueNuevo;
}

int Hash::add(StringInputData* sid) {
	// Verifico unicidad
	if (existsElement(sid)){
		return 1;
	}

	unsigned int bucketNumber = this->getNumberOfBucket(sid->getKey());

	// Se obtiene el bloque desde el disco
	Block* block = this->hashFile->getBlock(bucketNumber);
	if (block == NULL) {
		printf("Hubo un error al intentar leer un bloque que no existia");
		return -1;
	}

	Bucket* bucket = new Bucket(block);
	//agregar td al bloque en el 1er reg del block

	int numeroBloqueDesbordado = bucket->insert(sid);
	//si se pudo agregar en el bucket lo guardo
	if ( numeroBloqueDesbordado==-1 ){
		this->hashFile->saveBlock(bucket->getBlock());
	}
	else{  //hubo desborde
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla){
			this->hashTable->duplicate();
			int nuevoTamTabla = tamTabla * 2;
			//TODO: aca ver en la lista de bqs libres si puedo rescatar algun bq, sino creo un bq nuevo

			int bloqueNuevo = createNewBlock(nuevoTamTabla);

			this->hashTable->changeFirstTimeInTable(numeroBloqueDesbordado,bloqueNuevo);

		}

		else{
			bucket->setDepth(bucket->getDepth()*2);
			Block* block2 = this->hashFile->getNewBlock();
			Bucket* bucket2 = new Bucket(block2);
			bucket2->setDepth(bucket2->getDepth()*2);

			this->hashTable->verifyJumps(calculateHashFunction(sid->getKey()), bucket2->getDepth() / 2);

			this->reHash(bucket); // Redispersa los registros del bloque del bucket.
			this->add(sid);
			delete bucket2;
		}


	}

	delete bucket;
	return 0;
}

void Hash::print() {
	unsigned int i = 1;
	Bucket* bucket;
	Block* actualBlock = this->hashFile->getBlock(i);

	while (actualBlock != NULL) {
		bucket = new Bucket(actualBlock);
		bucket->print();
		delete bucket;
		i++;
		actualBlock = this->hashFile->getBlock(i);
	}
}
