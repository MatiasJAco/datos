/*
 * Bucket.cpp
 *
 *  Created on: Apr 24, 2010
 *      Author: Pablo Lisio / Adrián Bernardi
 */

#include "Bucket.h"

unsigned int Bucket::getDepthFromHashFile(){
	this->block->restartCounter();

	//el primer registro tiene el valor del td
	VarRegister varRegister=this->block->getNextRegister(true);
	char * value = varRegister.getValue();
	unsigned int depth;
	std::string stringDepth = ByteConverter::bytesToString(value);
	depth = atoi(stringDepth.c_str());
	if (value!=NULL)
		delete [] value;
	return depth;
}

Bucket::Bucket(Block* block) {
	this->block=block;
	this->number = block->getBlockNumber()-1;
	this->depth=getDepthFromHashFile();
}

Bucket::~Bucket() {
	if (this->block!= NULL)
		delete this->block;
}

void Bucket::setNumber(unsigned int number) {
	this->number = number;
}

unsigned int Bucket::getNumber() {
	return this->number;
}

void Bucket::setDepth(unsigned int depth) {
	this->depth = depth;
}

unsigned int Bucket::getDepth() {
	return this->depth;
}

void Bucket::setBlock(Block* block) {
	this->block = block;
}

Block* Bucket::getBlock() {
	return this->block;
}

void Bucket::positionateAt(int position){
	this->block->restartCounter();
	while (this->block->hasNextRegister()&& position!=0) {
		this->block->getNextRegister(true);
		position--;
	}
}

int Bucket::insertRegister(StringInputData* sid) {
	loadResultEnum loadResult;
	unsigned int dataSize = sid->size();
	int result = 0; // Es el valor de retorno de esta función. Indica si se pudo insertar el registro al bloque, o no.

	char* valueReg = new char[dataSize];
	VarRegister* varRegister = new VarRegister(sid->toStream(valueReg),dataSize);

	/* Intenta insertar el registro en el bloque. */
	bool inserted = this->block->addRegister(*varRegister, loadResult);

	if (loadResult == OVERFLOW_LOAD) {
		result = 1;
	} else if (inserted == false) {
		result = 2;
	}
	delete [] valueReg;
	delete varRegister;
	return result;
}

bool Bucket::existsRegister(std::string key) {
	int aux = -1;
	return this->existsRegister(key,aux);
}
bool Bucket::existsRegister(std::string key,int & position) {
	position = 0;
	positionateAt(1);//para salvar el primer reg (que es el td) - contra ese no se tiene que comparar

	while (this->block->hasNextRegister()) {
		VarRegister varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		position++;
		//if (sid->getKey() == key) {
		if (strcmp(sid->getKey().c_str(),key.c_str())==0) {
			delete [] registerValue;
			delete sid;
			return true;
		}
		if (registerValue!=NULL)
			delete [] registerValue;
		delete sid;
	}
	return false;
}


VarRegister Bucket::getRegister(std::string key) {
	VarRegister varRegister;
	this->getBlock()->restartCounter();
	bool found = false;
	while ((!found) && (this->getBlock()->hasNextRegister())) {
		varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		//if (sid->getKey() == key) {
		if (strcmp(sid->getKey().c_str() , key.c_str())==0) {
			found = true;
		}
		if (registerValue!=NULL)
			delete [] registerValue;
		delete sid;
	}
	return varRegister;
}

bool Bucket::deleteRegister(std::string key) {
	this->getBlock()->restartCounter();
	VarRegister varRegister = this->getBlock()->getNextRegister(true); // Salteo el primer registro que es de control.
	bool result = false;

	while (this->getBlock()->hasNextRegister()) {
		varRegister = this->getBlock()->getNextRegister(false);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		//if (sid->getKey() == key) {
		if (strcmp(sid->getKey().c_str(), key.c_str())==0) {
			result = this->getBlock()->deleteRegister();
			delete [] registerValue;
			delete sid;
			return result;
		}
		varRegister = this->getBlock()->getNextRegister(true);
		if (registerValue!=NULL)
			delete [] registerValue;
		delete sid;
	}
	return result;
}

void Bucket::print(){
	VarRegister varReg;
	bool primeraVez = true;

	this->block->restartCounter();

	while (this->block->hasNextRegister()) {
		varReg=this->block->getNextRegister(true);
		StringInputData* sid = new StringInputData();
		char * value = varReg.getValue();
		sid->toData(value);
		if (primeraVez){
			cout << "(" << sid->getKey() << ") ";
			primeraVez=false;
		}
		else
			cout << sid->getKey() << "-" << sid->getValue() << " | ";
		if (value !=NULL)
			delete [] value;

		delete sid;
	}
}

bool Bucket::modifyDepth(int depth){
	loadResultEnum result;
	this->block->restartCounter();
	VarRegister varReg = this->block->getNextRegister(false);

	StringInputData* sid = new StringInputData();
	sid->toData(varReg.getValue());
	unsigned int dataSize = sizeof(int);
	char* valueReg = new char[dataSize];

	char stringDepth[10];
	sprintf(stringDepth,"%i",depth);
	sid->setKey(stringDepth);

	varReg.setValue(sid->toStream(valueReg),dataSize);

	bool result2 = this->block->modifyRegister(varReg,result);

	delete sid;
	return result2;
}

bool Bucket::duplicateDepth(){
	bool result = modifyDepth(this->depth*2);
		if (result) this->depth = this->depth*2;
	return result;
}

bool Bucket::divideDepth(){
	if (this->depth > 1){
		bool result = modifyDepth(this->depth/2);
			if (result) this->depth = this->depth/2;
		return result;
	}
	else return false;
}


void Bucket::getListOfSids(list<StringInputData> &listaDatos){
	block->restartCounter();
	StringInputData* sid;
	VarRegister varRegister = block->getNextRegister(true); // Salteo el primer registro que tiene datos de control.
	while (!block->isLastRegister()) {
		varRegister = block->getNextRegister(false);
		sid = new StringInputData();
		char * value = varRegister.getValue();
		sid->toData(value);
		listaDatos.push_back(*sid);
		if (value!= NULL)
			delete [] value;
		delete sid;
		block->getNextRegister(true);
	}
}

bool Bucket::empty(){
	block->restartCounter();
	bool deleteResult = true;
	bool result = true;
	VarRegister varRegister = block->getNextRegister(true); // Salteo el primer registro que tiene datos de control.
	while (!block->isLastRegister()) {
		varRegister = block->getNextRegister(false);
		loadResultEnum load = NORMAL_LOAD;
		deleteResult = block->deleteRegister(load);
		if (deleteResult == false) {
			result = false;
		}
	}
	return result;
}
