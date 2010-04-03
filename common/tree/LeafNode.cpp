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


bool LeafNode::insert(const Register & reg)
{
	bool retVal=true;
	RegisterMapIterator it;

	Register* reg1 = reg.newInstance();
	Register* key;


	it = m_registers.find(reg1);

	if(it == m_registers.end())
	{
		key = reg1->getRegisterKey();
		m_registers.insert(m_registers.end(),RegisterMapPair(key, reg1));
	}
	//En caso que ya este no se crea el elemento
	else
	{
		//Pongo el valor de retorno en false y elimino el registro reg1
		//que se uso para buscar en el mapa, ya que este no se va a insertar
		retVal=false;
		delete reg1;
	}

	delete key;
	return retVal;
}

LeafNode::LeafNode(unsigned int NodeNumber, unsigned int size, unsigned int branchFactor):Node(NodeNumber,0,size,branchFactor)
{
	m_PrevNode=0;
	m_NextNode=0;
}

LeafNode::LeafNode(unsigned int size, unsigned int branchFactor):Node(0,size,branchFactor)
{
	m_PrevNode=0;
	m_NextNode=0;
}

Register *LeafNode::newInstance() const
{
	return new LeafNode();

}

unsigned int LeafNode::getSize() const
{
	//TODO VER TAMAÑO
	return 0;
}

bool LeafNode::remove(const Register & key)
{
	return true;

}

bool LeafNode::modify(const Register & key, const Register & reg)
{
	return true;

}

bool LeafNode::find(const Register & key, Register & reg) const
{
	return true;

}

/**
 * Serializa el registro en bytes
 * \param bytes Cadena de bytes en la que almacena el contenido del registro
 * \return El puntero a la cadena de bytes
 */
char* LeafNode::serialize(char* bytes) const
{
	return bytes;
}

/**
 * Transforma la cadena de bytes a un registro
 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
 */
void LeafNode::deserialize(const char* bytes)
{

}

string LeafNode::toString()const
{
	stringstream ss;
	RegisterMapIterator iter;
	RegisterMap map = m_registers;

	ss <<"NodeNumber " <<m_nodeNumber<<endl;
	ss <<"Nivel " <<m_level<<endl;
	ss <<"Prev " <<m_PrevNode<<endl;
	ss <<"Next " <<m_NextNode<<endl;


	for (iter = map.begin(); iter != map.end(); iter++)
	{
		ss << *(iter->second);
	}

	return ss.str();
}




