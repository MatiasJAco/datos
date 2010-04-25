/**
 * @file NodeFactory.cpp
 *
 *  @date: 25/04/2010
 *  @author: kira
 */

#include "NodeFactory.h"

Node* NodeFactory::newNode(Block* block)
{
	Node* node = NULL;
	VarRegister levelReg = block->getNextRegister();

	unsigned int nodeNumber = block->getBlockNumber();
	unsigned int level = ByteConverter::bytesToUInt(levelReg.getValue());

	if (level == Node::LEAF_LEVEL)
	{
		node = new LeafNode(nodeNumber);
	}
	else
	{
		node = new InnerNode(nodeNumber,level);
	}

	node->setBlock(block);

	return node;
}
