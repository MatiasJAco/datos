/*
 * LeafNode.cpp
 *
 *  Created on: 17/04/2010
 *      Author: matias
 */

#include "LeafNode.h"

LeafNode::LeafNode(){};

LeafNode::LeafNode(unsigned int size,double branch)
:Node(Node::LEAF_LEVEL,size,branch){
};

LeafNode::LeafNode(unsigned int number,unsigned int size,double branch)
:Node(number,Node::LEAF_LEVEL,size,branch){

};

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

void LeafNode::divide(){
	LeafNode* nodoNuevo = new LeafNode();
	while(nodoNuevo->getUsedSpace()<50){
		//TODO Implementar traslado de registros de un bloque a otro.
	}

}



