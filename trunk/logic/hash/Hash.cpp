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
#include "../logic/bigint/BigIntegerLibrary.hh"
#include "../logic/md5/MD5.h"

Hash::Hash() {
	this->hashTable->createFile();
	this->hashFile = new BlockFile();
	this->hashFile->open("./hash.bin", 512);
	this->inicializeHashFile();
}

Hash::~Hash() {
	this->hashFile->close();
	delete hashFile;
}

StringInputData* Hash::get(std::string key) {
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

	std::string depthString;
	std::stringstream aux;
	aux << depth;
	depthString = aux.str();

	varRegister->setValue(depthString);
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
	if (block!=NULL)
		delete block;
}

int Hash::calculateHashFunction(std::string key) {
	int numero = 0;
	try {
	MD5 md5(key);
	std::string md5KeyString(md5.hexdigest());
	int i = 0;
	std::string nueva = "";
	while(i < 32) {
		if (md5KeyString.substr(i,1).compare("0") == 0) {
			nueva.append("00");
		} else if (md5KeyString.substr(i,1).compare("1") == 0) {
			nueva.append("01");
		} else if (md5KeyString.substr(i,1).compare("2") == 0) {
			nueva.append("02");
		} else if (md5KeyString.substr(i,1).compare("3") == 0) {
			nueva.append("03");
		} else if (md5KeyString.substr(i,1).compare("4") == 0) {
			nueva.append("04");
		} else if (md5KeyString.substr(i,1).compare("5") == 0) {
			nueva.append("05");
		} else if (md5KeyString.substr(i,1).compare("6") == 0) {
			nueva.append("06");
		} else if (md5KeyString.substr(i,1).compare("7") == 0) {
			nueva.append("07");
		} else if (md5KeyString.substr(i,1).compare("8") == 0) {
			nueva.append("08");
		} else if (md5KeyString.substr(i,1).compare("9") == 0) {
			nueva.append("09");
		} else if (md5KeyString.substr(i,1).compare("a") == 0) {
			nueva.append("10");
		} else if (md5KeyString.substr(i,1).compare("b") == 0) {
			nueva.append("11");
		} else if (md5KeyString.substr(i,1).compare("c") == 0) {
			nueva.append("12");
		} else if (md5KeyString.substr(i,1).compare("d") == 0) {
			nueva.append("13");
		} else if (md5KeyString.substr(i,1).compare("e") == 0) {
			nueva.append("14");
		} else if (md5KeyString.substr(i,1).compare("f") == 0) {
			nueva.append("15");
		} else {
			nueva.append(md5KeyString.substr(i,1));
		}
		i++;
	}
	BigInteger f = stringToBigInteger(nueva);
	BigInteger g = BigInteger(this->hashTable->getSize());
	numero = (f % g).toInt();
	} catch(...) {
		std::cout << "error desconocido. " << std::endl;
	}
	return numero;
	//return atoi (key.c_str()) % this->hashTable->getSize();
}

void Hash::saveBucket(Bucket * bucket){
	this->hashFile->saveBlock(bucket->getBlock());
}

int Hash::getNumberOfBucket(std::string key) {
	//incremento en uno el valor porque el metodo getBlock() no acepta ceros (0)
	int result = 1;
	result += this->hashTable->getNumberOfBucketInHash(calculateHashFunction(key));
	return result;
}

bool Hash::existsElement(std::string key) {
	int aux = -1;
	return (this->existsElement(key,aux));
}
bool Hash::existsElement(std::string key, int & position) {
	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Block * block = this->hashFile->getBlock(bucketNumber);
	Bucket* bucket = new Bucket(block);
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
	delete bucketDesbordado;
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

int Hash::add(std::string clave, string valor) {
	StringInputData* sid = new StringInputData();
	sid->setKey(clave);
	sid->setValue(valor);
	int result = this->add(sid);
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
			delete bucketNuevo;
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->add(sid);
		} else {
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());
			this->hashTable->jumpAndReplace(this->calculateHashFunction(sid->getKey()),bucketNuevo->getDepth(),bucketNuevo->getNumber());
			delete bucketNuevo;
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->add(sid);
		}
	} else {
		delete bucket;
		return insertResult;
	}
	return 0;
}
int Hash::modify(std::string key, string newValue) {
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

int Hash::erase(std::string key) {
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
			delete bucket;
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
				this->hashTable->jumpAndReplace(this->calculateHashFunction(key),tdElement,element);

				if (!bucketAux->divideDepth()){
					delete bucketAux;
					return -1;  //esto no deberia de pasar nunca, pero se lanza el error de todos modos
				}
				else
					this->saveBucket(bucketAux);

				delete bucketAux;
				this->hashTable->verifyAndDivide();
			}
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
		i++;
		delete bucket;
		actualBlock = this->hashFile->getBlock(i);
		cout << endl;
	}
	cout << endl;
}
