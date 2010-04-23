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
