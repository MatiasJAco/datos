/**
 * @file INodeData.cpp
 *
 *  @date: 23/04/2010
 *  @author: kira
 */

#include "INodeData.h"

const std::string INodeData::UNDEFINED_KEY= "@-1";


INodeData::INodeData() {
	// TODO Auto-generated constructor stub

}

INodeData::INodeData( unsigned int leftPointer,std::string key)
{
	m_key = key;
	m_leftPointer = leftPointer;
}

INodeData::~INodeData() {
	// TODO Auto-generated destructor stub
}

std::string INodeData::getKey()const
{
	return m_key;
}

void INodeData::setKey(std::string key)
{
	m_key = key;
}

void INodeData::setLeftPointer(unsigned int leftPointer)
{
	m_leftPointer = leftPointer;
}


unsigned int INodeData::getLeftPointer()const
{
	return m_leftPointer;
}


char *INodeData::toStream(char* stream)const
{
	ByteConverter::stringToBytes(m_key,stream);
	stream+=sizeof(m_key);
	ByteConverter::uIntToBytes(m_leftPointer,stream);

	return stream;
}

void INodeData::toNodeData(const char *stream)
{
	m_key = ByteConverter::bytesToString(stream);
	stream+=sizeof(m_key);
	m_leftPointer = ByteConverter::bytesToUInt(stream);
}

unsigned int INodeData::getSize() const
{
	return (sizeof(int)*2);
}

bool    INodeData::operator ==(INodeData &p)
{
	return p.m_key == m_key;
}

bool    INodeData::operator <(INodeData &p)
{
	bool retVal=false;

	retVal = m_key < p.m_key || p.m_key==UNDEFINED_KEY;
	std::string stringVacio = "";
	retVal = (strcmp(m_key.c_str(),p.m_key.c_str())<0) || (strcmp(p.m_key.c_str(),stringVacio.c_str())==0);

	return retVal;
}

bool    INodeData::operator >(INodeData &p)
{
	bool retVal=false;

	retVal = (p.m_key!= UNDEFINED_KEY)&&(m_key > p.m_key || m_key==UNDEFINED_KEY);
	std::string stringVacio = "";
	retVal = ( (strcmp(p.m_key.c_str(),stringVacio.c_str())!=0) && ((strcmp(m_key.c_str(),p.m_key.c_str()) > 0) ) || (strcmp(m_key.c_str(),stringVacio.c_str()) == 0));
	return retVal;
}





