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

FrequencyTable::FrequencyTable(const FrequencyTable &ft )
{
	m_Frequencies =ft.m_Frequencies;
	m_isSorted=true;
	m_FrequencyTotal =ft.m_FrequencyTotal;
	m_Frequencies.sort();
}

FrequencyTable::~FrequencyTable() {
}

unsigned long FrequencyTable::getFrequencyTotal()
{
	return m_FrequencyTotal;
}

void FrequencyTable::increaseFrequency(short c, unsigned long ammount=1)
{
	unsigned long freq = getFrequency(c);

	setFrequency(c,freq+ammount);

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
			m_FrequencyTotal -= it->getFrequency();
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
	m_FrequencyTotal += cf.getFrequency();

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

FrequencyTable FrequencyTable::excludeFromTable(FrequencyTable &ft)
{
	CharFrequencyListIterator it;
	CharFrequencyListIterator itDel;

	FrequencyTable retFt(*this);

	if(!ft.m_isSorted)
	{
		ft.m_Frequencies.sort();
		ft.m_isSorted=true;
	}

	itDel = ft.m_Frequencies.begin();

	//Voy buscando el caracter si termino la tabla corto el ciclo
	for(it=retFt.m_Frequencies.begin();it !=retFt.m_Frequencies.end(); it++)
	{
		while(((*itDel) < (*it)||(*itDel)==ESC_CHAR)&&itDel!=ft.m_Frequencies.end())
			itDel++;

		if( (*itDel) == (*it))
		{
			m_FrequencyTotal = it->getFrequency();
			it = retFt.m_Frequencies.erase(it);
			itDel++;

			if((*itDel)==ESC_CHAR)
				itDel++;
		}

		if(itDel==ft.m_Frequencies.end())
			break;
	}
	return retFt;
}

FrequencyTable FrequencyTable::operator= (FrequencyTable ft)
{
	if(!ft.m_isSorted)
	{
		ft.m_Frequencies.sort();
		ft.m_isSorted=true;
	}

	m_Frequencies =ft.m_Frequencies;
	m_isSorted=true;
	m_FrequencyTotal =ft.m_FrequencyTotal;

	return *this;
}

void FrequencyTable::deserialize(string serialized)
{
	if(!m_Frequencies.empty())
		m_Frequencies.clear();

	unsigned int serializedSize=serialized.size();
	m_FrequencyTotal=0;
	m_Frequencies.clear();
	unsigned int bytePos=0;

	CharFrequency cF;

	if(serializedSize >0 )
	{
		while(bytePos < serializedSize)
		{
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
