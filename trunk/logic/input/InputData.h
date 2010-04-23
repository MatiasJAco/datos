/*
 * InputData.h
 *
 *  Created on: Apr 13, 2010
 *      Author: adrian
 */

#ifndef INPUTDATA_H_
#define INPUTDATA_H_

#include <iostream>
#include <sstream>

using namespace std;

/**
 * Abstract class which represents and holds a user Input value.
 */
class InputData {

protected:
	int key;
	stringstream value;

public:
	InputData();
	virtual ~InputData();

	virtual void setKey(int key) = 0;
	virtual void setValue(std::stringstream& value) = 0;
	virtual  int getKey()const = 0;
	virtual string getValue() = 0;
};

#endif /* INPUTDATA_H_ */
