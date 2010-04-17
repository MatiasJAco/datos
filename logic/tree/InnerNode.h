/**
 * @file InnerNode.h
 * @author MCM
 *
 */

#ifndef INNERNODE_H_
#define INNERNODE_H_

#include "Node.h"
#include <iostream>
#include <sstream>

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos internos.
 */
class InnerNode: public Node {

public:
	/// Constructor.
	InnerNode();

	/**
	 * Constructor
	 * @param level Nivel en donde se encuentra el nodo interno.
	 * @param size Tamaño del nodo.
	 * @param branchFactor Factor de carga del nodo.
	 */
	InnerNode(unsigned int level,unsigned int size,double branchFactor);

	/**
	 * Constructor
	 * @param nodeNumber Identificador del nodo.
	 * @param level Nivel en donde se encuentra el nodo.
	 * @param size Tamaño del nodo hoja.
	 * @param branchFactor Factor de carga del nodo hoja.
	 */
	InnerNode(unsigned int nodeNumber,unsigned int level,unsigned int size,double branchFactor);

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
	bool insert(const InputData& dato);

	/**
	 * Elimina el elemento identificado por la clave
	 * @param key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar
	 */
	bool remove(const InputData& key);

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param key clave del elemento a buscar
	 * @param registro refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	bool find(const InputData& key, const InputData& dato) const;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param registro valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	bool modify(const InputData& key, const InputData& dato);

	unsigned int getUsedSpace();

protected:

	void divide();

	void join();

	void save();


};

#endif /* INNERNODE_H_ */
