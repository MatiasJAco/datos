/*
 * testFrequencyTable.cpp
 *
 *  Created on: 14/06/2010
 *      Author: alex
 */
#include "../application/compresion/common/FrequencyTable.h"
#include "../application/compresion/common/CharFrequency.h"
#include <iostream>

using namespace std;

void testFreqTable()
{
	FrequencyTable *ft;
	FrequencyTable *ft2;
	string serial, deserial;

	ft = new FrequencyTable();
	ft2 = new FrequencyTable();

	ft->setFrequency('a',2);
	ft->setFrequency('d',3);
	ft->setFrequency('c',4);
	ft->setFrequency('b',5);
	ft->setFrequency('/',5);
	ft->setFrequency('\\',5);
	ft->setFrequency(EOF_CHAR,5);
	ft->setFrequency(ESC_CHAR,5);

	ft->increaseFrequency('c',4);
	ft->increaseFrequency(ESC_CHAR,2);
	serial = ft->toString();

	cout << serial<<endl;

	ft2->deserialize(serial);
	ft2->increaseFrequency(ESC_CHAR,4);

	cout << ft2->toString()<<endl;


	cout<<"cum frec "<< ft->getCumFrequency('c')<<endl;
	cout<<"cum frec2 "<< ft->getCumFrequency('j')<<endl;
	cout<< "frec "<<ft->getFrequency('c')<<endl;
	cout<< "frec2 "<<ft->getFrequency('j')<<endl;
	cout <<"char"<< (char) 98<<endl;
	cout <<"esc char"<<ft2->getFrequency(ESC_CHAR)<<endl;
	cout <<"total1"<< ft->getFrequencyTotal()<<endl;
	cout <<"total2"<< ft2->getFrequencyTotal()<<endl;

	delete ft;
	delete ft2;

}

int main()
{
try
{
	testFreqTable();



}
catch (exception e)
{
	cout <<e.what()<<endl;
}






	return 0;
}
