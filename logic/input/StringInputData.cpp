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

StringInputData::StringInputData(std::string key,std::string value)
{
	this->key = key;
	this->value = value;
}

StringInputData::~StringInputData() {
}

void StringInputData::setKey(std::string key) {
	this->key = key;
}

void StringInputData::setValue(std::string value) {
	this->value = value;
}

std::string StringInputData::getKey()const {
	return this->key;
}

string StringInputData::getValue()const {
	return this->value;
}

char* StringInputData::toStream(char* stream) const
{
	char *p=stream;
	ByteConverter::stringToBytes(key,p);
	p += sizeof(key);
	ByteConverter::stringToBytes(value,p);

	return stream;
}

void StringInputData::toData(const char* stream)
{
	char *p=(char *)stream;
	key = ByteConverter::bytesToString(p);
	p += sizeof(key);
	value = ByteConverter::bytesToString(p);
}

unsigned int StringInputData::size()const
{
	return (sizeof(key)+value.size()+1);
}

InputData* StringInputData::newInstance()const
{
	return new StringInputData();
}

std::string StringInputData::toString()const
{
	std::string str;

	str+= "Clave: " + key;
	str+= ", Data: " + value;
	str+= "\n";

	return str;
}
