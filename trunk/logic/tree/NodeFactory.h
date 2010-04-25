/**
 * @file NodeFactory.h
 *
 *  @date: 25/04/2010
 *  @author: kira
 */

#ifndef NODEFACTORY_H_
#define NODEFACTORY_H_

#include "Node.h"
#include "InnerNode.h"
#include "LeafNode.h"

class NodeFactory {

public:
	friend class BPlusTree;
private:

	/**
	 * Lee un bloque y devuelve un nodo.
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el nodo creado
	 * @param block bloque leido.
	 * @return Node (puede ser InnerNode o LeafNode). NULL en caso de no poder leer bien el bloque o
	 *				presentarse error
	 */
	static Node* newNode(Block* block);

};

#endif /* NODEFACTORY_H_ */
