/*
 * Node.h
 *
 *  Created on: 14/04/2010
 *      Author: matias
 */

#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <sstream>

#include "../../input/InputData.h"
#include "../../../physical/file/Block.h"
#include "../../../physical/file/BlockManager.h"
#include "dataNode/INodeData.h"


class Node{

public:

	friend class BPlusTree;

public:

	//---------------Constants------------//
	/// Define el nivel de un nodo hoja
	static const unsigned int LEAF_LEVEL = 0;

	/// Definicion de constante para los nodos que no tienen asignado un identificador.
	static const unsigned int UNDEFINED_NODE_NUMBER = -1;
	static const unsigned int UNDEFINED_NODE_LEVEL = -1;

protected:
	//---------------Atributes-------------//
	/// Identificador del nodo.
	unsigned int m_nodeNumber;

	Block* m_block;


protected:
	//--------------Constructor/Destructor----------------//
	Node(unsigned int nodeNumber,unsigned int level,Block* block);

public:

	//--------------Constructor/Destructor----------------//
	Node();

	/**
	 * Constructor.
	 * @param nodeNumber Identificador del nodo.
	 * @param level Nivel en el que se encuentra el nodo.
	 */
	Node(unsigned int nodeNumber);

	/// Destructor
	virtual ~Node();

	//-------------Metodos basicos------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param data par clave-valor a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	virtual loadResultEnum insert(const InputData& data,INodeData& promotedKey) = 0;

	/**
	 * Elimina el elemento identificado por la clave
	 * @param key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar, FALSE de lo contrario.
	 */


	virtual loadResultEnum remove(const InputData& data) = 0;

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param key clave del elemento a buscar
	 * @param reg refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	virtual bool find(std::string key,InputData &data) = 0;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	virtual loadResultEnum modify(const InputData& data1, const InputData& data2,INodeData& promotedKey) = 0;

	/**
	 * Modifica el nodo identificado por la clave de data
	 * Si lo encuentra escribe el contenido de data en el nodo.
	 * @param data valor que se colocara en el nodo.
	 * @return loadResultEnum TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	virtual loadResultEnum modify(const InputData& data) = 0;


	virtual void printContent() = 0;

	virtual void show() = 0;

	/**
	* Permite obtener el primer dato de una hoja.
	*/
	virtual bool getFirstData(InputData &data) = 0;
	/**
	 * Evalua si el nodo esta vacio.
	 * @return bool TRUE si esta vacio FALSE en caso contrario
	 */
	bool isEmpty();


	bool isLeaf();


	//---------------Get/Set--------------------------//

	/// Devuelve el nivel del nodo
	unsigned int getLevel();
	/// Modifica el nivel del nodo
	void setLevel(const unsigned int level);


	/// Obtiene el identificador.
	unsigned int getNodeNumber()const;

	Block* getBlock();

	void setNodeNumber(unsigned int number);

protected:

	void setBlock(Block* block);

	static unsigned int readLevel(Block block);

};

#endif /* NODE_H_ */
