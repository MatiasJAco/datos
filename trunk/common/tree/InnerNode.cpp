/*
 * InnerNode.cpp
 *
 *  Created on: 03/04/2010
 *      Author: kira
 */

#include "InnerNode.h"

using namespace std;

InnerNode::InnerNode() {
	// TODO Auto-generated constructor stub

}

InnerNode::InnerNode(unsigned int nodeNumber, unsigned int level, unsigned int size, unsigned int branchFactor)
:Node(nodeNumber,level, size, branchFactor)
{
}

InnerNode::InnerNode(unsigned int level, unsigned int size, unsigned int branchFactor)
:Node(level, size, branchFactor)
{
}

InnerNode::~InnerNode() {
	// TODO Auto-generated destructor stub
}

bool InnerNode::insert(const Register & registro)
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

bool InnerNode::remove(const Register & key)
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

bool InnerNode::modify(const Register & key, const Register & registro)
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

bool InnerNode::find(const Register & key, Register & registro)const
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
char* InnerNode::serializeChilds(char* bytes) const
{
	return bytes;
}

/**
 * Transforma la cadena de bytes a un registro
 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
 */
void InnerNode::deserializeChilds(const char* bytes)
{
}

Register *InnerNode::newInstance() const
{
	return new InnerNode();
}

string InnerNode::toString()const
{
	stringstream ss;
	RegisterMapIterator iter;
	RegisterMap map = m_registers;

	ss <<"NodeNumber " << m_nodeNumber << endl;
	ss <<"Nivel " << m_level << endl;
	ss <<"Tamanio " << m_size << endl;

	for (iter = map.begin(); iter != map.end(); iter++)
	{
		ss << *(iter->second);
	}

	return ss.str();
}


void InnerNode::setFields(const Register& registro)
{
//	const InnerNode& node = dynamic_cast<const InnerNode&>(registro);

	Node::setFields(registro);

	// TODO falta
}
