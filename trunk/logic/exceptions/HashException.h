/*
 * HashException.h
 *
 *  Created on: Jun 16, 2010
 *      Author: pablolisio
 */
#include "ManagerException.h"

#ifndef HASHEXCEPTION_H_
#define HASHEXCEPTION_H_

class HashException: public ManagerException  {

//public:
//	typedef enum
//	{
//		DUPLICATED_IN_INNER,
//		DUPLICATED_IN_LEAF,
//		INVALID_REF,
//		INEXISTENT_ELEMINNER,
//		INEXISTENT_ELEMLEAF,
//		ANOMALOUS_LOADRESULT,
//		INSUFFICIENT_ALLOCK_PARAM,
//		BAD_CALL_OPERATION,
//		UNDEFINED
//	}ExceptionCause;

public:
	HashException(ExceptionCause cause):ManagerException(cause){
		//m_cause = cause;
	}

	ExceptionCause getCause() const
	{
		return m_cause;
	}

	const char* what() const throw()
		{
			switch(m_cause)
			{
			case DATA_ALREADY_EXISTS:
				return "Se intento insertar un elemento duplicado ya existente";
				break;


			default:
				return "Error inesperado";
				break;
			}
			return "Error inesperado";
		}
//
//private:
//	ExceptionCause m_cause;
};


#endif /* HASHEXCEPTION_H_ */
