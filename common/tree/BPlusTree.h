/*
 * BPlusTree.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include "Nodo.h"
#include "Bucket.h"
#include "BufferTree.h"
#include "../register/Register.h"

class BPlusTree {

public:
	static const unsigned int TAMANIO_NODO;

private:

	Nodo* raiz;

	Bucket* first_bucket;
	Bucket* last_bucket;

	BufferTree buffer;


public:
	BPlusTree();
	virtual ~BPlusTree();

	void insertar(Register& registro);
};

#endif /* BPLUSTREE_H_ */
