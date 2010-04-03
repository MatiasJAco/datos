/*
 * Nodo.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef NODE_H_
#define NODE_H_

#include "../register/Register.h"
#include <list>
#include <set>

class Node : public Register{

public:
	static const unsigned int LEAF_LEVEL = 0;


protected:

	typedef std::set<Register*,RegisterCmp> Registers;

	unsigned int size;

	/// Campos de control
	unsigned int m_level;
	unsigned int m_qRegisters;
	Registers m_registers;

	/// Espacio libre dentro del nodo
	unsigned int m_qFreeSpace;





public:
	Node();

	Node(unsigned int size,unsigned int level);

	virtual ~Node();

	virtual void insert(const Register& reg);
	//virtual void remove(const Key& key);

	virtual bool hadOverflow();

};

#endif /* NODE_H_ */
