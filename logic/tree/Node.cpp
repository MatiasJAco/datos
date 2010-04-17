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

Node::Node(unsigned int level,unsigned int size,double branchFactor)
{
	m_nodeNumber = UNDEFINED_NODE_NUMBER;
	m_level = level;
	m_size = size;
	m_branchFactor = branchFactor;
}

Node::Node(unsigned int nodeNumber,unsigned int level,unsigned int size,double branchFactor)
{
	m_nodeNumber = nodeNumber;
	m_level = level;
	m_size = size;
	m_branchFactor = branchFactor;
}

Node::~Node()
{
}


unsigned int Node::getLevel()const
{
	return m_level;
}

void Node::setLevel(const unsigned int level)
{
	m_level = level;
}

unsigned int Node::getSize() const
{
	return m_size;
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
	return m_branchFactor;
}

void Node::setBranchFactor(double branchFactor)
{
	m_branchFactor = branchFactor;
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
