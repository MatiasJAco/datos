/**
 * @file Node.h
 * @author Alex - MCM
 */

#ifndef LEAF_H_
#define LEAF_H_

#include "Node.h"
#include <iostream>
#include <sstream>

#include "BPlusTree.h"

/**
 *	Permite el manejo en memoria de los datos almacenados en el arbol.
 *	Estructura que representa a los nodos hojas.
 */
class BPlusTree;

class LeafNode: public Node {

	friend class BPlusTree;

private:
	BPlusTree* m_tree;

private:
	//--------------Constructor/Destructor----------------//
	LeafNode(unsigned int nodeNumber,Block* block,BPlusTree* pointerTree);

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
	INodeData* insert(const InputData & dato,loadResultEnum& result);

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

public:
	/*********************************************************************************************/

	loadResultEnum insert_(const InputData& data,INodeData& promotedKey);


	/*********************************************************************************************/

private:
	/**
	 * Separa la hoja en otra, quedando unida a la misma.
	 * Devuelve la clave de promocion para el siguiente nivel.
	 * @param data Elemento que produjo el split.
	 * @param pos posicion donde va el dato.
	 * @param promotedKey clave que se promueve a partir de esta operacion.
	 * @return bool que indica si tuvo exito la operacion de split.
	 */
	bool split(const InputData& data,unsigned int pos,INodeData& promotedKey);

public:
	/**
	 * Devuelve el puntero a la siguiente hoja.
	 * @return Numero de nodo o identificador.
	 */
	unsigned int getNext();

	/**
	 * Devuelve el puntero a la hoja anterior.
	 * @return Numero de nodo o identificador.
	 */
	unsigned int getPrevious();


	/**
	 * Imprime el contenido del nodo por pantalla.
	 * @param data un dato del tipo que se emplea internamente, para saber que tipos de dato
	 * tenemos
	 */
	void printContent(InputData & data);

};

#endif /* LEAF_H_ */
