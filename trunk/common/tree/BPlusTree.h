/*
 * BPlusTree.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_

#include "Node.h"
#include "LeafNode.h"
#include "BufferNode.h"
#include "../register/Register.h"

class BPlusTree {

private:

	unsigned int m_sizeNodo;

	Node* m_raiz;

	LeafNode* m_firstBucket;
	LeafNode* m_lastBucket;

	BufferNode m_buffer;

public:
	BPlusTree();

	BPlusTree(unsigned int sizeNodo);

	virtual ~BPlusTree();

	void insertar(Register& registro);
};

#endif /* BPLUSTREE_H_ */
