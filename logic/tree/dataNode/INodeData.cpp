/**
 * @file INodeData.cpp
 *
 *  @date: 23/04/2010
 *  @author: kira
 */

#include "INodeData.h"

INodeData::INodeData() {
	// TODO Auto-generated constructor stub

}

INodeData::INodeData( unsigned int leftPointer,unsigned long int key)
{
	m_key = key;
	m_leftPointer = leftPointer;
}

INodeData::~INodeData() {
	// TODO Auto-generated destructor stub
}

unsigned long int INodeData::getKey()const
{
	return m_key;
}

void INodeData::setKey(unsigned long int key)
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
	ByteConverter::uLongIntToBytes(m_key,stream);
	stream+=sizeof(m_key);
	ByteConverter::uIntToBytes(m_leftPointer,stream);

	return stream;
}

void INodeData::toNodeData(const char *stream)
{
	m_key = ByteConverter::bytesToULongInt(stream);
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
	return retVal;
}

bool    INodeData::operator >(INodeData &p)
{
	bool retVal=false;

	retVal = (p.m_key!= UNDEFINED_KEY)&&(m_key > p.m_key || m_key==UNDEFINED_KEY);
	return retVal;
}





