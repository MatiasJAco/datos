/*
 * Nodo.cpp
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#include "Node.h"

Node::Node() {
	// TODO Auto-generated constructor stub

}

Node::~Node()
{
}


Node::Node(unsigned int level,unsigned int size,unsigned int BranchFactor)
{
	m_level = level;
	m_size = size;
	m_BranchFactor = BranchFactor;
}

Node::Node(unsigned int NodeNumber,unsigned int level,unsigned int size,unsigned int BranchFactor)
{
	m_NodeNumber = NodeNumber;
	m_level = level;
	m_size = size;
	m_BranchFactor = BranchFactor;
}

void Node::setNivel(const unsigned int nivel)
{
	m_level = nivel;
}

unsigned int Node::getLevel()
{
	return m_level;
}

bool Node::isEmpty()
{
	return getUsedSpace() == 0;
}


unsigned int Node::getUsedSpace()
{
	unsigned int totalOcupied = 0;
	if(!isEmpty())
	{
		RegisterMapIterator iter;

		for (iter = m_registers.begin(); iter != m_registers.end(); iter++)
		{
			totalOcupied += (iter->second)->getSize();
		}
	}
	return totalOcupied;
}


bool Node::underflow()
{
	bool retVal = false;
	unsigned int totalOcupied;


	//Obtengo el espacio utilizado en el nodo
	totalOcupied = getUsedSpace();

	if(totalOcupied < m_BranchFactor)
		retVal = true;

	return retVal;
}

bool Node::overflow()
{
	bool retVal = false;
	unsigned int totalOcupied;

	//Obtengo el espacio utilizado en el nodo
	totalOcupied = getUsedSpace();

	if(totalOcupied > m_size)
		retVal = true;

	return retVal;
}

unsigned int Node::getBranchFactor() const
{
    return m_BranchFactor;
}

char *Node::serialize(char *bytes) const
{
	bytes = ByteConverter::uIntToBytes(m_level, bytes);
	bytes += sizeof(m_level);
	bytes = serialize(bytes);
	return bytes;
}

void Node::deserialize(const char *bytes)
{
	m_level = ByteConverter::bytesToUInt(bytes);
	bytes += sizeof(m_level);
	deserialize(bytes);
}

bool Node::isLeaf(const char *bytes)
{
	int level = ByteConverter::bytesToUInt(bytes);

	return (level == LEAF_LEVEL);
}

void Node::setBranchFactor(unsigned int branchFactor)
{
    m_BranchFactor = branchFactor;
}

void Node::setNodeNumber(unsigned int number)
{
	m_NodeNumber = number;
}

unsigned int Node::getNodeNumber()
{
	return m_NodeNumber;
}


