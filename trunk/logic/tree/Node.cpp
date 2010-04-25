/**
 * @file Node.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "Node.h"

Node::Node()
{
	m_nodeNumber = UNDEFINED_NODE_NUMBER;
}

Node::Node(unsigned int nodeNumber,unsigned int level)
{
	m_nodeNumber = nodeNumber;
	m_level = level;
}

Node::~Node()
{
}


unsigned int Node::getLevel()const
{
	return m_level;
}

unsigned int Node::readLevel(Block block)
{
	block.restartCounter();

	VarRegister firstReg = block.getNextRegister();

	unsigned int level = ByteConverter::bytesToUInt(firstReg.getValue());

	return level;
}


void Node::setLevel(const unsigned int level)
{
	m_level = level;
}

unsigned int Node::getSize() const
{
	throw "Hay que quitar este constructor! Nodo no va a tener mas el tamaño!";

//	return m_size;
	return 0;
}

unsigned int Node::getNodeNumber()const
{
	return m_nodeNumber;
}

void Node::setNodeNumber(unsigned int number)
{
	m_nodeNumber = number;
}

double Node::getBranchFactor() const
{
	throw "Hay que quitar este constructor! Nodo no va a tener mas el factor de carga!";

//	return m_branchFactor;
	return 0;
}

void Node::setBranchFactor(double branchFactor)
{
	throw "Hay que quitar este constructor! Nodo no va a tener mas el factor de carga!";

//	m_branchFactor = branchFactor;
}


bool Node::isEmpty()
{
	return true;
}

bool Node::overflow()
{
	return true;
}


bool Node::underflow()
{
	return true;
}

bool Node::isLeaf()
{
	return (m_level == LEAF_LEVEL);
}


void Node::setBlock(Block* block)
{
	m_block = block;
}

Block* Node::getBlock()
{
	return m_block;
}

void Node::save()
{

}
