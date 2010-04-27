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
	createNewBucket(1);
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

Bucket* Hash::createNewBucket(int depth){
	VarRegister* varRegister = new VarRegister();
	varRegister->setValue(depth);
	Block* block = this->hashFile->getNewBlock();
	block->addRegister(*varRegister);
	this->hashFile->saveBlock(block);
	delete varRegister;
	return new Bucket(block);
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

//	loadResultEnum result = bucket->insert(sid);
//	//UNDERFLOW_LOAD=0, NORMAL_LOAD ,OVERFLOW_LOAD
//	if (result == UNDERFLOW_LOAD)
//		printf("hubo UNDERFLOW_LOAD");
//	else if (result == OVERFLOW_LOAD)
//		printf("hubo OVERFLOW_LOAD");
//	else if (result == NORMAL_LOAD)
//			printf("hubo NORMAL_LOAD");
//
//
//	this->hashFile->saveBlock(bucket->getBlock());

	//si se pudo agregar en el bucket lo guardo
	if ( bucket->insert(sid) ){
		this->hashFile->saveBlock(bucket->getBlock());
	}
	else{  //hubo desborde
		printf("\nHubo desborde en el bucket: %i. ",bucket->getNumber());
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla){
			printf("Entro por td=tamTabla=%i.\n",td);
			this->hashTable->duplicate();
			int nuevoTamTabla = tamTabla * 2;
			//TODO: aca ver en la lista de bqs libres si puedo rescatar algun bq, sino creo un bq nuevo

			Bucket *bucketNuevo = createNewBucket(nuevoTamTabla);

			this->hashTable->changeFirstTimeInTable(bucket->getNumber(),bucketNuevo->getNumber());

			bucket->duplicateDepth();

			//TODO aca hay que calcular todas las ctas de nuevo

			this->hashFile->saveBlock(bucket->getBlock());
			this->hashFile->saveBlock(bucketNuevo->getBlock());
			delete bucketNuevo;

		}

		else{
			printf("Entro por td!=tamTabla (%i!=%i).\n",td,tamTabla);
			bucket->duplicateDepth();
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());

			//TODO en realidad no se usa este metodo, hay que hacer uno nuevo, dsp preguntame adrian cualq cosa
			//this->hashTable->verifyJumps(calculateHashFunction(sid->getKey()), bucketNuevo->getDepth() / 2);
			this->hashTable->jumpAndReplace(bucketNumber,bucketNuevo->getDepth(),bucketNuevo->getNumber());

			//TODO revisar esto del rehash (ni lo mire= soy pablo)
			this->reHash(bucket); // Redispersa los registros del bloque del bucket.
			this->add(sid);
			delete bucketNuevo;
		}


	}

	delete bucket;
	return 0;
}

void Hash::print() {
	unsigned int i = 1;
	Bucket* bucket;
	Block* actualBlock = this->hashFile->getBlock(i);
	this->hashTable->print();
	printf("\nHashFile: \n");
	while (actualBlock != NULL) {
		printf("Bucket %i : ",i);
		bucket = new Bucket(actualBlock);
		bucket->print();
		delete bucket;
		i++;
		actualBlock = this->hashFile->getBlock(i);
		printf("\n");
	}
}
