/**
 * @file CompressionException.h
 *
 *  @date: 30/06/2010
 *  @author: kira
 */

#ifndef COMPRESSIONEXCEPTION_H_
#define COMPRESSIONEXCEPTION_H_

#include <iostream>
#include <typeinfo>

class CompressionException: public std::exception  {

public:
	typedef enum
	{
		BITS_NOT_ENOUGH,
		INVALID_CHAR
	}CompressionExceptionCause;

public:
	CompressionException(CompressionExceptionCause cause): std::exception(){
		m_cause = cause;
	}

	CompressionExceptionCause getCause() const
	{
		return m_cause;
	}

	const char* what() const throw()
		{
		std::string retVal;
			switch(m_cause)
			{
			case BITS_NOT_ENOUGH:
				retVal = "Cantidad de bits insuficiente. Piso y techo iguales!!";
				break;
			case INVALID_CHAR:
				retVal = "Cantidad de bits insuficiente. Piso y techo iguales!!";
				break;
			default:
				retVal = "Error inesperado";
				break;
			}

		return retVal.c_str();
		}

private:
	CompressionExceptionCause m_cause;
};

#endif /* COMPRESSIONEXCEPTION_H_ */
