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

#include "../logic/tree/dataNode/INodeData.h"
#include "../../physical/utils/ByteConverter.h"

#include "BPlusTree.h"

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos internos.
 */

class BPlusTree;

class InnerNode: public Node {

public:

//	friend class BPlusTree::NodeFactory;


	BPlusTree* m_tree;

public:
	/// Constructor.
	InnerNode();

	/**
	 * Constructor.
	 * @param nodeNumber Identificador del nodo.
	 * @param level Nivel en el que se encuentra el nodo.
	 */
	InnerNode(unsigned int nodeNumber,unsigned int level);

	/// Destructor.
	~InnerNode();

	//-------------Metodos de operación basicos sobre registros ------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param registro registro a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	loadResultEnum insert(const InputData& dato);

	/**
	 * Elimina el elemento identificado por la clave
	 * @param key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar
	 */
	loadResultEnum remove(const InputData& key);

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param key clave del elemento a buscar
	 * @param registro refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	bool find(const InputData& key,InputData& data) const;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param registro valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	loadResultEnum modify(const InputData& key, const InputData& dato);

	/**
	 * Modifica el nodo identificado por la clave de data
	 * Si lo encuentra escribe el contenido de data en el nodo.
	 * @param data valor que se colocara en el nodo.
	 * @return loadResultEnum TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	loadResultEnum modify(const InputData& data);


	/// Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!
	unsigned int getUsedSpace();

	void divide(Node* destNode);

	void join(Node* fusionNode);

	/**
	 * Simula la eliminacion de una determinada cantidad de bytes.
	 *
	 * **/
	bool falseRemove(unsigned int toRemove);

	/**
	*Dona una cantidad minima determinada de bytes a otro nodo.
	*
	***/
	void donate(Node* destNode,unsigned int toDonate);

};

#endif /* INNERNODE_H_ */
