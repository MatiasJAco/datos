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
 *	Implementa los metodos de Register para su persistencia en disco.
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
	LeafNode(unsigned int size,unsigned int branchFactor);

	/**
	 * Constructor
	 * @param nodeNumber Identificador del nodo hoja.
	 * @param size Tamaño del nodo hoja.
	 * @param branchFactor Factor de carga del nodo hoja.
	 */
	LeafNode(unsigned int nodeNumber,unsigned int size,unsigned int branchFactor);

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
	bool find(const InputData& dato, InputData& dato) const;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param registro valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	bool modify(const InputData& dato, const InputData& dato);


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
	 * Devuelve un string con el contenido del registro
	 * Se debe definir en cada clase obligatoriamente, para
	 * ser utilizada por el operador << en Register
	 * @return string con la informacion contenida en el registro
	 * @see Register operator <<
	 */
	std::string toString()const;

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	void setFields(const InputData& dato);


protected:
	//-------------------Serialize/Deserialize--------------------//

	/**
	 * Serializa el registro en bytes.
	 * @param bytes Cadena de bytes en la que almacena el contenido del registro
	 * @return El puntero a la cadena de bytes
	 */
	char* serializeChilds(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * @param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserializeChilds(const char* bytes);

};

#endif /* LEAF_H_ */
