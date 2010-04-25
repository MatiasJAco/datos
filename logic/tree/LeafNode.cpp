/*
 * LeafNode.cpp
 *
 *  Created on: 17/04/2010
 *      Author: matias
 */

#include "LeafNode.h"

LeafNode::LeafNode()
{
}

LeafNode::LeafNode(unsigned int nodeNumber)
:Node(nodeNumber,Node::LEAF_LEVEL)
{
}

LeafNode::~LeafNode()
{
}

bool LeafNode::find(const InputData & dato,const InputData & dato2) const
{
	return true;
}

loadResultEnum LeafNode::insert(const InputData & dato)
{
	return NORMAL_LOAD;
}

loadResultEnum LeafNode::remove(const InputData & dato)
{
	return NORMAL_LOAD;
}

loadResultEnum LeafNode::modify(const InputData & dato, const InputData & dato2)
{
	return NORMAL_LOAD;
}


unsigned int LeafNode::getUsedSpace()
{
	throw "Hay que quitar este metodo! se hace control desde el Block";
	return 0;
}


void LeafNode::divide(Node* destNode){
//	LeafNode* nodoNuevo = new LeafNode();
	while(destNode->getUsedSpace()<50){
		//TODO Implementar traslado de registros de un bloque a otro.
	}
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";

}

void LeafNode::join(Node* fusionNode){
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}

void LeafNode::donate(Node* destNode,unsigned int toDonate)
{
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}

bool LeafNode::falseRemove(unsigned int toRemove)
{
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}


