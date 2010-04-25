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
Bucket::Bucket(Block* block) {
	this->block=block;
	this->number = block->getBlockNumber();
	//this->depth = ( (VarRegister) block->getNextRegister(false) ).getValue();
	//TODO: hacer un metodo que devuelva el td sacado desde el bloque
	this->depth=1;
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

loadResultEnum Bucket::insert(StringInputData* sid) {
	VarRegister* varRegister = new VarRegister();

	char* stream;
	unsigned int size = sizeof(*sid);
	varRegister->setValue(sid->toStream(stream),size);


	/* Si el bloque posee suficiente espacio para guardar un registro más, lo guarda: */

	this->block->addRegister(*varRegister);

	delete varRegister;
	return NORMAL_LOAD;


//	//TODO: cambiar este metodo por el nuevo q esta haciendo alex (mail que envio el 24/04/10)
//	if (this->block->getRemainingSpace() >= varRegister->getDiskSize()) {
//		this->block->addRegister(*varRegister);
//		//this->hashFile->saveBlock(this->block);
//	} else { /* En caso contrario, se duplica la tabla y se guarda el registro en un bloque nuevo. */
//
//
//		//TODO completar qué hacer al dar de alta cuando se duplica la tabla.
//	}

//	return true;
}

bool Bucket::existsRegister(int key) {
	this->getBlock()->restartCounter();
	while (!this->getBlock()->isLastRegister()) {
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
	//this->block->printRegisters();
	VarRegister varRegister;
	this->getBlock()->restartCounter();
	//while (!this->block->isLastRegister()) {
		varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		cout << "Key: " << sid->getKey() << endl;
		cout << "Value: " << sid->getValue() << endl;
	//}
}