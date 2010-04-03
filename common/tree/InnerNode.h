/*
 * InnerNode.h
 *
 *  Created on: 03/04/2010
 *      Author: kira
 */

#ifndef INNERNODE_H_
#define INNERNODE_H_

#include "Node.h"

class InnerNode: public Node {
public:
	InnerNode();
	InnerNode(unsigned int level,unsigned int size,unsigned int BranchFactor);
	InnerNode(unsigned int NodeNumber,unsigned int level,unsigned int size,unsigned int BranchFactor);
	~InnerNode();

};

#endif /* INNERNODE_H_ */
