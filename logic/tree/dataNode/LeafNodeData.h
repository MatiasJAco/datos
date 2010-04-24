/**
 * @file LeafNodeData.h
 *
 *  @date: 23/04/2010
 *  @author: kira
 */

#ifndef LEAFNODEDATA_H_
#define LEAFNODEDATA_H_

#include "../physical/utils/ByteConverter.h"
/**
 * Representacion de los datos base que almacena un nodo hoja; esto es: un puntero al nodo
 * derecho y un puntero al nodo izquierdo.
 * Utilizados estos dos datos para permitir acceso secuencial a los nodos.
 * Solo puede haber un unico objeto de este tipo en una hoja determinada.
 */

// TODO esta clase podria ser heredera de una abstracta, pero solo se hara en caso que sea
// necesario en la implementacion.
class LeafNodeData {
private:
	unsigned int m_leftPointer;
	unsigned int m_rightPointer;

public:
	/// Constructor.
	LeafNodeData();

	/// Constructor que recibe por parametro la referencia al nodo derecho y al nodo izquierdo.
	LeafNodeData(unsigned int leftPointer,unsigned int rightPointer);

	/// Destructor.
	virtual ~LeafNodeData();

	/**
	 * Devuelve la referencia izquierda de la hoja.
	 * @return Puntero referencia a un numero de nodo.
	 */
	unsigned int getLeftPointer();

    /// Set del puntero izquierdo de la hoja.
    void setLeftPointer(unsigned int leftPointer);

	/**
	 * Devuelve la referencia que apunta al nodo hoja derecho.
	 * @return Puntero referencia a un numero de nodo.
	 */
	unsigned int getRightPointer();

    /// Set del puntero derecho de la hoja.
    void setRightPointer(unsigned int leftPointer);

	/**
	 * Devuelve un stream correspondiente al LeafNodeData.
	 * @return stream que representa a LeafNodeData.
	 */
	char* toStream(char* stream);

	/**
	 * Recibe por parametro un stream y lo convierte a tipo LeafNodeData, haciendo el inverso toStream.
	 */
	void toNodeData(const char* stream);
};

#endif /* LEAFNODEDATA_H_ */
