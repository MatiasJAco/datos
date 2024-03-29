/**
 * @file INodeData.cpp
 *
 *  @date: 23/04/2010
 *  @author: kira
 */

#include "INodeData.h"

const std::string INodeData::UNDEFINED_KEY= "@-1";


INodeData::INodeData() {

}

INodeData::INodeData( unsigned int leftPointer,std::string key)
{
	m_key = key;
	m_leftPointer = leftPointer;
}

INodeData::~INodeData() {
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
	char*p=stream;

	ByteConverter::stringToBytes(m_key,p);
	p+=m_key.size()+1;
	ByteConverter::uIntToBytes(m_leftPointer,p);

	return stream;
}

void INodeData::toNodeData(const char *stream)
{
	m_key = ByteConverter::bytesToString(stream);
	stream+=m_key.size()+1;
	m_leftPointer = ByteConverter::bytesToUInt(stream);
}

unsigned int INodeData::getSize() const
{
	return (m_key.size()+1 +sizeof(int));
}

bool    INodeData::operator ==(INodeData &p)
{
	return p.m_key == m_key;
}

bool    INodeData::operator <(INodeData &p)
{
	bool retVal=false;


	retVal = (strcmp(m_key.c_str(),p.m_key.c_str())<0) || (strcmp(p.m_key.c_str(),INodeData::UNDEFINED_KEY.c_str())==0);

	return retVal;
}

bool    INodeData::operator >(INodeData &p)
{
	bool retVal=false;

	retVal = ( (strcmp(p.m_key.c_str(),INodeData::UNDEFINED_KEY.c_str())!=0) && (((strcmp(m_key.c_str(),p.m_key.c_str()) > 0) ) || (strcmp(m_key.c_str(),INodeData::UNDEFINED_KEY.c_str()) == 0)));
	return retVal;
}





