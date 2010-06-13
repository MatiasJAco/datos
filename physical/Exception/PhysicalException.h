/*
 * PhysicalException.h
 *
 *  Created on: 12/06/2010
 *      Author: alex
 */

#ifndef PHYSICALEXCEPTION_H_
#define PHYSICALEXCEPTION_H_

#include <iostream>
#include <typeinfo>

class PhysicalException: public std::exception  {

public:
	typedef enum
	{
		NULL_POINTER,
		BUFFER_SIZE_EXCEDED,
		ERROR_OPENING_FILE,
		INVALID_FILE_OPERATION,
		UNDEFINED
	}PhysicalExceptionCause;

public:
	PhysicalException(PhysicalExceptionCause cause): std::exception(){
		m_cause = cause;
	}

	PhysicalExceptionCause getCause() const
	{
		return m_cause;
	}

	const char* what() const throw()
		{
		std::string retVal;
			switch(m_cause)
			{
			case INVALID_FILE_OPERATION:
				retVal = "La operacion no es valida sobre el archivo";
				break;
			case NULL_POINTER:
				retVal = "Se paso un puntero a null";
				break;
			case BUFFER_SIZE_EXCEDED:
				retVal = "Se excedio el tamano del buffer";
				break;
			case ERROR_OPENING_FILE:
				retVal = "Error al abrir el archivo";
				break;
			default:
				retVal = "Error inesperado";
				break;
			}

		return retVal.c_str();
		}

private:
	PhysicalExceptionCause m_cause;
};

#endif /* PHYSICALEXCEPTION_H_ */
