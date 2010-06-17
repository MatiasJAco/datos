/**
 * @file NodeException.h
 *
 *  @date: 01/05/2010
 *  @author: kira
 */
#include "ManagerException.h"

#ifndef NODEEXCEPTION_H_
#define NODEEXCEPTION_H_


class NodeException: public ManagerException  {

public:
	NodeException(ExceptionCause cause):ManagerException(cause){}

	ExceptionCause getCause() const
	{
		return m_cause;
	}

	const char* what() const throw()
		{
			switch(m_cause)
			{
			case DUPLICATED_IN_INNER:
				return "Se intento insertar un elemento duplicado ya existente en el nodo interno";
				break;
			case DUPLICATED_IN_LEAF:
				return "Se intento insertar un elemento duplicado ya existente en el nodo hoja";
			case INVALID_REF:
				return "Llego una clave a un nodo que no la referencia";
				break;
			case INEXISTENT_ELEMINNER:
				return "Elemento de nodo interno inexistente";
				break;
			case INEXISTENT_ELEMLEAF:
				return "Elemento de nodo hoja inexistente";
				break;
			case ANOMALOUS_LOADRESULT:
				return "Una operacion sobre el nodo devolvio un estado de carga inesperado";
				break;
			case INSUFFICIENT_ALLOCK_PARAM:
				return "Se intento almacenar en un nodo existente, un elemento que supera al tamaño disponible";
				break;
			case BAD_CALL_OPERATION:
				return "Llamada a una operacion de forma invalida";
				break;
			default:
				return "Error inesperado";
				break;
			}
			return "Error inesperado";
		}

};

#endif /* NODEEXCEPTION_H_ */
