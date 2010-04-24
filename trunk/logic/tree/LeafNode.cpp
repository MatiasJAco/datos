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

LeafNode::LeafNode(unsigned int size,double branch)
:Node(Node::LEAF_LEVEL,size,branch){
}

LeafNode::LeafNode(unsigned int number,unsigned int size,double branch)
:Node(number,Node::LEAF_LEVEL,size,branch){

}

LeafNode::~LeafNode()
{
}

bool LeafNode::find(const InputData & dato,const InputData & dato2) const
{
	return true;
}

bool LeafNode::insert(const InputData & dato)
{
	return true;
}

bool LeafNode::remove(const InputData & dato)
{
	return true;
}

bool LeafNode::modify(const InputData & dato, const InputData & dato2)
{
	return true;
}

unsigned int LeafNode::getUsedSpace()
{
	return 0;
}

void divide(Node* destNode){
//	LeafNode* nodoNuevo = new LeafNode();
	while(destNode->getUsedSpace()<50){
		//TODO Implementar traslado de registros de un bloque a otro.
	}

}

void LeafNode::join()
{
}

void LeafNode::save()
{

}

bool LeafNode::isLeaf(){
	return true;
};




