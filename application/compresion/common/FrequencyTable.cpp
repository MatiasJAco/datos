/*
 * FrequencyTable.cpp
 *
 *  Created on: 13/06/2010
 *      Author: alex
 */

#include "FrequencyTable.h"

using namespace std;

FrequencyTable::FrequencyTable() {
	m_FrequencyTotal=0;
	m_isSorted= true;
}

FrequencyTable::~FrequencyTable() {
}

unsigned long FrequencyTable::getFrequencyTotal()
{
	return m_FrequencyTotal;
}

bool FrequencyTable::increaseFrequency(short c, unsigned long ammount=1)
{
	bool retVal= false;

	unsigned long freq = getFrequency(c);

	setFrequency(c,freq+ammount);

	return retVal;
}

string FrequencyTable::toString()
{
	stringstream retStr;

	CharFrequencyListIterator it;

	if(!m_isSorted)
	{
		m_Frequencies.sort();
		m_isSorted=true;
	}

	for(it=m_Frequencies.begin();it !=m_Frequencies.end(); it++)
	{
		retStr << it->toString();
	}

	return retStr.str();
}



void FrequencyTable::setFrequency(short c, unsigned long freq)
{
	CharFrequency cf(c, freq);
	setFrequency(cf);
}



void FrequencyTable::setFrequency(CharFrequency cf)
{
	CharFrequencyListIterator it;
	bool found=false;

	//Voy buscando el caracter si termino la tabla corto el ciclo
	for(it=m_Frequencies.begin();it !=m_Frequencies.end(); it++)
	{
		//Si lo encuentro corto el ciclo
		if((*it) == cf)
		{
			it-> setFrequency(cf.getFrequency());
			 found= true;
			break;
		}
	}
	if(!found)
	{
		m_Frequencies.push_back(cf);
		m_isSorted=false;
	}
}



unsigned long FrequencyTable::getFrequency(short c)
{
	unsigned long retVar=0;

	CharFrequencyListIterator it;

	if(!m_isSorted)
	{
		m_Frequencies.sort();
		m_isSorted=true;
	}

	//Voy buscando el caracter si termino la tabla corto el ciclo
	for(it=m_Frequencies.begin();it !=m_Frequencies.end(); it++)
	{
		//Si lo encuentro corto el ciclo
		if((*it) == c)
		{
			retVar = it->getFrequency();
			break;
		}
	}


	return retVar;
}



void FrequencyTable::deserialize(string serialized)
{
	//unsigned int pieceSize = CharFrequency::getSize();
	unsigned int serializedSize=serialized.size();
	m_FrequencyTotal=0;
	m_Frequencies.clear();
	unsigned int bytePos=0;

	if(serializedSize >0 )
	{
		while(bytePos < serializedSize)
		{
			CharFrequency cF;

			cF.deserialize(serialized,bytePos);

			m_FrequencyTotal+=cF.getFrequency();
			m_Frequencies.push_back(cF);

		}
	}


}



unsigned long FrequencyTable::getCumFrequency(short c)
{
	unsigned long retVar=0;
	bool found=false;

	CharFrequencyListIterator it;

	if(!m_isSorted)
	{
		m_Frequencies.sort();
		m_isSorted=true;
	}

	//Voy buscando el caracter si termino la tabla corto el ciclo
	for(it=m_Frequencies.begin();it !=m_Frequencies.end(); it++)
	{
		retVar += it->getFrequency();

		//Si lo encuentro corto el ciclo
		if((found =((*it) == c)))
		{
			break;
		}
	}

	if(!found)
		retVar=0;

	return retVar;
}

