/*
 * Bucket.h
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include "../../physical/file/Block.h"

class Bucket {

private:
	Block* block;

public:
	Bucket();
	virtual ~Bucket();

	void setBlock(Block* block);
	Block* getBlock();

	friend bool operator<(const Bucket &object1, const Bucket &object2);
	friend bool operator>(const Bucket &object1, const Bucket &object2);
	friend bool operator==(const Bucket &object1, const Bucket &object2);
	friend bool operator!=(const Bucket &object1, const Bucket &object2);
};

#endif /* BUCKET_H_ */
