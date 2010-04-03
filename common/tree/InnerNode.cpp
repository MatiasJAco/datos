/*
 * InnerNode.cpp
 *
 *  Created on: 03/04/2010
 *      Author: kira
 */

#include "InnerNode.h"

InnerNode::InnerNode() {
	// TODO Auto-generated constructor stub

}

InnerNode::InnerNode(unsigned int NodeNumber, unsigned int level, unsigned int size, unsigned int branchFactor):Node(NodeNumber,level, size, branchFactor)
{
}

InnerNode::InnerNode(unsigned int level, unsigned int size, unsigned int branchFactor):Node(level, size, branchFactor)
{
}

InnerNode::~InnerNode() {
	// TODO Auto-generated destructor stub
}
