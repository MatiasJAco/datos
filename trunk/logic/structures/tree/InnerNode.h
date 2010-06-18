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

#include "../../../physical/utils/ByteConverter.h"

#include "BPlusTree.h"

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos internos.
 */
class LeafNode;
class BPlusTree;

class InnerNode: public Node {

	friend class BPlusTree;

public:
	typedef enum {MINOR,EQUAL,BIGGER}Condition;

private:
	BPlusTree* m_tree;

private:
    InnerNode(unsigned int nodeNumber, unsigned int level,Block *block,const InputData& typeData, BPlusTree *pointerTree);


public:
    InnerNode(unsigned int nodeNumber, unsigned int level, Block *block,const InputData& typeData);

    ~InnerNode();

public:
	/*********************************************************************************************/

	loadResultEnum insert(const InputData& data,INodeData& promotedKey)throw (NodeException);

	loadResultEnum remove(const InputData& data) throw(NodeException);

    bool find(std::string key, InputData & data) throw (NodeException);

    loadResultEnum modify(const InputData & key, const InputData & dato,INodeData& promotedKey) throw (NodeException);

    loadResultEnum modify(const InputData & data);

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

	/**
	 * Redistribuye el nodo que se encuentra en underflow con el hermano.
	 * @param node Nodo que se encuentra en underflow.
	 * @param siblingNode hermano del nodo con underflow.
	 * @param keyToModify es la clave que se debe promover luego de la redistribucion.
	 * @return bool TRUE si pudo efectuar la operacion. FALSE de lo contrario.
	 */
	bool redistribute(Node* node,Node* siblingNode,const InputData& data,INodeData& keyToModify,sideEnum side=RIGHT_SIDE);

	/**
	 * Fusiona el nodo con su hermano.
	 * @param node Nodo que se encuentra en underflow.
	 * @param siblingNode Hermano del nodo con el cual va a hacer la fusion.
	 * @param fusionatedNode Devuelve la clave principal y el numero de nodo del fusionado.
	 * @return bool TRUE si pudo efectuar la operacion. FALSE de lo contrario.
	 */
	bool merge(Node* node,Node* siblingNode,const InputData& data,INodeData& fusionatedNode,sideEnum side);

	/**
	 * Guarda el nodo.
	 * @param node Nodo a guardar.
	 */
    void save(Node* node);

public:
	/**
	 * Se le pasa una clave y devuelve el INodeData que corresponde a esa clave.
	 * @param innerNodeElem Elemento INodeData que se busca.
	 * @param innerNodeFound elemento que se encontro. Si no se encontro no se modifica
	 * @param condition. Segun se setee la condition, devuelve el igual, o el inmediatamente mayor o
	 * 					menor. El default es igual.
	 * @return bool. TRUE si lo encontro, FALSE de lo contrario.
	 */
	bool findINodeData(INodeData& innerNodeElem,INodeData & innerNodeFound, Condition condition);

	/**
	 * Inserta un elemento INodeData en forma ordenada dentro del InnerNode.
	 * @param iNodeData Elemento de InnerNode que se desea insertar.
	 * @param promotedKey devuelve el valor de la clave a promover como resultado de la insercion.
	 * 					  se debe verificar el valor del return para analizar el dato de promotedKey.
	 * 					  Solo tiene sentido si se devolvio un loadResultEnum distinto de NORMAL_LOAD.
	 * @return dato de tipo loadResultEnum. Posibles valores: OVERFLOW_LOAD,NORMAL_LOAD.
	 */
	loadResultEnum insertINodeData(const INodeData& iNodeData,INodeData& promotedKey) throw(NodeException);

	/**
	 * Elimina un elemento INodeData dentro del InnerNode, a partir de la clave pasada en el parametro.
	 * @param iNodeData Elemento de InnerNode que se desea eliminar.
	 * @return dato de tipo loadResultEnum. Posibles valores: UNDERFLOW_LOAD,NORMAL_LOAD.
	 */
	loadResultEnum removeINodeData(const INodeData& iNodeData) throw (NodeException);

	/**
	 * Modifica un elemento INodeData a partir de la clave pasada en el parametro.
	 * @param iNodeData Elemento de InnerNode que se desea modificar.
	 * @return dato de tipo loadResultEnum. Posibles valores: NORMAL_LOAD.
	 * 										(Al ser de tamaño fijo no hay OVERFLOW ni UNDERFLOW)
	 */
	loadResultEnum modifyINodeData(const INodeData& iNodeData) throw (NodeException);

	/**
	 * Modifica un elemento INodeData a partir de la clave pasada en el parametro, y lo sustituye por lo que
	 * se encuentra en el segundo parametro.
	 * @param iNodeData Elemento de InnerNode que se desea modificar.
	 * @param newINodeData Elemento por el cual se va a modificar
	 * @return dato de tipo loadResultEnum. Posibles valores: NORMAL_LOAD.
	 * 										(Al ser de tamaño fijo no hay OVERFLOW ni UNDERFLOW)
	 */
	loadResultEnum modifyINodeData(const INodeData& iNodeData,const INodeData& newINodeData) throw (NodeException);

	/**
	 * Imprime en pantalla los elementos de un nodo interno.
	 */
	void printContent();

	/**
	 * Muestra por pantalla todos los elementos de su nivel y hacia abajo.
	 */
	void show();


	void modifyLastKey();

	INodeData getFirstKeyLeaf(Node* searchNode,const InputData&  data);

	INodeData getLastINodeData();

};

#endif /* INNERNODE_H_ */
