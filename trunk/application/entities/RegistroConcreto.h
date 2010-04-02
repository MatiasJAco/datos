/*
 * RegistroConcreto.h
 *
 *  Created on: 27/03/2010
 *      Author: kira
 */

#ifndef REGISTROCONCRETO_H_
#define REGISTROCONCRETO_H_

#include "../../common/register/Register.h"
#include "../../common/utils/ByteConverter.h"
#include <iostream>
#include <sstream>

class RegistroConcreto: public Register {

private:
	int m_clave;
	double m_double;
	float m_float;
	std::string m_string;

public:
	RegistroConcreto(){};

	RegistroConcreto(const RegistroConcreto& reg);

	RegistroConcreto(int clave,double tdouble,float tfloat,std::string tstring);
	virtual ~RegistroConcreto();

	unsigned int getSize() const;

	char* serialize(char* bytes) const;

	/**
	 * Transfo0rma la cadena de bytes a un registro
	 * \param bytes Cadena de bytes de la cual lee para setear los campos del registro.
	 */
	void deserialize(const char* bytes);

	std::string toString() const;


	bool operator==(const Register& registro) const	;

	virtual bool operator<(const Register& registro) const;

	virtual bool operator>(const Register& registro) const;

    int getClave() const
    {
        return m_clave;
    }

    double getDouble() const
    {
        return m_double;
    }

    float getFloat() const
    {
        return m_float;
    }

    std::string getString() const
    {
        return m_string;
    }

    void setClave(int m_clave)
    {
        this->m_clave = m_clave;
    }

    void setDouble(double m_double)
    {
        this->m_double = m_double;
    }

    void setFloat(float m_float)
    {
        this->m_float = m_float;
    }

    void setString(std::string m_string)
    {
        this->m_string = m_string;
    }

};

//istream& operator>> (istream& is, string& str);
//
//ostream& operator<< (ostream& os, const string& str);


#endif /* REGISTROCONCRETO_H_ */
