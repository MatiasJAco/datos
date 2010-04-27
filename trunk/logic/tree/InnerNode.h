/**
 * @file InnerNode.h
 * @author MCM
 *
 */

#ifndef INNERNODE_H_
#define INNERNODE_H_

#include <iostream>
#include <sstream>

#include "Node.h"
#include "LeafNode.h"

//#include "../logic/tree/dataNode/INodeData.h"
#include "../../physical/utils/ByteConverter.h"

#include "BPlusTree.h"

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos internos.
 */

class BPlusTree;

class InnerNode: public Node {

	friend class BPlusTree;

private:

	BPlusTree* m_tree;

	unsigned int buscarPosicionInner(InnerNode *& nodoAPartir,INodeData & newData);
	unsigned int buscarPosicionLeaf(LeafNode *& nodoAPartir,const InputData & newData);


private:
    InnerNode(unsigned int nodeNumber, unsigned int level, Block *block, BPlusTree *pointerTree);
public:
    InnerNode();
    InnerNode(unsigned int nodeNumber);
    ~InnerNode();
    INodeData *insert(const InputData & dato, loadResultEnum & result);
    loadResultEnum remove(const InputData & key);
    bool find(const InputData & key, InputData & data) const;
    loadResultEnum modify(const InputData & key, const InputData & dato);
    loadResultEnum modify(const InputData & data);
    void insertINodeData(INodeData *contBuscado);
    void join(Node *toDivide, Node *destNode, const InputData & newData);
    void save(Node* node);
private:

	INodeData* divideLeaf (Node* toDivide,Node* destNode,const InputData& newData);

	INodeData* divideInner(Node* aPartir,Node* destNode,INodeData& newData);

	bool balanceLeaf(Node* underNode,Node* toDonate,const InputData& newData);

	bool balanceInner(Node* underNode,Node* toDonate, INodeData& newData);
};

#endif /* INNERNODE_H_ */
