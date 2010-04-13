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
	string value;

public:
	InputData();
	virtual ~InputData();

	virtual void setValue(string value) = 0;
	virtual string getValue() = 0;
	virtual int getKey() = 0;
};

#endif /* INPUTDATA_H_ */
