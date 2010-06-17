/**
 * @file BPlusTreeException.h
 *
 *  @date: 01/05/2010
 *  @author: kira
 */
#include "NodeException.h"
#include "ManagerException.h"

#ifndef BPLUSTREEEXCEPTION_H_
#define BPLUSTREEEXCEPTION_H_

class BPlusTreeException: public ManagerException {

public:
	BPlusTreeException(ExceptionCause cause): ManagerException(cause){}

	BPlusTreeException(NodeException& e): ManagerException(m_cause){

		switch(e.getCause())
		{
		case NodeException::DUPLICATED_IN_LEAF:
			m_cause = DUPLICATED;
			break;
		case NodeException::INVALID_REF:
			m_cause = CORRUPTED;
			break;
		case NodeException::INEXISTENT_ELEMINNER:
		case NodeException::INEXISTENT_ELEMLEAF:
			m_cause = INEXISTENT_ELEM;
			break;
		case NodeException::INSUFFICIENT_ALLOCK_PARAM:
			m_cause = CORRUPTED;
			break;
		default:
			m_cause = UNDEFINED;
			break;
		}
	}

	ExceptionCause getCause() const
	{
		return m_cause;
	}

	const char* what() const throw()
		{
			switch(m_cause)
			{
			case DUPLICATED:
				return "Se intento insertar un elemento duplicado ya existente en el arbol";
				break;
			case INEXISTENT_ELEM:
				return "No se encuentra el elemento";
				break;
			case ANOMALOUS_LOADRESULT:
				break;
			case DELETED_FREENODE:
				return "Se intento borrar un elemento ya eliminado";
				break;
			case CORRUPTED:
				return "El arbol se encuentra corrupto";
				break;
			default:
				return "Error inesperado";
				break;
			}
			return "Error inesperado";
		}
};

#endif /* BPLUSTREEEXCEPTION_H_ */
