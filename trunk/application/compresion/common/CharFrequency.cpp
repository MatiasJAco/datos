/*
 * CharFrequency.cpp
 *
 *  Created on: 13/06/2010
 *      Author: alex
 */

#include "CharFrequency.h"
#define LONG_SEPARATOR '/'
#define SHORT_SEPARATOR "--"

using namespace std;


CharFrequency::CharFrequency() {
	m_Char = '\0';
	m_Frequency =0;
}

CharFrequency::CharFrequency(short c, unsigned long freq)
{
	m_Char = c;
	m_Frequency =freq;
}

void CharFrequency::deserialize(string &serializedStr, unsigned int &pos)
{
	m_Char = StringToShort(serializedStr, pos);
	m_Frequency = StringToLong(serializedStr, pos);
	//const char *p=serializedStr.data();


}

string CharFrequency::toString()
{
	string retStr;

	retStr =  shortToString(m_Char) + longToString(m_Frequency);

	return retStr;
}

bool CharFrequency::operator < (const CharFrequency &cF) const
{
	return m_Char < cF.m_Char;
}

bool CharFrequency::operator == (short &c) const
{
	return m_Char == c;
}

CharFrequency::CharFrequency(const CharFrequency & cF)
{
	m_Char = cF.m_Char;
	m_Frequency = cF.m_Frequency;
}

unsigned int CharFrequency::getSize()
{
	return CHAR_FREQUENCY_SIZE;
}

unsigned long CharFrequency::getFrequency()
{
	return m_Frequency;
}


string CharFrequency::longToString(long val)
{
	stringstream ss;

	ss << val<<LONG_SEPARATOR ;

	return ss.str();
}

string CharFrequency::shortToString(short val)
{
	stringstream ss;

	ss << val<<SHORT_SEPARATOR;

	return ss.str();
}

long CharFrequency::StringToLong(string &str,unsigned int &pos)
{
	long retVal;
	string strPiece;
	unsigned int tempPos = str.find(LONG_SEPARATOR, pos);

	if (tempPos ==string::npos)
		throw "NO ES UN STRING VALIDO";

	strPiece = str.substr (pos,tempPos-pos);

	retVal = atol(strPiece.c_str());

	pos = tempPos+1;

	return retVal;
}

short CharFrequency::StringToShort(string &str,unsigned int &pos)
{
	short retVal;
	string strPiece;

	unsigned int tempPos = str.find(SHORT_SEPARATOR, pos);

	if (tempPos ==string::npos)
		throw "NO ES UN STRING VALIDO";

	strPiece = str.substr (pos,tempPos-pos);

	retVal = atoi(strPiece.c_str());

	pos = tempPos+2;

	return retVal;
}


CharFrequency::~CharFrequency() {
}
