/*
 * Bucket.cpp
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#include "Bucket.h"

Bucket::Bucket(unsigned int number) {
	this->number = number;
}

Bucket::~Bucket() {
}

void Bucket::setNumber(unsigned int number){
	this->number = number;
}

unsigned int Bucket::getNumber(){
	return this->number;
}

void Bucket::setDepth(unsigned int depth){
	this->depth = depth;
}

unsigned int Bucket::getDepth(){
	return this->depth;
}

//TODO revisar que funcionen bien los operadores
bool operator<(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.number < bucket2.number;
}
bool operator>(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.number > bucket2.number;
}
bool operator==(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.number == bucket2.number;
}
bool operator!=(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.number != bucket2.number;
}
