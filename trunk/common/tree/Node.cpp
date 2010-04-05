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
	RegisterMapIterator it;

	for (it = m_registers.begin();it != m_registers.end();it++)
	{
		delete (it->first);
		delete (it->second);
	}
}


Node::Node(unsigned int level,unsigned int size,unsigned int branchFactor)
{
	m_level = level;
	m_size = size;
	m_branchFactor = branchFactor;
}

Node::Node(unsigned int nodeNumber,unsigned int level,unsigned int size,unsigned int branchFactor)
{
	m_nodeNumber = nodeNumber;
	m_level = level;
	m_size = size;
	m_branchFactor = branchFactor;
}

void Node::setNivel(const unsigned int nivel)
{
	m_level = nivel;
}

unsigned int Node::getLevel()
{
	return m_level;
}


unsigned int Node::getSize() const
{
	// Solo es posible devolver el tamaño del nodo, una vez creado no se puede modificar
	return m_size;
}

bool Node::isEmpty()
{
	return getUsedSpace() == 0;
}


unsigned int Node::getUsedSpace()
{
	// TODO CAMBIAR PARA QUE INCLUYA EL TAMAÑO DE LOS DATOS DE CONTROL
	// Tener en cuenta que los datos de control pueden cambiar en las clases herederas de Node
	// por eso este metodo se define virtual.
	unsigned int totalOcupied = sizeof(m_level);

	RegisterMapIterator iter;

	for (iter = m_registers.begin(); iter != m_registers.end(); iter++)
	{
		totalOcupied += (iter->second)->getSize();
	}

	return totalOcupied;
}


bool Node::underflow()
{
	bool retVal = false;
	unsigned int totalOcupied;

	//Obtengo el espacio utilizado en el nodo
	totalOcupied = getUsedSpace();

	if(totalOcupied < m_branchFactor*m_size)
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
    return m_branchFactor;
}

char *Node::serialize(char *bytes) const
{
	bytes = ByteConverter::uIntToBytes(m_level, bytes);
	bytes += sizeof(m_level);
	serializeChilds(bytes);
	return bytes;
}

void Node::deserialize(const char *bytes)
{
	m_level = ByteConverter::bytesToUInt(bytes);
	bytes += sizeof(m_level);
	deserializeChilds(bytes);
}

void Node::setFields(const Register& registro)
{
	const Node& node = dynamic_cast<const Node&>(registro);

	m_nodeNumber = node.m_nodeNumber;
	m_level = node.m_level;
	m_size = node.m_size;
	m_branchFactor = node.m_branchFactor;

	// TODO falta hacer la copia del map.
//	RegisterMapIterator iter;
//
//	for (iter = (node.m_registers).begin();iter != (node.m_registers).end();iter++)
//	{
//		Register* key = (iter->first)->newInstance();
//		Register* reg = (iter->second)->newInstance();
//
//
//	}
}

bool Node::isLeaf(const char *bytes)
{
	unsigned int level = ByteConverter::bytesToUInt(bytes);

	return (level == LEAF_LEVEL);
}

void Node::setBranchFactor(unsigned int branchFactor)
{
    m_branchFactor = branchFactor;
}

void Node::setNodeNumber(unsigned int number)
{
	m_nodeNumber = number;
}

unsigned int Node::getNodeNumber()const
{
	return m_nodeNumber;
}


