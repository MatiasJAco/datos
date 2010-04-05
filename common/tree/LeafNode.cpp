/*
 * Bucket.cpp
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#include "LeafNode.h"

using namespace std;

LeafNode::LeafNode() {
	// TODO Auto-generated constructor stub

}

LeafNode::~LeafNode() {
	// TODO Auto-generated destructor stub

}

LeafNode::LeafNode(unsigned int nodeNumber, unsigned int size, unsigned int branchFactor):Node(nodeNumber,Node::LEAF_LEVEL,size,branchFactor)
{
	m_prevNode = 0;
	m_nextNode = 0;
}

LeafNode::LeafNode(unsigned int size, unsigned int branchFactor):Node(Node::LEAF_LEVEL,size,branchFactor)
{
	m_prevNode = 0;
	m_nextNode = 0;
}

bool LeafNode::insert(const Register & registro)
{
	// Recordar: en el insert aun cuando haya overflow, se estan agregando los registros al map
	// en algun momento deberian ser borrados. (split?)

	bool retVal = true;

	Register* reg = registro.newInstance();
	Register* key  = registro.getRegisterKey();

	pair<RegisterMapIterator,bool> p = m_registers.insert(RegisterMapPair(key, reg));
	retVal = p.second;

	return retVal;
}

bool LeafNode::remove(const Register & key)
{
	Register* keyreg = key.newInstance();

	RegisterMapIterator it = m_registers.find(keyreg);

	bool found = (it!=m_registers.end());

	if( found ){
		delete (it->first);
		delete (it->second);
		m_registers.erase(it);
	}

	delete keyreg;

	return found;
}

bool LeafNode::modify(const Register & key, const Register & registro)
{
	Register* keyreg = key.newInstance();

	RegisterMapIterator it = m_registers.find(keyreg);

	bool found = (it!=m_registers.end());

	if( found ){
		Register * reg = it->second;
		reg->setFields(registro);
	}

	delete keyreg;

	return found;
}

bool LeafNode::find(const Register & key, Register & registro)const
{
	Register* keyreg = key.newInstance();
	RegisterMap map = m_registers;

	RegisterMapIterator it = map.find(keyreg);

	bool found = (it!=m_registers.end());

	if( found ){
		Register* reg = it->second;
		registro.setFields(*reg);
	}

	delete keyreg;

	return found;
}

/**
 * Serializa el registro en bytes
 * \param bytes Cadena de bytes en la que almacena el contenido del registro
 * \return El puntero a la cadena de bytes
 */
char* LeafNode::serializeChilds(char* bytes) const
{
	ByteConverter::uIntToBytes(m_prevNode,bytes);
	bytes+= sizeof(m_prevNode);
	ByteConverter::uIntToBytes(m_nextNode,bytes);
	return bytes;
}

/**
 * Transforma la cadena de bytes a un registro
 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
 */
void LeafNode::deserializeChilds(const char* bytes)
{
	m_prevNode = ByteConverter::bytesToUInt(bytes);
	bytes+= sizeof(m_prevNode);
	m_nextNode = ByteConverter::bytesToUInt(bytes);
}

Register *LeafNode::newInstance() const
{
	return new LeafNode();
}

string LeafNode::toString()const
{
	stringstream ss;
	RegisterMapIterator iter;
	RegisterMap map = m_registers;

	ss <<"NodeNumber " << m_nodeNumber << endl;
	ss <<"Nivel " << m_level << endl;
	ss <<"Tamanio " << m_size << endl;
	ss <<"Prev " << m_prevNode << endl;
	ss <<"Next " << m_nextNode << endl;


	for (iter = map.begin(); iter != map.end(); iter++)
	{
		ss << *(iter->second);
	}

	return ss.str();
}


void LeafNode::setFields(const Register& registro)
{
	const LeafNode& node = dynamic_cast<const LeafNode&>(registro);

	Node::setFields(registro);
	m_prevNode = node.m_prevNode;
	m_nextNode = node.m_nextNode;
}



