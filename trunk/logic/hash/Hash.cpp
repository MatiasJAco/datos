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

Bucket* Hash::createNewBucket(int depth){
	VarRegister* varRegister = new VarRegister();
	varRegister->setValue(depth);
	Block* block = this->hashFile->getNewBlock();
	Bucket *bucket = new Bucket(block);
	block->addRegister(*varRegister);
	this->saveBucket(bucket);
	delete varRegister;
	return bucket;
}

Bucket* Hash::tryToInsertNewSid(StringInputData* sid, int & result) {
	unsigned int bucketNumber = this->getNumberOfBucket(sid->getKey());

	// Se obtiene el bloque desde el disco
	Block* block = this->hashFile->getBlock(bucketNumber);
	Bucket* bucket = new Bucket(block);
	result = bucket->insertRegister(sid);
	return bucket;
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
		printf("Hubo desborde en el bucket: %i. ",bucket->getNumber());
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla) {
			cout << "Entro por td=tamTabla=" << td << endl;
			this->hashTable->duplicate();
			Bucket *bucketNuevo = createNewBucket(tamTabla * 2);
			int numeroBuquet = bucket->getNumber();
			int numeroBuquetNuevo = bucketNuevo->getNumber();
			this->hashTable->changeFirstTimeInTable(numeroBuquet,numeroBuquetNuevo);
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			delete bucket;
			this->add(sid);
//			this->print();
			delete bucketNuevo;

		} else {
			printf("Entro por td!=tamTabla (%i!=%i).\n",td,tamTabla);
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());
			this->hashTable->jumpAndReplace(this->getNumberOfBucket(sid->getKey()),bucketNuevo->getDepth(),bucketNuevo->getNumber());
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->add(sid);
//			this->print();
			delete bucketNuevo;
			//TODO no hay qeu poner un delete bucket aca?
		}
	} else {
		return insertResult;
	}
	//TODO ver si hay que hacer el delete
	//delete bucket;
	return 0;
}
int Hash::modify(int key, char* newValue) {
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
			cout << "Se produjo un error al intentar eliminar el registro cuya clave es: " << key << endl;
			delete bucket;
			return -1;
		} else { // Si se pudo borrar exitosamente, reviso cuantos registros le quedan al bloque.

			this->saveBucket(bucket);
			unsigned int registerAmount = block->getRegisterAmount();
			int element = this->hashTable->verifyJumps(this->calculateHashFunction(key), bucket->getDepth()/2);
//			print();
			if ((registerAmount == 1) && (bucket->getDepth() == this->hashTable->getSize()) && (element != -1)) {
				//intento liberar el bloque
				if (!this->hashFile->deleteBlock(bucketNumber))
					return -1;
				//hago las modificaciones necesarias en la tabla
				this->hashTable->modifyRegister(this->calculateHashFunction(key),element);

				//-------------------------------
				Block *blockAux = this->hashFile->getBlock(element+1);
				Bucket * bucketAux = new Bucket(blockAux);
				int tdElement = bucketAux->getDepth();
				delete bucketAux;
				this->hashTable->jumpAndReplace(this->calculateHashFunction(key),tdElement,element);

				Bucket * bucketAux2 = new Bucket(blockAux);
				if (!bucketAux2->divideDepth()){
					delete bucket;
					delete bucketAux2;
					return -1;
				}
				else
					this->saveBucket(bucketAux2);
				delete bucketAux2;

//				print();
				this->hashTable->verifyAndDivide();
//				print();

				//-------------------------------
			}
			delete bucket;
		}
	} else {
		cout << "No existe la clave: " << key << endl;
		return 1;
	}
	return 0;
}

void Hash::print() {
	unsigned int i = 1;
	Bucket* bucket;
	Block* actualBlock = this->hashFile->getBlock(i);
	this->hashTable->print();

	//TODO : cambiar esto y usar el this->hashFile->getFreeBlockList() y restarle uno a cada elem de la lista
	cout << "Bloques libres: " << this->hashFile->getFreeBlockString() << endl;

	printf("\nHashFile: \n");
	while (actualBlock != NULL) {
		int numeroReal = i-1;
		cout<<"Bucket "<< numeroReal<<": ";
		bucket = new Bucket(actualBlock);
		bucket->print();
		delete bucket;
		i++;
		actualBlock = this->hashFile->getBlock(i);
		printf("\n");
	}
}
