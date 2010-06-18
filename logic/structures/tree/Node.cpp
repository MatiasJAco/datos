/**
 * @file Node.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "Node.h"

//Node::Node(unsigned int nodeNumber,unsigned int level,Block* block,BPlusTree* pointerTree)
Node::Node(unsigned int nodeNumber,unsigned int level,Block* block){
	m_nodeNumber = nodeNumber;
	m_block = block;
//	m_tree = pointerTree;

	if (m_block->getRegisterAmount()==0)
	{
		VarRegister regLevel;

		regLevel.setValue(level);

		m_block->restartCounter();
		m_block->addRegister(regLevel);
	}
}

Node::~Node()
{
	if (m_block!=NULL)
		delete m_block;
}


unsigned int Node::getLevel()
{
	unsigned int level = UNDEFINED_NODE_LEVEL;
	char* levelValue = NULL;

	m_block->restartCounter();

	if (!m_block->isLastRegister())
	{
		VarRegister regLevel = m_block->getNextRegister();
		levelValue = regLevel.getValue();
		level = ByteConverter::bytesToUInt(levelValue);
		delete[] levelValue;
	}

	return level;
}

unsigned int Node::readLevel(Block block)
{
	unsigned int level = UNDEFINED_NODE_LEVEL;
	char* levelValue = NULL;

	block.restartCounter();

	if (!block.isLastRegister())
	{
		VarRegister regLevel = block.getNextRegister();
		levelValue = regLevel.getValue();
		level = ByteConverter::bytesToUInt(levelValue);
		delete [] levelValue;
	}

	return level;
}


void Node::setLevel(const unsigned int level)
{
	m_block->restartCounter();

	VarRegister regLevel;

	regLevel.setValue(level);

	m_block->modifyRegister(regLevel);
}

unsigned int Node::getNodeNumber()const
{
	return m_block->getBlockNumber();
}


bool Node::isEmpty()
{
	return true;
}

bool Node::isLeaf()
{
	unsigned int level = getLevel();

	return (level == LEAF_LEVEL);
}


void Node::setBlock(Block* block)
{
	m_block = block;
}

void Node::setNodeNumber(unsigned int number)
{
	this->m_nodeNumber=number;
}

Block* Node::getBlock()
{
	return m_block;
}
