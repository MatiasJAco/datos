/*
 * FrequencyTable.h
 *
 *  Created on: 13/06/2010
 *      Author: celeste
 */

#ifndef FREQUENCYTABLE_H_
#define FREQUENCYTABLE_H_
#include <list>
#include "CharFrequency.h"

class FrequencyTable {
typedef list <CharFrequency>CharFrequencyList;
typedef CharFrequencyList::iterator CharFrequencyListIterator;


public:
	FrequencyTable();

	virtual ~FrequencyTable();

	unsigned long getFrequency(char c);

	unsigned long getFrequencySum();

	void setFrequency(char c, unsigned long);

	void setFrequency(CharFrequency cf);

	void deserialize(std::string serialized);

	std::string toString();

private:
	CharFrequencyList m_Frequencies;

	unsigned long m_FrequencySum;
};

#endif /* FREQUENCYTABLE_H_ */
