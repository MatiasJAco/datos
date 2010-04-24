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

private:
	/// Puntero al nodo anterior.
	unsigned int m_prevNode;
	/// Puntero al nodo siguiente.
	unsigned int m_nextNode;


public:
	/// Constructor
	LeafNode();
	/**
	 * Constructor
	 * @param size Tamaño del nodo hoja.
	 * @param branchFactor Factor de carga del nodo hoja.
	 */
	LeafNode(unsigned int size,double branchFactor);

	/**
	 * Constructor
	 * @param nodeNumber Identificador del nodo hoja.
	 * @param size Tamaño del nodo hoja.
	 * @param branchFactor Factor de carga del nodo hoja.
	 */
	LeafNode(unsigned int nodeNumber,unsigned int size,double branchFactor);

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
	bool insert(const InputData& dato);

	/**
	 * Elimina el elemento identificado por la clave
	 * @param key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar
	 */
	bool remove(const InputData& dato);

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param key clave del elemento a buscar
	 * @param registro refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	bool find(const InputData& data1, const InputData& data2) const;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param registro valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	bool modify(const InputData& dato, const InputData& dato2);

	/**
	 * Obtiene el espacio utilizado del nodo, tomando el mapa de
	 * registros y viendo el tamaño de cada elemento.
	 * @return unsigned int espacio en uso
	 */
	unsigned int getUsedSpace();

	bool isLeaf();

	void divide(Node* destNode);


protected:

	void join();

	void save();

};

#endif /* LEAF_H_ */
