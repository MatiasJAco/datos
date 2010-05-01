/**
 * @file BPlusTreeException.h
 *
 *  @date: 01/05/2010
 *  @author: kira
 */
#include <iostream>
#include <typeinfo>

#ifndef BPLUSTREEEXCEPTION_H_
#define BPLUSTREEEXCEPTION_H_

class BPlusTreeException: public std::exception {

public:
	typedef enum
	{
		DUPLICATED = 0,
		INVALID_REF,
		INEXISTENT_ELEM,
		ANOMALOUS_LOADRESULT,
		INNEXISTENT_ROOT,
		DELETED_FREENODE,
		INSUFFICIENT_ALLOCK_PARAM

	}ExceptionCause;

public:
	BPlusTreeException(ExceptionCause cause): std::exception(){
		m_cause = cause;
	}

	const char* what() const throw()
		{
			switch(m_cause)
			{
			case DUPLICATED:
				return "Se intento insertar un elemento duplicado ya existente en el arbol";
				break;
			case INVALID_REF:
				return "Error: llego clave a una referencia invalida";
				break;
			case INEXISTENT_ELEM:
				break;
			case ANOMALOUS_LOADRESULT:
				break;
			case DELETED_FREENODE:
				break;
			case INSUFFICIENT_ALLOCK_PARAM:
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
