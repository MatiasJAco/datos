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
		VarRegister varRegister = block->getNextRegister(false);
		sid = new StringInputData();
		sid->toData(varRegister.getValue());
		listaDatos.push_back(*sid);
		delete sid;
		loadResultEnum load = NORMAL_LOAD;
		deleteResult = block->deleteRegister(load);
		if (deleteResult == false) {
			cout << "No pudo borrarse el registro: " << sid->getKey() << " del bloque: " << bucketDesbordado->getNumber() << endl;
		}
		this->hashFile->saveBlock(block);
	}
	//almaceno el td del bloque
	VarRegister* varReg = new VarRegister();
	varReg->setValue(bucketDesbordado->getDepth());
	block->addRegister(*varReg);
	this->hashFile->saveBlock(block);
	delete varReg;

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
	if (existsElement(sid)){
		return 1;
	}

	int insertResult;
	Bucket * bucket = tryToInsertNewSid(sid,insertResult);
	if (insertResult == 0) { //si se pudo agregar en el bucket lo guardo
		this->hashFile->saveBlock(bucket->getBlock());
	} else if (insertResult == 1) {  //hubo desborde
		printf("Hubo desborde en el bucket: %i. ",bucket->getNumber());
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla) {
			cout << "Entro por td=tamTabla=" << td << endl;
			this->hashTable->duplicate();
			Bucket *bucketNuevo = createNewBucket(tamTabla * 2);
			this->hashTable->changeFirstTimeInTable(bucket->getNumber(),bucketNuevo->getNumber());
			bucket->duplicateDepth();
			this->hashFile->saveBlock(bucket->getBlock());
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->add(sid);
			delete bucketNuevo;
		} else {
			printf("Entro por td!=tamTabla (%i!=%i).\n",td,tamTabla);
			bucket->duplicateDepth();
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());
			this->hashTable->jumpAndReplace(this->getNumberOfBucket(sid->getKey()),bucketNuevo->getDepth(),bucketNuevo->getNumber());
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
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

int Hash::modify(int key, string newValue) {
	StringInputData* sid1 = new StringInputData();
	sid1->setKey(key);
	sid1->setValue(newValue); // no importa el valor que le paso porque busca por key
	// Verifico unicidad
	if (!existsElement(sid1)){
		return 1;
	}
	delete sid1;

	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Block* block = this->hashFile->getBlock(bucketNumber);
	block->restartCounter();
	VarRegister varReg = block->getNextRegister(true);

	StringInputData* sid = new StringInputData();
	sid->toData(varReg.getValue());
	unsigned int dataSize = newValue.size();;
	char* valueReg = new char[dataSize];
	sid->setValue(newValue);
	varReg.setValue(sid->toStream(valueReg),dataSize);

	loadResultEnum result;
	bool result2 = block->modifyRegister(varReg,result);

	if (OVERFLOW_LOAD == result) {
		cout << "Error al intentar modificar el tamaño de dispersion de un bloque. Este no puede modificarse. Causado por Overflow" << endl;
		return -1;
	}
	else if (UNDERFLOW_LOAD == result) {
		cout << "Error al intentar modificar el tamaño de dispersion de un bloque. Este no puede modificarse. Causado por Underflow" << endl;
		return -1;
	}

	delete sid;
	if (!this->hashFile->saveBlock(block))
		return -1;

	return 0;
}

int Hash::erase(int key) {
	StringInputData* sid = new StringInputData();
	sid->setKey(key);
	bool exists = this->existsElement(sid);
	bool result = false;

	if (exists) {
		unsigned int bucketNumber = this->getNumberOfBucket(key);
		Block* block = this->hashFile->getBlock(bucketNumber);
		Bucket* bucket = new Bucket(block);
		bucket->setDepth(bucket->getDepthFromHashFile());
		result = bucket->deleteRegister(key);
		if (result == false) {
			cout << "Se produjo un error al intentar eliminar el registro cuya clave es: " << key << endl;
		} else { // Si se pudo borrar exitosamente, reviso cuantos registros le quedan al bloque.
			unsigned int registerAmount = block->getRegisterAmount();

			int element = this->hashTable->verifyJumps(this->calculateHashFunction(key), bucket->getDepth());

			if ((registerAmount == 0) && (bucket->getDepth() == this->hashTable->getSize()) && (element != -1)) {
				this->hashTable->verifyAndDivide();
				this->hashFile->deleteBlock(bucketNumber);
			}
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
