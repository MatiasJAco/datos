/*
 * Bucket.cpp
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#include "Bucket.h"

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

//void Bucket::positionateAtEnd(){
//	this->block->restartCounter();
//	while (this->block->hasNextRegister()) {
//		this->block->getNextRegister(true);
//	}
//}
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
	//me paro al final del bloque.
	//TODO es necesario pararse al final? para mi no ,soy pablo
	//positionateAtEnd();

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
	int aux = -1;
	return this->existsRegister(key,aux);
}
bool Bucket::existsRegister(int key,int & position) {
	//position = -1;
	position = 0;
	//this->getBlock()->restartCounter();

	//para salvar el primer reg (que es el td) - contra ese no se tiene que comparar
//	if (this->block->hasNextRegister()) {
//			this->getBlock()->getNextRegister(true);
//			position++; //queda en cero
//	}
	positionateAt(1);
	while (this->block->hasNextRegister()) {
		VarRegister varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		position++;
		if (sid->getKey() == key) {
			delete sid;
			return true;
		}
		delete sid;
	}
	return false;
}


VarRegister Bucket::getRegister(int key) {
	VarRegister varRegister;
	this->getBlock()->restartCounter();
	bool found = false;
	while ((!found) && (this->getBlock()->hasNextRegister())) {
		varRegister = this->getBlock()->getNextRegister(true);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		if (sid->getKey() == key) {
			found = true;
			delete sid;
		}
		delete sid;
	}
	return varRegister;
}

bool Bucket::deleteRegister(int key) {
	this->getBlock()->restartCounter();
	VarRegister varRegister = this->getBlock()->getNextRegister(true); // Salteo el primer registro que es de control.
	bool result = false;

	while (this->getBlock()->hasNextRegister()) {
		varRegister = this->getBlock()->getNextRegister(false);
		char* registerValue = varRegister.getValue();
		StringInputData* sid = new StringInputData();
		sid->toData(registerValue);
		if (sid->getKey() == key) {
			result = this->getBlock()->deleteRegister();
			delete sid;
			return result;
		}
		varRegister = this->getBlock()->getNextRegister(true);
		delete sid;
	}
	return result;
}

//bool Bucket::deleteRegisterAtPosition(int position){
//	positionateAt(position);
//	loadResultEnum load = NORMAL_LOAD;
//	bool deleteResult = block->deleteRegister(load);
//	if (deleteResult == false) {
//		cout << "No pudo borrarse el registro: ";
//		return false;
//	}
//	return true;
//}



//bool Bucket::modifyRegister(int key, int position,char* newValue){
//	//borro el elemento
//
//
//	/*
//	loadResultEnum loadResult;
//	unsigned int dataSize = sid->size();
//	int result = 0; // Es el valor de retorno de esta función. Indica si se pudo insertar el registro al bloque, o no.
//	char* valueReg = new char[dataSize];
//	VarRegister* varRegister = new VarRegister(sid->toStream(valueReg),dataSize);
//	//me paro al final del bloque.
//	positionateAtEnd();
//	bool inserted = this->block->addRegister(*varRegister, loadResult);
//
//	if (loadResult == OVERFLOW_LOAD) {
//		result = 1;
//	} else if (inserted == false) {
//		result = 2;
//	}
//	delete varRegister;
//	return result;
//	*/
//
//	stringstream ss (stringstream::in | stringstream::out);
//		ss.str(newValue);
//	StringInputData* sid = new StringInputData();
//	sid->setKey(key);
//	sid->setValue(ss.str());
//
//	unsigned int dataSize = sid->size();
//	cout <<sid->getKey()<<"--"<< sid->getValue()<<"----"<<dataSize<<"------------------------------------------";
//	char* valueReg = new char[dataSize];
//	//varReg.setValue(sid->toStream(valueReg),dataSize);
//	VarRegister* varRegister = new VarRegister(sid->toStream(valueReg),dataSize);
//	delete sid;
//	loadResultEnum loadResult;
//	bool inserted = this->block->addRegister(*varRegister, loadResult);
//
//	if (loadResult == OVERFLOW_LOAD) {
//		//result = 1;
//		return false;
//	} else if (inserted == false) {
//		//result = 2;
//		return false;
//	}
//
////	if (OVERFLOW_LOAD == result) {
////		cout << "Error al intentar modificar el tamaño de dispersion de un bloque. Este no puede modificarse. Causado por Overflow" << endl;
////		return -1;
////	}
////	else if (UNDERFLOW_LOAD == result) {
////		cout << "Error al intentar modificar el tamaño de dispersion de un bloque. Este no puede modificarse. Causado por Underflow" << endl;
////		return -1;
////	}
////
////	delete sid;
//
//	return inserted;
//}

void Bucket::print(){
	VarRegister varReg;
	bool primeraVez = true;

	this->block->restartCounter();

	while (this->block->hasNextRegister()) {
		varReg=this->block->getNextRegister(true);
		StringInputData* sid = new StringInputData();
		sid->toData(varReg.getValue());
		if (primeraVez){
			cout << "(" << sid->getKey() << ") ";
			primeraVez=false;
		}
		else
			cout << sid->getKey() << "-" << sid->getValue() << " | ";

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
	sid->setKey(depth);
	varReg.setValue(sid->toStream(valueReg),dataSize);

	bool result2 = this->block->modifyRegister(varReg,result);

	if (OVERFLOW_LOAD == result) {
		cout << "Error al intentar modificar el tamaño de dispersion de un bloque. Este no puede modificarse. Causado por Overflow" << endl;
	}
	else if (UNDERFLOW_LOAD == result) {
		cout << "Error al intentar modificar el tamaño de dispersion de un bloque. Este no puede modificarse. Causado por Underflow" << endl;
	}

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
