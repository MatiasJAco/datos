/*
 * Hash.h
 *
 *  Created on: Apr 16, 2010
 *      Author: Adrián Bernardi
 */

#ifndef HASH_H_
#define HASH_H_

#include "../input/StringInputData.h"
#include "../../common/hash/Table.h"

class Hash {

private:
	Table* hashTable;

public:

	Hash();

	virtual ~Hash();

	/**
	 * This method adds a value to the hash.
	 */
	void add(StringInputData* sid);
};

#endif /* HASH_H_ */
