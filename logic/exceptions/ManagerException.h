/**
 * @file ManagerException.h
 *
 *  @date: 01/05/2010
 *  @author: kira
 */
#include <iostream>
#include <typeinfo>

#ifndef MANAGEREXCEPTION_H_
#define MANAGEREXCEPTION_H_


class ManagerException: public std::exception  {

public:
	typedef enum
	{
		/* para BPlusTree */
		DUPLICATED = 0,
		INEXISTENT_ELEM,
		INNEXISTENT_ROOT,
		DELETED_FREENODE,
		CORRUPTED,

		/* para nodos */
		DUPLICATED_IN_INNER,
		DUPLICATED_IN_LEAF,
		INVALID_REF,
		INEXISTENT_ELEMINNER,
		INEXISTENT_ELEMLEAF,
		BAD_CALL_OPERATION,

		/* Comunes para Nodos y BPlusTree*/
		ANOMALOUS_LOADRESULT,
		INSUFFICIENT_ALLOCK_PARAM,
		UNDEFINED,

		/* para hash */
		DATA_ALREADY_EXISTS


	}ExceptionCause;

public:
	ManagerException(ExceptionCause cause): std::exception(){
		m_cause = cause;
	}

	ExceptionCause getCause() const
	{
		return m_cause;
	}

protected:
	ExceptionCause m_cause;
};

#endif /* MANAGEREXCEPTION_H_ */
