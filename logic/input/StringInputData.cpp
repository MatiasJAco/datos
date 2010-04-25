/*
 * StringInputData.cpp
 *
 *  Created on: Apr 13, 2010
 *      Author: adrian
 */

#include "StringInputData.h"
#include <iostream>

StringInputData::StringInputData() {
}

StringInputData::~StringInputData() {
}

void StringInputData::setKey(int key) {
	this->key = key;
}

void StringInputData::setValue(std::stringstream& value) {
	this->value << value.str();
}

int StringInputData::getKey()const {
	return this->key;
}

string StringInputData::getValue() {
	return this->value.str();
}

char* StringInputData::toStream(char* stream) const
{
	ByteConverter::intToBytes(key,stream);
	stream += sizeof(key);
	ByteConverter::stringToBytes(value.str(),stream);

	return stream;
}

void StringInputData::toData(const char* stream)
{
	key = ByteConverter::bytesToInt(stream);
	stream += sizeof(key);
	value << ByteConverter::bytesToString(stream);
}

unsigned int StringInputData::size()
{
	return (sizeof(key)+value.str().size());
}

InputData* StringInputData::newInstance()
{
	return new StringInputData();
}
