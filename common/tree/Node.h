/**
 * @file Node.h
 * @author Alex - MCM
 */

#ifndef NODE_H_
#define NODE_H_

#include "../register/Register.h"
#include "../utils/ByteConverter.h"

#include <map>

class Node : public Register{

public:
	//---------------Constants------------//
	static const unsigned int LEAF_LEVEL = 0;
	static const unsigned int UNDEFINED_NODE_NUMBER = -1;

protected:

	//---------------Typedefs--------------//
	typedef std::map<Register*,Register*,RegisterComparator> RegisterMap;
	typedef RegisterMap::iterator RegisterMapIterator;
	typedef std::pair<Register*,Register*> RegisterMapPair;

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
	 * RegisterMap m_registers: Los registros en si
	 */
	RegisterMap m_registers;

	/**
	 * unsigned int m_Id El Id del nodo (se obtiene con el offset del nodo en disco)
	 * Este dato no se persiste en disco.
	 */
	unsigned int m_nodeNumber;

	/**
	 * unsigned int m_BranchFactor porcentaje de utilizacion minima del nodo
	 */
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


	virtual ~Node();

	//-------------Metodos basicos------------------------//

	/**
	 * Inserta un Register en el nodo, puede superar la capacidad del nodo
	 * por lo cual luego de una insercion hay que llamar al metodo overflow()
	 * para no rebalsar el espacio en disco del nodo
	 * @param const Register& reg registro a insertar
	 * @return TRUE si se pudo insertar. En caso de clave duplicada devuelve FALSE
	 */
	virtual bool insert(const Register& reg) = 0;

	/**
	 * Elimina el elemento identificado por la clave
	 * @param const Key& key clave del elemento a eliminar
	 * @return bool TRUE si se pudo eliminar
	 */
	virtual bool remove(const Register& key) = 0;

	/**
	 * Busca el elemento identificado por la clave
	 * Si lo encuentra guarda el registro en reg
	 * @param const Key& key clave del elemento a buscar
	 * @param Register &reg refencia en la cual se va a almacenar el registro encontrado
	 * @return bool TRUE en caso de encontrar el registro, FALSE en el caso que no se encuentre.
	 */
	virtual bool find(const Register& key, Register &reg)const = 0;

	/**
	 * Modifica el nodo identificado por la clave
	 * Si lo encuentra escribe el contenido de reg en el registro
	 * @param const Key& key clave del elemento a modificar
	 * @param Register &reg valor que se colocara en el registro
	 * @return bool TRUE si modifico el elemento FALSE en caso que no se encontrara.
	 */
	virtual bool modify(const Register& key, const Register &reg) = 0;



	/**
	 * Evalua si el nodo esta vacio
	 * @return bool TRUE si esta vacio FALSE en caso contrario
	 */
	bool isEmpty();

	/**
	 * Evalua si se supero la capacidad del nodo en una insercion previa
	 * Sirve para evaluar cuando hay q//	const Register* key  = registro.getRegisterKey());ue partir el nodo.
	 * @return bool TRUE si se supero la capacidad anteriormente FALSE en caso contrario
	 */
	bool overflow();

	/**
	 * Evalua si la capacidad del nodo esta por debajo del factor de llenado.
	 * Sirve para evaluar cuando hacer un merge de los nodos
	 * @return bool TRUE si se produjo underflow FALSE en caso contrario
	 */
	bool underflow();

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
	 * @param const char* bytes la cadena de bytes a evaluar
	 * @return bool TRUE si es hoja, FALSE en caso contrario
	 */
	static bool isLeaf(const char* bytes);


	//-------------Serialize/Deserialize----------//
	/**
	 * Serializa el registro en bytes
	 * \param bytes Cadena de bytes en la que almacena el contenido del registro
	 * \return El puntero a la cadena de bytes
	 */
	virtual char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	virtual void deserialize(const char* bytes);

	virtual void setFields(const Register& registro);

	//---------------Get/Set--------------------------//
	unsigned int getLevel();
	void setNivel(const unsigned int nivel);

	unsigned int getSize() const;

	unsigned int getNodeNumber()const;
	void setNodeNumber(unsigned int number);

	unsigned int getBranchFactor() const;
	void setBranchFactor(unsigned int branchFactor);

protected:
	// TODO cambiar el nombre
	/**
	 * Transforma a una cadena de bytes el nodo, teniendo en cuenta que los herederos de @class Node
	 * podrian tener datos de control adicionales, por eso es definida virtual pura dentro de esta clase.
	 * @param bytes La cadena de bytes en donde se almacena el resultado de la serializacion
	 * @return Puntero a la cadena de bytes.
	 */
	virtual char* serializeChilds(char* bytes) const = 0;
	/**
	 * Setea el valor del nodo a partir de la cadena de bytes, teniendo en cuenta que los herederos de
	 * @class Node podrian tener datos de control adicionales, por eso es definida virtual pura dentro de esta clase.
	 * Es llamada desde el metodo serialize.
	 * @param bytes La cadena de bytes en donde se almacena el resultado de la serializacion
	 * @return Puntero a la cadena de bytes.
	 */
	virtual void deserializeChilds(const char* bytes) = 0;

};

#endif /* NODE_H_ */
