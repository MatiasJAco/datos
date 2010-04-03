/*
 * Bucket.h
 *
 *  Created on: 24/03/2010
 *      Author: kira
 */

#ifndef LEAF_H_
#define LEAF_H_

#include "Node.h"
#include <iostream>
#include <sstream>

class LeafNode: public Node {

private:
	unsigned int m_NextNode;
	unsigned int m_PrevNode;

public:
	LeafNode();
	LeafNode(unsigned int size,unsigned int BranchFactor);
	LeafNode(unsigned int NodeNumber,unsigned int size,unsigned int BranchFactor);
	~LeafNode();


	std::string toString()const;

	/**
	 * Devuelve una instancia nueva de la clase.
	 * Se crea una nueva instancia del tipo especifico con new()
	 * Importante: Una vez que se termine de usar la instancia
	 * es necesario liberar la memoria mediante un delete.
	 * @throws bad_alloc en caso de error al asignar memoria
	 * @return Register * puntero a la instancia nueva
	 */
	Register * newInstance() const;

	/**
	 * Obtiene el tamaño del registro.
	 * \return El tamaño del registro.
	 */
	unsigned int getSize() const;



	//-------------Metodos basicos------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param const Register& reg registro a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	bool insert(const Register& reg);

	/**
	 * Elimina el elemento identificado por la clave
	 * @param const Key& key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar
	 */
	bool remove(const Register& key);

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param const Key& key clave del elemento a buscar
	 * @param Register &reg refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	bool find(const Register& key, Register &reg) const;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param const Key& key clave del elemento a modificar
	 * @param Register &reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	bool modify(const Register& key, const Register &reg);


	//-------------------Serialize/Deserialize--------------------//

	/**
	 * Serializa el registro en bytes
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);


};

#endif /* LEAF_H_ */
