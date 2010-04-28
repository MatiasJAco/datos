/**
 * @file InnerNode.h
 * @author MCM
 *
 */

#ifndef INNERNODE_H_
#define INNERNODE_H_

#include <iostream>
#include <sstream>

#include "Node.h"
#include "LeafNode.h"

//#include "../logic/tree/dataNode/INodeData.h"
#include "../../physical/utils/ByteConverter.h"

#include "BPlusTree.h"

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos internos.
 */
class LeafNode;
class BPlusTree;

class InnerNode: public Node {

	friend class BPlusTree;

private:
	BPlusTree* m_tree;

private:

	unsigned int buscarPosicionInner(InnerNode *& nodoAPartir,INodeData & newData);
	unsigned int buscarPosicionLeaf(LeafNode *& nodoAPartir,const InputData & newData);


private:
    InnerNode(unsigned int nodeNumber, unsigned int level, Block *block, BPlusTree *pointerTree);
public:
    InnerNode();
    InnerNode(unsigned int nodeNumber);
    ~InnerNode();
    loadResultEnum remove(const InputData & key);
    bool find(const InputData & key, InputData & data) const;
    loadResultEnum modify(const InputData & key, const InputData & dato);
    loadResultEnum modify(const InputData & data);
//    void insertINodeData(INodeData *contBuscado);
    void join(Node *toDivide, Node *destNode, const InputData & newData);
    void save(Node* node);

private:

	INodeData* divideLeaf (Node* toDivide,Node* destNode,const InputData& newData);

	INodeData* divideInner(Node* aPartir,Node* destNode,INodeData& newData);

	bool balanceLeaf(Node* underNode,Node* toDonate,const InputData& newData);

	bool balanceInner(Node* underNode,Node* toDonate, INodeData& newData);




public:
	/*********************************************************************************************/

	loadResultEnum insert(const InputData& data,INodeData& promotedKey);

	/*********************************************************************************************/

private:
	/**
	 * Separa el nodo en otro.
	 * Devuelve la clave de promocion para el siguiente nivel.
	 * @param data Elemento que produjo el split.
	 * @param pos posicion donde va el dato.
	 * @param promotedKey clave que se promueve a partir de esta operacion.
	 * @return bool que indica si tuvo exito la operacion de split.
	 */
	bool split(const INodeData& data,unsigned int pos,INodeData& promotedKey);
public:
	/**
	 * Se le pasa una clave y devuelve el INodeData que corresponde a esa clave.
	 * @param innerNodeElem Elemento INodeData que se busca.
	 * @param less Si no encuentra el elemento devuelve el inmediatamente menor o mayor segun el valor
	 * 				de este parametro opcional. El default es devolver el menor.
	 * @return bool. TRUE si lo encontro, FALSE de lo contrario.
	 */
	bool findINodeData(INodeData& innerNodeElem,bool less = true);

	/**
	 * Inserta un elemento INodeData en forma ordenada dentro del InnerNode.
	 * @param iNodeData Elemento de InnerNode que se desea insertar.
	 * @param promotedKey devuelve el valor de la clave a promover como resultado de la insercion.
	 * 					  se debe verificar el valor del return para analizar el dato de promotedKey.
	 * 					  Solo tiene sentido si se devolvio un loadResultEnum distinto de NORMAL_LOAD.
	 * @return dato de tipo loadResultEnum. Posibles valores: OVERFLOW_LOAD,NORMAL_LOAD.
	 */
	loadResultEnum insertINodeData(const INodeData& iNodeData,INodeData& promotedKey);

	/**
	 * Elimina un elemento INodeData dentro del InnerNode, a partir de la clave pasada en el parametro.
	 * @param iNodeData Elemento de InnerNode que se desea eliminar.
	 * @return dato de tipo loadResultEnum. Posibles valores: UNDERFLOW_LOAD,NORMAL_LOAD.
	 */
	loadResultEnum removeINodeData(const INodeData& iNodeData);

	/**
	 * Modifica un elemento INodeData a partir de la clave pasada en el parametro.
	 * @param iNodeData Elemento de InnerNode que se desea modificar.
	 * @return dato de tipo loadResultEnum. Posibles valores: NORMAL_LOAD.
	 * 										(Al ser de tamaño fijo no hay OVERFLOW ni UNDERFLOW)
	 */
	loadResultEnum modifyINodeData(const INodeData& iNodeData);

};

#endif /* INNERNODE_H_ */
