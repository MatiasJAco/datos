/*
 * BPlusTree.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_



#include "../input/InputData.h"

#include "../../physical/file/Block.h"
#include "../../physical/file/BlockFile.h"

#include "Node.h"
#include "InnerNode.h"
#include "LeafNode.h"

//class Node;

class LeafNode;
class InnerNode;

/**
 * Implementacion de arbol B+ guardado en disco
 *
 */
class BPlusTree {

private:
	static const unsigned int ROOT_NODENUMBER = 1;

private:
	/// Atributos propios del arbol por default cuando no son ingresados.
	static const unsigned int SIZENODE_DEFAULT = 512;
	static const double BRANCHFACTOR_DEFAULT = 0.5;

	/// Default del nombre del archivo en donde se guarda el arbol cuando no es ingresado
	/// por parametro.
	static const std::string FILENAME_DEFAULT;

private:
	/// Archivo de bloques donde se almacena el arbol.
	BlockFile file;

	unsigned int m_sizeNodes;
	float m_branchFactor;
	const InputData& m_typeData;

private:
	/// Guardo una referencia a la raiz.
	Node* m_root;
	/// Guardo una referencia al nodo corriente para permitir acceso secuencial.
	Node* m_currentNode;

public:


	/** Constructor que recibe el tamaño y factor de carga de los nodos, y el nombre
	 * del archivo donde se almacena el arbol.
	 * @param nameFile nombre del archivo.
	 * @param sizeNodes tamaño de los nodos.
	 * @param branchFactor factor de carga de los nodos.
	 * @param typedata Un referencia al tipo de dato que almacena.
	 */
	BPlusTree(unsigned int sizeNodes,float branchFactor,const InputData& typedata);

	/** Constructor que recibe el tamaño y factor de carga de los nodos, y el nombre
	 * del archivo donde se almacena el arbol.
	 * @param nameFile nombre del archivo.
	 * @param sizeNodes tamaño de los nodos.
	 * @param branchFactor factor de carga de los nodos.
	 * @param typedata Un referencia al tipo de dato que almacena.
	 */
	BPlusTree(std::string nameFile,unsigned int sizeNodes,float branchFactor,const InputData& typedata);



	bool insert(const InputData& data);

	/// Destructor
	virtual ~BPlusTree();

/// TODO Estos deberian ser privates? o friends?
	/**
	 * Recibe un numero de nodo y devuelve el nodo almacenado en disco.
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el nodo creado
	 * @param nodeNumber identificador del nodo.
	 * @return El nodo. Si no lo encuentra devuelve NULL.
	 */
	Node* getNode(const unsigned int nodeNumber);

	/**
	 * Recibe un numero de nodo y guarda el mismo en disco.
	 * @param nodeNumber El nodo a guardar en disco.
	 */
	void saveNode(Node* node);

	/**
	 * Devuelve un nodo interno,
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el nodo creado
	 * @param level Nivel del nodo interno.
	 * @return El nodo. NULL en caso de algun error.
	 */
	InnerNode* newInnerNode(unsigned int level);

	/**
	 * Devuelve un nodo hoja
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el nodo creado
	 * @return El nodo. NULL en caso de algun error.
	 */
	LeafNode* newLeafNode();

	/**
	 * Elimina un nodo del arbol. Permite que este disponible para usarlo.
	 * @param node. Nodo a eliminar.
	 */
	void deleteNode(Node* node);




};




#endif /* BPLUSTREE_H_ */



