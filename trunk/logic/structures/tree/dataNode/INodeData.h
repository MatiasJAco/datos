/**
 * @file INodeData.h
 *
 *  @date: 23/04/2010
 *  @author: kira
 */

#ifndef INODEDATA_H_
#define INODEDATA_H_

#include "../../../../physical/utils/ByteConverter.h"

/**
 * Representacion de los datos base primarios que almacena un nodo interno.
 * Esto es: una clave (el separador) y la referencia al nodo izquierdo al que apunta la clave.
 * Puede haber mas de uno de estos elementos dentro de un nodo interno.
 */
class INodeData {

private:
	std::string m_key;
	unsigned int m_leftPointer;

public:

	//TODO pablo - reemplace todos los lugares donde aparecia UNDEFINED_KEY como un string vacio ("")

	static const std::string UNDEFINED_KEY;



public:

	/// Constructor
	INodeData();

	/// Constructor con parametro clave y puntero izquierdo.
	INodeData( unsigned int leftPointer,std::string key);

	/// Destructor
	virtual ~INodeData();

	/**
	 * Devuelve la clave (separador) del nodo interno.
	 * @return Entero que representa a la clave.
	 */
	//TODO revisar si no deberia ser generico, por el momento, no.
	// Si fuera generico deberia hacerse ese cambio de implementacion sobre las claves, en todos los proyectos.
	std::string getKey()const;

	/**
	 * Devuelve la referencia izquierda de la clave.
	 * @return Puntero referencia a un numero de nodo.
	 */
	unsigned int getLeftPointer()const;

	/// Set de la clave (separador).
    void setKey(std::string key);

    /// Set del puntero izquierdo al separador.
    void setLeftPointer(unsigned int leftPointer);

	/**
	 * Devuelve un stream correspondiente al INodeData.
	 * @return stream que representa a INodeData.
	 */
	char* toStream(char* stream)const;

	/**
	 * Recibe por parametro un stream y lo convierte a tipo INodeData, haciendo el inverso toStream.
	 */
	void toNodeData(const char* stream);


	/**
	 * Tama�o del dato.
	 */
	unsigned int getSize()const;

	/**
	 *
	 */
	bool    operator ==(INodeData &p);
	/**
	 *
	 */
	bool    operator <(INodeData &p);

	/**
	 *
	 */
	bool    operator >(INodeData &p);



};

#endif /* INODEDATA_H_ */
