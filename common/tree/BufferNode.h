/*
 * BufferTree.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef BUFFERNODE_H_
#define BUFFERNODE_H_

#include "Node.h"
#include "LeafNode.h"
#include "InnerNode.h"
#include "../utils/ByteConverter.h"

#include <fstream>
#include <iostream>
#include <list>
#include <queue>

class BufferNode {

private:
	/// Cantidad de numeros de nodos libres maximo que voy a leer
	static const unsigned int MAXSIZEBUFF = 128*sizeof(unsigned int);
	static const unsigned int MAX_FREENODES_BUFF = MAXSIZEBUFF/sizeof(unsigned int);

	typedef std::priority_queue< int, std::queue<int>,std::less<int> > PriorityQueue;


private:
	unsigned int m_nodeSize;
	int m_branchFactor;

	std::fstream m_nodesFile;

	std::fstream m_freeNodesfile;
//	PriorityQueue m_freeNodes;

	/// TODO tener lista de nodos libres ordenados por numero de nodo

public:
	BufferNode();

	BufferNode(std::string nodesFileName,unsigned int nodeSize,int branchFactor);

	virtual ~BufferNode();

	void writeNode(Node& node);
	Node* readNode(unsigned int nodeNumber);

	void removeNode(Node& node);

	///TODO agregar el manejo de nodos libres

private:
	unsigned int getFreeNodeNumber();
	void writeFreeNodes();
	void readFreeNodes();

	void deserializeFreeNodes(const char* bytes);

};

#endif /* BUFFERNODE_H_ */
