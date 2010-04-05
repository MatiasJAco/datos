/*
 * BufferTree.cpp
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#include "BufferNode.h"

using namespace std;


BufferNode::BufferNode() {
	// TODO Auto-generated constructor stub

}

BufferNode::BufferNode(std::string nodesFileName, unsigned int nodeSize,int branchFactor)
:m_nodesFile(nodesFileName.c_str(),std::ios::binary |	std::ios::in | std::ios::out ),
m_freeNodesfile((nodesFileName+string(".free")).c_str(),std::ios::binary |	std::ios::in | std::ios::out )
{
	m_nodeSize = nodeSize;

	if (!m_nodesFile)
	{
		/* El archivo se crea por primera vez */
		m_nodesFile.open(nodesFileName.c_str(),fstream::binary|fstream::in |fstream::out |fstream::trunc );
	}

	m_branchFactor = branchFactor;
}

BufferNode::~BufferNode() {
	// TODO Auto-generated destructor stub
}

void BufferNode::writeNode(Node& node)
{
	char* bytes = new char[m_nodeSize];
	unsigned int offset;

	/// Si en el nodo no tiene indicado el numero de nodo busco un nodo libre
	if (node.getNodeNumber() == Node::UNDEFINED_NODE_NUMBER)
		node.setNodeNumber(getFreeNodeNumber());

	offset = node.getNodeNumber()*m_nodeSize;
	m_nodesFile.clear();
	m_nodesFile.seekp(offset,fstream::beg);
	node.serialize(bytes);
	m_nodesFile.write(bytes,m_nodeSize);

}

Node* BufferNode::readNode(unsigned int nodeNumber)
{
	char* bytes = new char[m_nodeSize];
	unsigned int offset = nodeNumber*m_nodeSize;
	Node* node;

	m_nodesFile.clear();
	m_nodesFile.seekg(offset,fstream::beg);
	m_nodesFile.read(bytes,m_nodeSize);

	// Necesito de bucket: Numero de nodo (opcional), nivel, tamaño
	if (Node::isLeaf(bytes))
	{
		node = new LeafNode(nodeNumber,m_nodeSize,m_branchFactor);
	}
//	else
//		// TODO llamar a new InnerNode, me falta el nivel
//		node = new InnerNode(nodeNumber,m_nodeSize,m_branchFactor);

	node->deserialize(bytes);

	delete[] bytes;
	return node;
}

void BufferNode::removeNode(Node& node)
{
	// Al dar de baja un nodo, deberia crear el archivo de nodos libres
	// en el caso en que no se haya creado

//	unsigned int numberNode = node.getNodeNumber();

	// Si supera mi tamaño de buffer de nodos libres que puedo tener en memoria,
	// deberia escribir a disco y obtener de nuevo el primer buffer.

//	if (m_freeNodes.size()>MAX_FREENODES_BUFF)
//	{
//
//	}

//	m_freeNodes.push(numberNode);
	node.setNodeNumber(Node::UNDEFINED_NODE_NUMBER);
}

unsigned int BufferNode::getFreeNodeNumber()
{
	// TODO leer de la lista de libres, ahora solo esta devolviendo el ultimo disponible
	unsigned int offset;

	m_nodesFile.clear();
	m_nodesFile.seekg(0,fstream::beg);
	offset = m_nodesFile.tellg();

	return (offset/m_nodeSize);
}

void BufferNode::writeFreeNodes()
{

}

void BufferNode::readFreeNodes()
{
	// si el archivo esta abierto (si existen nodos libres), carga los nodos del archivo
	if (m_freeNodesfile)
	{
		char* bytes = new char[MAXSIZEBUFF];
		unsigned int offset = m_freeNodesfile.tellg();

		m_freeNodesfile.seekg(offset,fstream::beg);
		// Leo solo un bloque, el primero del archivo, ya que tiene los nodos de menor numero
		m_freeNodesfile.read(bytes,MAXSIZEBUFF);
		deserializeFreeNodes(bytes);
	}
}

void BufferNode::deserializeFreeNodes(const char* bytes)
{
	unsigned int nodeNumber;
	unsigned int i = 0;

	for (i = 0; i< MAX_FREENODES_BUFF;i++);
	{
		nodeNumber = ByteConverter::bytesToInt(bytes);
		bytes += sizeof(unsigned int);
//		m_freeNodes.push(nodeNumber);
	}
}

