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
	// TODO Auto-generated destructor stub
}


void StringInputData::setValue(string value) {
	this->value = value;
}

string StringInputData::getValue() {
	return this->value;
}

int StringInputData::getKey() {
	int length = this->getValue().length();
	const char* temp = this->getValue().c_str();
	int i = 0;

	for (int j = 0; j < length; j++) {
		i += static_cast<int>(temp[j]);
		cout << "La suma actual es: " << i << endl;
	}
	return i;
}
