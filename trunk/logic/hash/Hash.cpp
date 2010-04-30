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
	Block* block = bucketDesbordado->getBlock();
	block->restartCounter();
	list<StringInputData> listaDatos;
	bool deleteResult = true;
	StringInputData* sid;
	VarRegister varRegister = block->getNextRegister(true); // Salteo el primer registro que tiene datos de control.
//this->print();
	while (!block->isLastRegister()) {
		varRegister = block->getNextRegister(false);
		sid = new StringInputData();
		sid->toData(varRegister.getValue());
		listaDatos.push_back(*sid);
		//cout << "Clave: " << sid->getKey() << " Valor: " << sid->getValue() <<endl;
		delete sid;
		loadResultEnum load = NORMAL_LOAD;
		deleteResult = block->deleteRegister(load);
//		this->print();
		if (deleteResult == false) {
			cout << "No pudo borrarse el registro: " << sid->getKey() << " del bloque: " << bucketDesbordado->getNumber() << endl;
		}
		this->hashFile->saveBlock(block);
	}

	//block->clear();
	this->hashFile->saveBlock(block);
//	this->print();

	//almaceno el td del bloque //creo que no hace falta esto
//	VarRegister* varReg = new VarRegister();
//	varReg->setValue(bucketDesbordado->getDepth());
//	block->addRegister(*varReg);
//	this->hashFile->saveBlock(block);
//	delete varReg;
//	bucketDesbordado->modifyDepth(bucketDesbordado->getDepth());
//	this->hashFile->saveBlock(block);
//	this->print();

	//recorro toda la lista de sids y redisperso el bloque
	while (!listaDatos.empty()) {
		StringInputData sid = listaDatos.front();
		this->add(&sid);
//		this->print();
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
		this->hashFile->saveBlock(bucket->getBlock());
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
			this->hashFile->saveBlock(bucket->getBlock());
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			delete bucket;
			this->add(sid);
//			this->print();
			delete bucketNuevo;

		} else {
			printf("Entro por td!=tamTabla (%i!=%i).\n",td,tamTabla);
			bucket->duplicateDepth();
			this->hashFile->saveBlock(bucket->getBlock());
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
	//sid->setValue(newValue); // no importa el valor que le paso porque busca por key

	int position;
	//TODO esto del existElement se puede mejorar, y en vez de pasar el sid pasarle la key sola
	// Verifico unicidad
	if (!existsElement(key,position)){
		return 1;
	}
//	delete sid;
	if (position==-1)
		return -1;  //esto no podria pasar, porque si se encontro el elemento, tiene que pasar una posicion

	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Block* block = this->hashFile->getBlock(bucketNumber);

	Bucket * bucket = new Bucket(block);
	this->print();
	if (!bucket->deleteRegister(key))
		return -1;

	if (!this->hashFile->saveBlock(bucket->getBlock()))
		return -1;

	//delete bucket;

	this->print();
//
	stringstream ss (stringstream::in | stringstream::out);
		ss.str(newValue);
	//StringInputData* sid = new StringInputData();
	//sid->setKey(key);
	sid->setValue(ss.str());

//	if (!bucket->insertRegister(sid))
//		return -1;

	int insertResult;
	delete bucket;
	Bucket * bucketA = tryToInsertNewSid(sid,insertResult);
	if (insertResult != 0) //si no se pudo agregar en el bucket lo guardo
		return -1;
	delete sid;


	if (!this->hashFile->saveBlock(bucketA->getBlock()))
		return -1;
	delete bucketA;
	//delete bucket;
	this->print();

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
		bucket->setDepth(bucket->getDepthFromHashFile());
		result = bucket->deleteRegister(key);

		if (result == false) {
			cout << "Se produjo un error al intentar eliminar el registro cuya clave es: " << key << endl;
		} else { // Si se pudo borrar exitosamente, reviso cuantos registros le quedan al bloque.

			this->hashFile->saveBlock(bucket->getBlock());
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
