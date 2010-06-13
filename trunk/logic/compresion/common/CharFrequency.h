/*
 * CharFrequency.h
 *
 *  Created on: 13/06/2010
 *      Author: celeste
 */

#ifndef CHARFREQUENCY_H_
#define CHARFREQUENCY_H_

class CharFrequency {
public:
	CharFrequency();
	CharFrequency(CharFrequency);
	CharFrequency(char, unsigned long);
	virtual ~CharFrequency();

	std::string toString();

private:

	char m_Char;
	unsigned long m_Frequency;
};

#endif /* CHARFREQUENCY_H_ */
