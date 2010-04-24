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
#include "../logic/input/InputData.h"
#include "../physical/file/Block.h"


class Node{

protected:

	//---------------Constants------------//
	/// Define el nivel de un nodo hoja
	static const unsigned int LEAF_LEVEL = 0;
	/// Definicion de constante para los nodos que no tienen asignado un identificador.
	static const unsigned int UNDEFINED_NODE_NUMBER = -1;

	//---------------Atributes-------------//

	/// Tamaño del nodo.
	unsigned int m_size;

	/// Nivel del nodo.
	unsigned int m_level;

	/// Identificador del nodo.
	unsigned int m_nodeNumber;

	/// Factor de carga del nodo. Da una indicacion de cuando se produce overflow o underflow.
	unsigned int m_branchFactor;

	Block* m_bloque;


public:

	//--------------Constructor/Destructor----------------//
	Node();

	/**
	 * Constructor.
	 * @param level Nivel en el que se encuentra el nodo.
	 * @param size Tamaño del nodo
	 * @param branchFactor Factor de carga que determina cuando el nodo esta por debajo o por encima
	 * de la cantidad minima/maxima de pares clave-valor.
	 */
	Node(unsigned int level,unsigned int size,double branchFactor);
	/**
	 * Constructor.
	 * @param nodeNumber Identificador del nodo.
	 * @param level Nivel en el que se encuentra el nodo.
	 * @param size Tamaño del nodo
	 * @param branchFactor Factor de carga que determina cuando el nodo esta por debajo o por encima
	 * de la cantidad minima/maxima de pares clave-valor.
	 */
	Node(unsigned int nodeNumber,unsigned int level,unsigned int size,double branchFactor);

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
	virtual bool insert(const InputData &data) = 0;

	/**
	 * Elimina el elemento identificado por la clave
	 * @param key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar, FALSE de lo contrario.
	 */
	virtual bool remove(const InputData &data) = 0;

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param key clave del elemento a buscar
	 * @param reg refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	virtual bool find(const InputData &data1,const InputData &data2)const = 0;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	virtual bool modify(const InputData& data1, const InputData& data2) = 0;

	/**
	 * Evalua si el nodo esta vacio.
	 * @return bool TRUE si esta vacio FALSE en caso contrario
	 */
	bool isEmpty();

	/**
	 * Evalua si se supero la capacidad del nodo en una insercion previa.
	 * Sirve para evaluar cuando hay que partir el nodo.
	 * @return bool TRUE si se supero la capacidad anteriormente FALSE en caso contrario
	 */
	bool overflow();

	/**
	 * Evalua si la capacidad del nodo esta por debajo del factor de llenado.
	 * Sirve para evaluar cuando hacer una union de los nodos.
	 * @return bool TRUE si se produjo underflow FALSE en caso contrario
	 */
	bool underflow();

	// TODO falta definir los metodos split y join (supongo que irian solo en InnerNode)

	/**
	 * Obtiene el espacio utilizado del nodo, tomando el mapa de
	 * registros y viendo el tamaño de cada elemento.
	 * @return unsigned int espacio en uso
	 */
	virtual unsigned int getUsedSpace() = 0;

	//---------------Get/Set--------------------------//

	/// Devuelve el nivel del nodo
	unsigned int getLevel()const;
	/// Modifica el nivel del nodo
	void setLevel(const unsigned int level);

	/// Devuelve el tamaño del nodo. No existe metodo para modificar el tamaño una vez construido.
	unsigned int getSize() const;

	/// Obtiene el identificador.
	unsigned int getNodeNumber()const;
	/// Modifica el identificador.
	void setNodeNumber(unsigned int number);

	/// Devuelve el factor de carga del nodo.
	double getBranchFactor() const;
	/// Modifica el factor de carga.
	void setBranchFactor(double branchFactor);

	virtual bool isLeaf() = 0;

	virtual void divide(Node* destNode) = 0;

	/**
	 * Simula la eliminacion de una determinada cantidad de bytes.
	 *Devuelve true si se puede hacer si que se de underflow.
	 * **/
	bool falseRemove(unsigned int toRemove);

	virtual void join(Node* fusionNode) = 0;


	/**
	*Dona una cantidad minima determinada de bytes a otro nodo.
	*
	***/
	virtual void donate(Node* destNode,unsigned int toDonate) = 0;

protected:

	virtual void save() = 0;

};

#endif /* NODE_H_ */
