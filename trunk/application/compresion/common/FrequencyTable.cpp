/*
 * FrequencyTable.cpp
 *
 *  Created on: 13/06/2010
 *      Author: celeste
 */

#include "FrequencyTable.h"

using namespace std;

FrequencyTable::FrequencyTable() {

}

FrequencyTable::~FrequencyTable() {
}

unsigned long FrequencyTable::getFrequencyTotal()
{
	return m_FrequencyTotal;
}



string FrequencyTable::toString()
{
	string retStr;
	return retStr;
}



void FrequencyTable::setFrequency(char c, unsigned long freq)
{
	CharFrequency cf(c, freq);
	setFrequency(cf);
}



void FrequencyTable::setFrequency(CharFrequency cf)
{
	m_Frequencies.push_back(cf);
}



unsigned long FrequencyTable::getFrequency(char c)
{
	char retChar;

	return retChar;
}



void FrequencyTable::deserialize(std::string serialized)
{
}



unsigned long FrequencyTable::getCumFrequency(char c)
{
	unsigned long retVal;

	return retVal;
}


