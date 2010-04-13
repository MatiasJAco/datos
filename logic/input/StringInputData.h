/*
 * StringInputData.h
 *
 *  Created on: Apr 13, 2010
 *      Author: adrian
 */

#ifndef STRINGINPUTDATA_H_
#define STRINGINPUTDATA_H_

#include "InputData.h"

class StringInputData: public InputData {

public:
	StringInputData();
	virtual ~StringInputData();

	void setValue(string value);
	string getValue();
	int getKey();
};

#endif /* STRINGINPUTDATA_H_ */
