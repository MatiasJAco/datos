/**
 * @file LeafNodeData.cpp
 *
 *  @date: 23/04/2010
 *  @author: kira
 */

#include "LeafNodeData.h"

LeafNodeData::LeafNodeData() {
	// TODO Auto-generated constructor stub

}

LeafNodeData::LeafNodeData(unsigned int leftPointer, unsigned int rightPointer)
{
	m_leftPointer = leftPointer;
	m_rightPointer = rightPointer;
}

LeafNodeData::~LeafNodeData() {
	// TODO Auto-generated destructor stub
}

unsigned int LeafNodeData::getRightPointer()
{
	return m_rightPointer;
}


void LeafNodeData::setRightPointer(unsigned int leftPointer)
{
	m_rightPointer = leftPointer;
}


void LeafNodeData::setLeftPointer(unsigned int leftPointer)
{
	m_leftPointer = leftPointer;
}

unsigned int LeafNodeData::getLeftPointer()
{
	return m_leftPointer;
}

char *LeafNodeData::toStream(char *stream)
{
	ByteConverter::intToBytes(m_rightPointer,stream);
	stream+=sizeof(m_rightPointer);
	ByteConverter::uIntToBytes(m_leftPointer,stream);

	return stream;
}

void LeafNodeData::toNodeData(const char *stream)
{

	m_rightPointer = ByteConverter::bytesToInt(stream);
	stream+=sizeof(m_rightPointer);
	m_leftPointer = ByteConverter::bytesToUInt(stream);
}


