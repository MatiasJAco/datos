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
	this->number = block->getBlockNumber();
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

bool Bucket::insert(StringInputData* sid) {
	char* valueReg = new char[sid->size()];
	VarRegister* varRegister = new VarRegister(sid->toStream(valueReg), sid->size());
	//me paro al final del bucket
	positionateAtEnd();

	/* Si el bloque posee suficiente espacio para guardar un registro más, lo guarda: */
	bool inserted = this->block->addRegister(*varRegister);

	delete varRegister;
	return inserted;


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
	//TODO: arreglar este metodo
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
	this->depth =this->depth * 2;
}

void Bucket::divideDepth(){
	this->depth =this->depth / 2;
}
