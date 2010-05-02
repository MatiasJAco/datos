/**
 * @file BPlusTreeException.h
 *
 *  @date: 01/05/2010
 *  @author: kira
 */
#include <iostream>
#include <typeinfo>

#include "NodeException.h"

#ifndef BPLUSTREEEXCEPTION_H_
#define BPLUSTREEEXCEPTION_H_

class BPlusTreeException: public std::exception {

public:
	typedef enum
	{
		DUPLICATED = 0,
		INEXISTENT_ELEM,
		ANOMALOUS_LOADRESULT,
		INNEXISTENT_ROOT,
		DELETED_FREENODE,
		INSUFFICIENT_ALLOCK_PARAM,
		CORRUPTED,
		UNDEFINED
	}ExceptionCause;

public:
	BPlusTreeException(){}

	BPlusTreeException(ExceptionCause cause): std::exception(){
		m_cause = cause;
	}

	BPlusTreeException(NodeException& e): std::exception(){

		switch(e.getCause())
		{
		case NodeException::DUPLICATED_IN_LEAF:
			m_cause = DUPLICATED;
			break;
		case NodeException::INVALID_REF:
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

private:
	ExceptionCause m_cause;
};

#endif /* BPLUSTREEEXCEPTION_H_ */
