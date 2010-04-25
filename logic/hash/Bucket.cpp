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

bool Bucket::add(StringInputData* sid) {
	VarRegister* varRegister = new VarRegister();


	//hay que ver como hacemos para pasarle (clave+valor) en el primer parametro. ¿Como lo "desparseamos" desp?
	//algo asi:
	// char* valor = sid->getKey().c_str() + sid->getValue().c_str();
	//varRegister->setValue(valor, sizeof(valor));      //usar el sizeof()
	//TODO: este renglon de aca abajo esta mal, ver explicacion de arriba
	varRegister->setValue((char*)sid->getValue().c_str(), sid->getValue().size()+1);


	/* Si el bloque posee suficiente espacio para guardar un registro más, lo guarda: */
	//TODO: cambiar este metodo por el nuevo q esta haciendo alex (mail que envio el 24/04/10)
	if (this->block->getRemainingSpace() >= varRegister->getDiskSize()) {
		this->block->addRegister(*varRegister);
		//this->hashFile->saveBlock(this->block);
	} else { /* En caso contrario, se duplica la tabla y se guarda el registro en un bloque nuevo. */


		//TODO completar qué hacer al dar de alta cuando se duplica la tabla.
	}

	return true;
}

bool Bucket::existsRegister(int key) {
	Block* block = this->getBlock();
	block->restartCounter();
	while (!block->isLastRegister()) {
		VarRegister varRegister = block->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		if (sid->getKey() == key) {
			return true;
		}
	}
	return false;
}
