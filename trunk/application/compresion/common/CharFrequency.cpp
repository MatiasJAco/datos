/*
 * CharFrequency.cpp
 *
 *  Created on: 13/06/2010
 *      Author: celeste
 */

#include "CharFrequency.h"
using namespace std;

CharFrequency::CharFrequency() {
	m_Char = '\0';
	m_Frequency =0;
}

CharFrequency::CharFrequency(char c, unsigned long freq)
{
	m_Char = c;
	m_Frequency =freq;
}



string CharFrequency::toString()
{
	stringstream retStr;

	retStr << m_Char << m_Frequency;
	return retStr.str();
}

CharFrequency::CharFrequency(const CharFrequency & charFrequency)
{
}

CharFrequency::~CharFrequency() {
}
