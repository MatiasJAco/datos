/*
 * Hash.cpp
 *
 *  Created on: Apr 16, 2010
 *      Author: Pablo Lisio / Adrián Bernardi
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
	this->hashFile->close();
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

Bucket* Hash::createNewBucket(int depth){
	VarRegister* varRegister = new VarRegister();
	varRegister->setValue(depth);
	Block* block = this->hashFile->getNewBlock();
	Bucket *bucket = new Bucket(block);
	bucket->setDepth(depth);
	block->addRegister(*varRegister);
	this->saveBucket(bucket);
	delete varRegister;
	bucketsUsedAmount++;	//se agrego un bucket al archivo Hash
	return bucket;
}

void Hash::inicializeHashFile(){
	Block* block = this->hashFile->getBlock(1);
	if (block == NULL)
		createNewBucket(1);
}

int Hash::calculateHashFunction(int key) {
	return key % this->hashTable->getSize();
}

void Hash::saveBucket(Bucket * bucket){
	this->hashFile->saveBlock(bucket->getBlock());
}

int Hash::getNumberOfBucket(int key) {
	//incremento en uno el valor porque el metodo getBlock() no acepta ceros (0)
	int result = 1;
	result += this->hashTable->getNumberOfBucketInHash(calculateHashFunction(key));
	return result;
}

bool Hash::existsElement(int key) {
	int aux = -1;
	return (this->existsElement(key,aux));
}
bool Hash::existsElement(int key, int & position) {
	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Bucket* bucket = new Bucket(this->hashFile->getBlock(bucketNumber));
	bool result = bucket->existsRegister(key,position);
	delete bucket;
	return result;
}

int Hash::reHash(Bucket* bucketDesbordado) {
	list<StringInputData> listaDatos;
	bucketDesbordado->getListOfSids(listaDatos);
	bucketDesbordado->empty();
	this->saveBucket(bucketDesbordado);

	//recorro toda la lista de sids y redisperso el bloque
	while (!listaDatos.empty()) {
		StringInputData sid = listaDatos.front();
		this->add(&sid);
		listaDatos.pop_front(); // Borro el primer sid de la lista.
	}
	return 0;
}

Bucket* Hash::tryToInsertNewSid(StringInputData* sid, int & result) {
	unsigned int bucketNumber = this->getNumberOfBucket(sid->getKey());

	// Se obtiene el bloque desde el disco
	Block* block = this->hashFile->getBlock(bucketNumber);
	Bucket* bucket = new Bucket(block);
	result = bucket->insertRegister(sid);
	return bucket;
}

int Hash::add(int clave, string valor) {
	StringInputData* sid = new StringInputData();
	sid->setKey(clave);
	sid->setValue(valor);
	bool result = this->add(sid);
	delete sid;
	return result;
}

int Hash::add(StringInputData* sid) {
	// Verifico unicidad
	if (existsElement(sid->getKey())){
		return 1;
	}

	int insertResult;
	Bucket * bucket = tryToInsertNewSid(sid,insertResult);
	if (insertResult == 0) { //si se pudo agregar en el bucket lo guardo
		this->saveBucket(bucket);
		delete bucket;
	} else if (insertResult == 1) {  //hubo desborde
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla) {
			this->hashTable->duplicate();
			Bucket *bucketNuevo = createNewBucket(tamTabla * 2);
			unsigned int numeroBuquet = bucket->getNumber();
			unsigned int numeroBuquetNuevo = bucketNuevo->getNumber();
			this->hashTable->changeFirstTimeInTable(numeroBuquet,numeroBuquetNuevo);
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			delete bucket;
			this->add(sid);
			delete bucketNuevo;
		} else {
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());
			this->hashTable->jumpAndReplace(this->calculateHashFunction(sid->getKey()),bucketNuevo->getDepth(),bucketNuevo->getNumber());
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->add(sid);
			delete bucketNuevo;
		}
	} else {
		return insertResult;
	}
	return 0;
}
int Hash::modify(int key, string newValue) {
	StringInputData* sid = new StringInputData();
	sid->setKey(key);
	bool exists = this->existsElement(sid->getKey());

	if (!exists) {
		return 1;
	} else {
		sid->setValue(newValue);
		int resultErase = this->erase(key);

		if (resultErase == 0) { // Si se pudo borrar correctamente el dato, se trata de reinsertar pero con el nuevo valor.
			int resultAdd = this->add(sid);
			if (resultAdd != 0) {
				return -1;
			}
		} else {
			return -1;
		}
	}

	return 0;
}

int Hash::erase(int key) {
	StringInputData* sid = new StringInputData();
	sid->setKey(key);
	bool exists = this->existsElement(key);
	bool result = false;

	if (exists) {
		unsigned int bucketNumber = this->getNumberOfBucket(key);
		Block* block = this->hashFile->getBlock(bucketNumber);
		Bucket* bucket = new Bucket(block);
		result = bucket->deleteRegister(key);

		if (result == false) {
			delete bucket;
			return -1;
		} else { // Si se pudo borrar exitosamente, reviso cuantos registros le quedan al bloque.

			this->saveBucket(bucket);
			unsigned int registerAmount = block->getRegisterAmount();

			unsigned int depth = bucket->getDepth();
			unsigned int tamTable = this->hashTable->getSize();
			int element = -1;
			bool soloLiberarBq = false;
			if ((depth>1)&&(tamTable>1))
				element = this->hashTable->verifyJumps(this->calculateHashFunction(key), depth/2);
			else if (bucketsUsedAmount > 1)
				soloLiberarBq = true;

			if (((registerAmount == 1) && (depth == tamTable) && (element != -1))  ||  ((registerAmount == 1)&& soloLiberarBq)) {
				//intento liberar el bloque
				if (!this->hashFile->deleteBlock(bucketNumber))
					return -1;

				if (soloLiberarBq)
					return 0;

				// Un bucket fue liberado
				bucketsUsedAmount--;

				//hago las modificaciones necesarias en la tabla
				this->hashTable->modifyRegister(this->calculateHashFunction(key),element);

				Block *blockAux = this->hashFile->getBlock(element+1);
				Bucket * bucketAux = new Bucket(blockAux);
				int tdElement = bucketAux->getDepth();
				delete bucketAux;
				this->hashTable->jumpAndReplace(this->calculateHashFunction(key),tdElement,element);

				Bucket * bucketAux2 = new Bucket(blockAux);
				if (!bucketAux2->divideDepth()){
					delete bucket;
					delete bucketAux2;
					return -1;  //esto no deberia de pasar nunca, pero se lanza el error de todos modos
				}
				else
					this->saveBucket(bucketAux2);
				delete bucketAux2;

				this->hashTable->verifyAndDivide();
			}
			delete bucket;
		}
	} else {
		return 1; // No existe la clave. Se devuelve 1.
	}
	return 0;
}

void Hash::print() {
	unsigned int i = 1;
	Bucket* bucket;
	Block* actualBlock = this->hashFile->getBlock(i);
	this->hashTable->print();

	cout << "Bloques libres: ";
	FreeBlockList freeBlockList = this->hashFile->getFreeBlockList();
	for (list<unsigned int>::iterator it = freeBlockList.begin(); it != freeBlockList.end(); it++)
	    cout << *it -1 << " | ";
	cout << endl;

	cout << "HashFile: " << endl;
	while (actualBlock != NULL) {
		int numeroReal = i-1;
		cout << "Bucket " << numeroReal << ": ";
		bucket = new Bucket(actualBlock);
		bucket->print();
		delete bucket;
		i++;
		actualBlock = this->hashFile->getBlock(i);
		cout << endl;
	}
	cout << endl;
}
