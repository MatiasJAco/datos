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

public:
	HashException(ExceptionCause cause):ManagerException(cause){}

	ExceptionCause getCause() const
	{
		return m_cause;
	}

	const char* what() const throw()
		{
			switch(m_cause)
			{
			case DUPLICATED:
				return "Se intento insertar un elemento duplicado ya existente";
				break;
			case OPERATION_FAULT:
				return "La operación no pudo ser realizada con éxito.";
				break;
			case INEXISTENT_ELEM:
				return "No se encontro elemento que contenga dicha clave.";
				break;
			default:
				return "Error inesperado";
				break;
			}
			return "Error inesperado";
		}

};


#endif /* HASHEXCEPTION_H_ */
