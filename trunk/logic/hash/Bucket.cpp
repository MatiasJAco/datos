/*
 * Bucket.cpp
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#include "Bucket.h"

Bucket::Bucket() {
	// TODO Auto-generated constructor stub

}

Bucket::~Bucket() {
	// TODO Auto-generated destructor stub
}

void Bucket::setBlock(Block* block){
	this->block = block;
}

Block* Bucket::getBlock(){
	return this->block;
}

//TODO revisar que funcionen bien los operadores
bool operator<(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.block < bucket2.block;
}
bool operator>(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.block > bucket2.block;
}
bool operator==(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.block == bucket2.block;
}
bool operator!=(const Bucket &bucket1, const Bucket &bucket2) {
	return bucket1.block != bucket2.block;
}
