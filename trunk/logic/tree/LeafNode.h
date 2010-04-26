/**
 * @file Node.h
 * @author Alex - MCM
 */

#ifndef LEAF_H_
#define LEAF_H_

#include "Node.h"
#include <iostream>
#include <sstream>

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos hojas.
 */
class LeafNode: public Node {

	friend class BPlusTree;

private:
	//--------------Constructor/Destructor----------------//
	LeafNode(unsigned int nodeNumber,Block* block);

public:
	/// Constructor
	LeafNode();

	/**
	 * Constructor.
	 * @param nodeNumber Identificador del nodo.
	 */
	LeafNode(unsigned int nodeNumber);

	/// Destructor.
	~LeafNode();

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
	loadResultEnum remove(const InputData& dato);

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
	loadResultEnum modify(const InputData& dato, const InputData& dato2);

	/**
	 * Modifica el nodo identificado por la clave de data
	 * Si lo encuentra escribe el contenido de data en el nodo.
	 * @param data valor que se colocara en el nodo.
	 * @return loadResultEnum TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	loadResultEnum modify(const InputData& data);


	/**
	 * Imprime el contenido del nodo por pantalla.
	 * @param data un dato del tipo que se emplea internamente, para saber que tipos de dato
	 * tenemos
	 */
	void printContent(InputData & data);


	void divide(Node* destNode,const InputData& newData);

	/**
	 * Simula la eliminacion de una determinada cantidad de bytes.
	 *
	 * **/
	bool falseRemove(unsigned int toRemove);

	void join(Node* fusionNode);

	/**
	*Dona una cantidad minima determinada de bytes a otro nodo.
	*
	***/
	bool donate(Node* destNode,const InputData& deletedData);


};

#endif /* LEAF_H_ */
