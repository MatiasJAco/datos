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

class Bucket {

private:
	unsigned int number; // Numero de cubo.
	unsigned int depth; // Dispersion del cubo.

public:
	Bucket(unsigned int number, unsigned int depth);
	virtual ~Bucket();

	void setNumber(unsigned int number);
	unsigned int getNumber();
	void setDepth(unsigned int depth);
	unsigned int getDepth();

	friend bool operator<(const Bucket &object1, const Bucket &object2);
	friend bool operator>(const Bucket &object1, const Bucket &object2);
	friend bool operator==(const Bucket &object1, const Bucket &object2);
	friend bool operator!=(const Bucket &object1, const Bucket &object2);
};

#endif /* BUCKET_H_ */
