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
	StringInputData(int key,std::string value);

	virtual ~StringInputData();

	void setKey(int key);
	void setValue(std::string value);
	int getKey()const;
	string getValue();


	char* toStream(char* stream) const;
	void toData(const char* stream);

	unsigned int size() const;

	InputData* newInstance() const;
};

#endif /* STRINGINPUTDATA_H_ */
