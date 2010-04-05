/**
 * @file Node.h
 * @author Alex - MCM
 */

#ifndef NODE_H_
#define NODE_H_

#include "../register/Register.h"
#include "../utils/ByteConverter.h"

#include <map>

/**
 * Permite el manejo en memoria de los datos que almacena el arbol.
 * Define la interfaz para realizar operaciones sobre los registros que se almacenan en el arbol.
 * Hereda de Register por lo cual tambien permite su manipulacion para su persistencia en disco.
 */
class Node : public Register{

public:
	//---------------Constants------------//
	/// Define el nivel de un nodo hoja
	static const unsigned int LEAF_LEVEL = 0;
	/// Definicion de constante para los nodos que no tienen asignado un identificador.
	static const unsigned int UNDEFINED_NODE_NUMBER = -1;

protected:

	//---------------Typedefs--------------//
	/// Tipo de dato Map que se utiliza para almacenar los registros del nodo.
	typedef std::map<Register*,Register*,RegisterComparator> RegisterMap;
	/// Iterador de RegisterMap
	typedef RegisterMap::iterator RegisterMapIterator;
	/// Tipo de dato pair para los datos del RegisterMap.
	typedef std::pair<Register*,Register*> RegisterMapPair;

	//---------------Atributes-------------//

	/// Tamaño del nodo.
	unsigned int m_size;

	/// Nivel del nodo.
	unsigned int m_level;

	/// Registros que contiene el nodo.
	RegisterMap m_registers;

	/// Identificador del nodo.
	unsigned int m_nodeNumber;

	/// Factor de carga del nodo. Da una indicacion de cuando se produce overflow o underflow.
	unsigned int m_branchFactor;

public:
	//--------------Constructor/Destructor----------------//
	Node();

	/**
	 * Constructor.
	 * @param level Nivel en el que se encuentra el nodo.
	 * @param size Tamaño del nodo
	 * @param branchFactor Factor de carga que determina cuando el nodo esta por debajo o por encima
	 * de la cantidad minima/maxima de registros.
	 */
	Node(unsigned int level,unsigned int size,unsigned int branchFactor);
	/**
	 * Constructor.
	 * @param nodeNumber Identificador del nodo.
	 * @param level Nivel en el que se encuentra el nodo.
	 * @param size Tamaño del nodo
	 * @param branchFactor Factor de carga que determina cuando el nodo esta por debajo o por encima
	 * de la cantidad minima/maxima de registros.
	 */
	Node(unsigned int nodeNumber,unsigned int level,unsigned int size,unsigned int branchFactor);

	/// Destructor
	virtual ~Node();

	//-------------Metodos basicos------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param reg registro a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	virtual bool insert(const Register& reg) = 0;

	/**
	 * Elimina el elemento identificado por la clave
	 * @param key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar, FALSE de lo contrario.
	 */
	virtual bool remove(const Register& key) = 0;

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param key clave del elemento a buscar
	 * @param reg refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	virtual bool find(const Register& key, Register &reg)const = 0;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param key clave del elemento a modificar
	 * @param reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	virtual bool modify(const Register& key, const Register &reg) = 0;

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
	virtual unsigned int getUsedSpace();


	/**
	 * Se encarga de averiguar si la cadena de bytes corresponde a una
	 * hoja o no.
	 * Para esto al serializar el nivel tiene que estar en una posicion fija
	 * para todas las clases hijas
	 * @param bytes la cadena de bytes a evaluar
	 * @return bool TRUE si es hoja, FALSE en caso contrario
	 */
	static bool isLeaf(const char* bytes);


	//-------------Serialize/Deserialize----------//
	/**
	 * Convierte el registro a una cadena de bytes.
	 * Convierte cada atributo mediante los metodos definidos en
	 * ByteConverter
	 * @param bytes cadena en la cual se serializan los atributos
	 * @return cadena resultante al serializar
	 * @see ByteConverter
	 */
	virtual char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * @param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	virtual void deserialize(const char* bytes);

	/**
	 * Setea los campos del registro con los mismos del objeto pasado por parametro
	 * @param registro Registro sobre el cual se hara la copia.
	 */
	virtual void setFields(const Register& registro);

	//---------------Get/Set--------------------------//
	/// Devuelve el nivel del nodo
	unsigned int getLevel();
	/// Modifica el nivel del nodo
	void setNivel(const unsigned int nivel);

	/// Devuelve el tamaño del nodo. No existe metodo para modificar el tamaño una vez construido.
	unsigned int getSize() const;

	/// Obtiene el identificador.
	unsigned int getNodeNumber()const;
	/// Modifica el identificador.
	void setNodeNumber(unsigned int number);

	/// Devuelve el factor de carga del nodo.
	unsigned int getBranchFactor() const;
	/// Modifica el factor de carga.
	void setBranchFactor(unsigned int branchFactor);

protected:
	/**
	 * Transforma a una cadena de bytes el nodo, teniendo en cuenta que los herederos de Node
	 * podrian tener datos de control adicionales, por eso es definida virtual pura dentro de esta clase.
	 * @param bytes La cadena de bytes en donde se almacena el resultado de la serializacion
	 * @return Puntero a la cadena de bytes.
	 */
	virtual char* serializeChilds(char* bytes) const = 0;
	/**
	 * Setea el valor del nodo a partir de la cadena de bytes, teniendo en cuenta que los herederos de
	 * Node podrian tener datos de control adicionales, por eso es definida virtual pura dentro de esta clase.
	 * Es llamada desde el metodo serialize.
	 * @param bytes La cadena de bytes en donde se almacena el resultado de la serializacion
	 * @return Puntero a la cadena de bytes.
	 */
	virtual void deserializeChilds(const char* bytes) = 0;

};

#endif /* NODE_H_ */
