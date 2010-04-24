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

INodeData::INodeData(int key, unsigned int leftPointer)
{
	m_key = key;
	m_leftPointer = leftPointer;
}

INodeData::~INodeData() {
	// TODO Auto-generated destructor stub
}

int INodeData::getKey()
{
	return m_key;
}

void INodeData::setKey(int key)
{
	m_key = key;
}

void INodeData::setLeftPointer(unsigned int leftPointer)
{
	m_leftPointer = leftPointer;
}


unsigned int INodeData::getLeftPointer()
{
	return m_leftPointer;
}


char *INodeData::toStream(char* stream)
{
	ByteConverter::intToBytes(m_key,stream);
	stream+=sizeof(m_key);
	ByteConverter::uIntToBytes(m_leftPointer,stream);

	return stream;
}

void INodeData::toNodeData(const char *stream)
{
	m_key = ByteConverter::bytesToInt(stream);
	stream+=sizeof(m_key);
	m_leftPointer = ByteConverter::bytesToUInt(stream);
}







