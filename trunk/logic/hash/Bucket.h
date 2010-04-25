/*
 * Bucket.h
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include "../../physical/file/Block.h"
#include "../../physical/file/BlockFile.h"
#include "../input/StringInputData.h"

class Bucket {

private:
	unsigned int number; // Numero de cubo.
	unsigned int depth; // Dispersion del cubo.
	Block* block;

public:
	//Bucket(unsigned int number, unsigned int depth);
	Bucket(Block* block);
	virtual ~Bucket();

	void setNumber(unsigned int number);
	unsigned int getNumber();
	void setDepth(unsigned int depth);
	unsigned int getDepth();

	friend bool operator<(const Bucket &object1, const Bucket &object2);
	friend bool operator>(const Bucket &object1, const Bucket &object2);
	friend bool operator==(const Bucket &object1, const Bucket &object2);
	friend bool operator!=(const Bucket &object1, const Bucket &object2);

	void setBlock(Block* block);
	Block* getBlock();


	/**
	 * Agrega un elemento nuevo al bucket.
	 * Si el StringInputData fue guardado exitosamente retorna true;
	 * Si hubo desborde en el bucket este metodo retorna false;
	 */
	bool add(StringInputData* sid);
};

#endif /* BUCKET_H_ */
