/*
 * BPlusTree.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef BPLUSTREE_H_
#define BPLUSTREE_H_



#include "../logic/input/InputData.h"

#include "../physical/file/Block.h"
#include "../physical/file/BlockFile.h"
#include "Node.h"
//#include "NodeFactory.h"


class BPlusTree {

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
	double m_branchFactor;

private:
	/// Guardo una referencia a la raiz.
	Node* m_root;
	/// Guardo una referencia al nodo corriente para permitir acceso secuencial.
	Node* m_currentNode;

public:
	/// Constructor por defecto
	BPlusTree();

	/// Constructor que recibe el tamaño y factor de carga de los nodos.
	BPlusTree(unsigned int sizeNodes,double branchFactor);

	/** Constructor que recibe el tamaño y factor de carga de los nodos, y el nombre
	 * del archivo donde se almacena el arbol.
	 * @param nameFile nombre del archivo.
	 * @param sizeNodes tamaño de los nodos.
	 * @param branchFactor factor de carga de los nodos.
	 */
	BPlusTree(std::string nameFile,unsigned int sizeNodes,double branchFactor);

	/// Destructor
	virtual ~BPlusTree();

	/**
	 * Recibe un numero de nodo y devuelve el nodo almacenado en disco.
	 * Como crea la instancia internamente, luego es necesario destruir desde afuera
	 * el nodo creado
	 * @param nodeNumber identificador del nodo.
	 * @return El nodo.
	 */
	Node* getNode(const unsigned int nodeNumber);


	int getNodeQuantity();

};




#endif /* BPLUSTREE_H_ */



