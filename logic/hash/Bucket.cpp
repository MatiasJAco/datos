/*
 * Bucket.cpp
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#include "Bucket.h"

//Bucket::Bucket(unsigned int number, unsigned int depth) {
//	this->number = number;
//	this->depth = depth;
//}

unsigned int Bucket::getDepthFromHashFile(){
	this->block->restartCounter();

	//el primer registro tiene el valor del td
	VarRegister varRegister=this->block->getNextRegister(true);
	unsigned int depth = ByteConverter::bytesToInt(varRegister.getValue());
	return depth;
}

Bucket::Bucket(Block* block) {
	this->block=block;
	this->number = block->getBlockNumber()-1;
	this->depth=getDepthFromHashFile();
}

Bucket::~Bucket() {
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

void Bucket::positionateAtEnd(){
	this->block->restartCounter();
	while (this->block->hasNextRegister()) {
		this->block->getNextRegister(true);
	}
}

int Bucket::insert(StringInputData* sid) {
	loadResultEnum loadResult;
	unsigned int dataSize = sid->size();
	int result = 0; // Es el valor de retorno de esta función. Indica si se pudo insertar el registro al bloque, o no.

	char* valueReg = new char[dataSize];
	VarRegister* varRegister = new VarRegister(sid->toStream(valueReg),dataSize);
	//me paro al final del bloque.
	positionateAtEnd();

	/* Intenta insertar el registro en el bloque. */
	bool inserted = this->block->addRegister(*varRegister, loadResult);

	if (loadResult == OVERFLOW_LOAD) {
		result = 1;
	} else if (inserted == false) {
		result = 2;
	}
	delete varRegister;
	return result;
}

bool Bucket::existsRegister(int key) {
	this->getBlock()->restartCounter();
	while (this->block->hasNextRegister()) {
		VarRegister varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		if (sid->getKey() == key) {
			return true;
		}
	}
	return false;
}

VarRegister Bucket::getRegister(int key) {
	VarRegister varRegister;
	this->getBlock()->restartCounter();
	bool found = false;
	while ((!found) && (!this->getBlock()->isLastRegister())) {
		varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		if (sid->getKey() == key) {
			found = true;
		}
	}
	return varRegister;
}


void Bucket::print(){
	VarRegister varReg;
	this->block->restartCounter();
	varReg=this->block->getNextRegister(true);

	//imprimo td del bucket
	StringInputData* sid = new StringInputData();
	sid->toData(varReg.getValue());
	cout << "(" << sid->getKey() << ") ";
	delete sid;

	//imprimo resto del bucket
	while (this->block->hasNextRegister()) {
		varReg=this->block->getNextRegister(true);
		StringInputData* sid = new StringInputData();
		sid->toData(varReg.getValue());
		cout << sid->getKey() << "-" << sid->getValue() << " | ";
		delete sid;
	}
}

void Bucket::duplicateDepth(){
	loadResultEnum result;
	this->block->restartCounter();
	VarRegister varReg = this->block->getNextRegister(true);

	StringInputData* sid = new StringInputData();
	sid->toData(varReg.getValue());
	varReg.setValue(sid->getKey()*2);

	this->block->modifyRegister(varReg,result);

	if (OVERFLOW_LOAD == result) {
		cout << "El cambio en el registro hace que se sobrepase el tamaño del bloque y no puede modificarse." << endl;
	}

	this->depth = this->depth * 2;
	delete sid;
}

void Bucket::divideDepth(){
//	this->depth =this->depth / 2;
	//TODO implementar este metodo copiando el duplicateDepth
}
