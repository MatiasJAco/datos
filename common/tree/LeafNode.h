/**
 * @file Node.h
 * @author Alex - MCM
 */

#ifndef LEAF_H_
#define LEAF_H_

#include "Node.h"
#include <iostream>
#include <sstream>

class LeafNode: public Node {

private:

	unsigned int m_prevNode;
	unsigned int m_nextNode;

public:
	LeafNode();
	LeafNode(unsigned int size,unsigned int branchFactor);
	LeafNode(unsigned int nodeNumber,unsigned int size,unsigned int branchFactor);
	~LeafNode();

	//-------------Metodos basicos------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param const Register& reg registro a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	bool insert(const Register& registro);

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
	bool find(const Register& key, Register &registro) const;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param const Key& key clave del elemento a modificar
	 * @param Register &reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	bool modify(const Register& key, const Register &registro);


	/**
	 * Devuelve una instancia nueva de la clase.
	 * Se crea una nueva instancia del tipo especifico con new()
	 * Importante: Una vez que se termine de usar la instancia
	 * es necesario liberar la memoria mediante un delete.
	 * @throws bad_alloc en caso de error al asignar memoria
	 * @return Register * puntero a la instancia nueva
	 */
	Register * newInstance() const;

	std::string toString()const;

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	void setFields(const Register& registro);


protected:
	//-------------------Serialize/Deserialize--------------------//

	/**
	 * Serializa el registro en bytes.
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	char* serializeChilds(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserializeChilds(const char* bytes);

};

#endif /* LEAF_H_ */
