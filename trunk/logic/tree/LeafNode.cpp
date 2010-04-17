/*
 * LeafNode.cpp
 *
 *  Created on: 17/04/2010
 *      Author: matias
 */

#include "LeafNode.h"

LeafNode::LeafNode(){};

LeafNode::LeafNode(unsigned int size,unsigned int branch){
	this->m_size=size;
	this->m_branchFactor=branch;
	this->m_bloque=NULL;
};

LeafNode::LeafNode(unsigned int number,unsigned int size,unsigned int branch){
	this->m_nodeNumber=number;
	this->m_size=size;
	this->m_branchFactor=branch;
	this->m_bloque=NULL;
};

void LeafNode::dividir(){
	LeafNode nodoNuevo=new LeafNode();
	while(nodoNuevo.getUsedSpace()<50){
		//TODO Implementar traslado de registros de un bloque a otro.
	}

};



