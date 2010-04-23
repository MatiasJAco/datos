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

	void setKey(int key);
	void setValue(std::stringstream& value);
	 int getKey()const;
	string getValue();
};

#endif /* STRINGINPUTDATA_H_ */
