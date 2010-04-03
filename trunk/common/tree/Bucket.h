/*
 * Bucket.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include "Node.h"

class Bucket: public Node {
public:
	Bucket();
	virtual ~Bucket();

	bool insert(const Register& reg);
	bool remove(const Key& key);

};

#endif /* BUCKET_H_ */
