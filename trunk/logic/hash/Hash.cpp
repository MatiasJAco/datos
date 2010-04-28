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

int Hash::reHash(Bucket* bucketDesbordado) {
	Block* block = bucketDesbordado->getBlock();
	block->restartCounter();
	list<StringInputData> listaDatos;
	bool deleteResult = true;

	StringInputData* sid;
	while (block->hasNextRegister()) {
		VarRegister varRegister = block->getNextRegister(true);
		sid = new StringInputData();
		sid->toData(varRegister.getValue());
		listaDatos.push_back(*sid);
		delete sid;
		deleteResult = block->deleteRegister();
		if (deleteResult == false) {
			cout << "No pudo borrarse el registro: " << sid->getKey() << " del bloque: " << bucketDesbordado->getNumber() << endl;
		}
	}

	this->hashFile->saveBlock(bucketDesbordado->getBlock());

	while (!listaDatos.empty()) {
		StringInputData sid = listaDatos.front();
		this->add(&sid);
		listaDatos.pop_front(); // Borro el primer sid de la lista.
	}

	return 0;
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

Bucket* Hash::tryToInsertNewSid(StringInputData* sid, int & result) {
	unsigned int bucketNumber = this->getNumberOfBucket(sid->getKey());

	// Se obtiene el bloque desde el disco
	Block* block = this->hashFile->getBlock(bucketNumber);
	if (block == NULL) {
		cout<<"Hubo un error al intentar leer un bloque que no existia"<<endl;
		result = 2;
	}
	Bucket* bucket = new Bucket(block);
	result = bucket->insert(sid);
	return bucket;
}


int Hash::add(StringInputData* sid) {
	// Verifico unicidad
	//TODO desconmmentar esto
//	if (existsElement(sid)){
//		return 1;
//	}

	int insertResult;
	Bucket * bucket = tryToInsertNewSid(sid,insertResult);

	if (insertResult == 0) { //si se pudo agregar en el bucket lo guardo
		this->hashFile->saveBlock(bucket->getBlock());
	} else if (insertResult == 1) {  //hubo desborde
		printf("\nHubo desborde en el bucket: %i. ",bucket->getNumber());
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla) {
			cout << "Entro por td=tamTabla=" << td << endl;
			this->hashTable->duplicate();
			Bucket *bucketNuevo = createNewBucket(tamTabla * 2);
			this->hashTable->changeFirstTimeInTable(bucket->getNumber(),bucketNuevo->getNumber());
			bucket->duplicateDepth();
//			this->print();
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->add(sid);
			delete bucketNuevo;
		} else {
			printf("Entro por td!=tamTabla (%i!=%i).\n",td,tamTabla);
			bucket->duplicateDepth();
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());

			this->hashTable->jumpAndReplace(this->getNumberOfBucket(sid->getKey()),bucketNuevo->getDepth(),bucketNuevo->getNumber());

			this->reHash(bucket); // Redispersa los registros del bloque del bucket.
			this->add(sid);
			delete bucketNuevo;
		}
	} else {
		return insertResult;
	}
	//TODO ver si hay que hacer el delete
	//delete bucket;
	return 0;
}

int modify(int key, string value) {
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
