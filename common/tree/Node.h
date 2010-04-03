/*
 * Nodo.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef NODE_H_
#define NODE_H_

#include "../register/Register.h"
#include "../register/Key.h"
#include <list>
#include <map>

class Node : public Register{

public:
	//---------------Constants------------//
	static const unsigned int LEAF_LEVEL = 0;


protected:

	//---------------Typedefs--------------//
	typedef std::map<Key*,Register*> RegisterMap;

	//---------------Atributes-------------//

	/**
	 * unsigned int m_size tamanio del nodo
	 */
	unsigned int m_size;

	/**
	 * unsigned int m_level nivel del nodo (se numeran de las hojas para arriba)
	 */
	unsigned int m_level;

	/**
	 * unsigned int m_qRegisters cantidad de registros
	 */
	unsigned int m_qRegisters;

	/**
	 * RegisterMap m_registers: Los registros en si
	 */
	RegisterMap m_registers;

	/**
	 * unsigned int Espacio libre dentro del nodo
	 */
	unsigned int m_qFreeSpace;

	/**
	 * unsigned int m_Id El Id del nodo (se obtiene con el offset del nodo en disco)
	 * Este dato no se persiste en disco.
	 */
	unsigned int m_NodeNumber;

public:
	//--------------Constructor/Destructor----------------//
	Node();

	Node(unsigned int size,unsigned int level);

	virtual ~Node();

	//-------------Metodos basicos------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param const Register& reg registro a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	virtual bool insert(const Register& reg)=0;

	/**
	 * Elimina el elemento identificado por la clave
	 * @param const Key& key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar
	 */
	virtual bool remove(const Key& key)=0;

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param const Key& key clave del elemento a buscar
	 * @param Register &reg refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	virtual bool find(const Key& key, Register &reg)=0;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param const Key& key clave del elemento a modificar
	 * @param Register &reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	virtual bool modify(const Key& key, Register &reg)=0;

	/**
	 * Evalua si el nodo esta vacio
	 * @return bool TRUE si esta vacio FALSE en caso contrario
	 */
	bool isEmpty();

	/**
	 * Evalua si se supero la capacidad del nodo en una insercion previa
	 * Sirve para evaluar cuando hay que partir el nodo.
	 * @return bool TRUE si se supero la capacidad anteriormente FALSE en caso contrario
	 */
	bool overflow();

	/**
	 * Evalua si la capacidad del nodo esta por debajo del factor de llenado.
	 * Sirve para evaluar cuando hacer un merge de los nodos
	 * @return bool TRUE si se produjo underflow FALSE en caso contrario
	 */
	bool underflow();


	virtual std::string toString() const;
	//---------------Get/Set--------------------------//
	unsigned int getNivel();
	void setNivel(unsigned int nivel);

};

#endif /* NODE_H_ */
