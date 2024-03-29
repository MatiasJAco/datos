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
	FrequencyTable *ft3;
	FrequencyTable ft4;
	FrequencyTable ft5;
	string serial, deserial;

	ft = new FrequencyTable();
	ft2 = new FrequencyTable();
	ft3 = new FrequencyTable();

	ft->setFrequency('a',2);
	ft->setFrequency('d',3);
	ft->setFrequency('c',4);
	ft->setFrequency('b',5);
	ft->setFrequency('/',5);
	ft->setFrequency('\\',7);
	ft->setFrequency(258,1000);
	ft->setFrequency(EOF_CHAR,5);
	ft->setFrequency(ESC_CHAR,5);

	ft->increaseFrequency('c',4);
	ft->increaseFrequency(ESC_CHAR,2);

	ft3->setFrequency('b',2);
	ft3->setFrequency('\\',2);
	ft3->setFrequency('j',2);
	ft3->setFrequency(ESC_CHAR,5);

	serial = ft->toString();

	cout << serial<<endl;

	ft2->deserialize(serial);
	ft2->increaseFrequency(ESC_CHAR,4);

	cout << ft2->toString()<<endl;


	cout<<"cum frec "<< ft->getCumFrequency('c')-ft->getFrequency('c')<<endl;
	cout<<"cum frec2 "<< ft->getCumFrequency('j')<<endl;

	cout << "short1 "<< (char) ft->getChar(19)<< " "<< (short) 'c'<<endl;
	cout << ft->toString()<<endl;
	cout << "short2 "<< (char) ft->getChar(1)<< " "<< (char) 47<<endl;

	cout<< "frec "<<ft->getFrequency('c')<<endl;
	cout<< "frec2 "<<ft->getFrequency('j')<<endl;
	cout <<"char"<< (char) 98<<endl;
	cout <<"esc char"<<ft2->getFrequency(ESC_CHAR)<<endl;
	cout <<"total1"<< ft->getFrequencyTotal()<<endl;
	cout <<"total2"<< ft2->getFrequencyTotal()<<endl;

	//ft->excludeFromTable(*ft2);

	ft4 = ft->excludeFromTable(*ft3);

	cout << "ft4 " << ft4.toString()<<endl;

	cout << "ft4 frec"<< ft4.getFrequencyTotal()<<endl;

	cout << ft2->toPrintableString()<<endl;


	ft5.setFrequency('D',3);
	ft5.setFrequency('I',3);
	ft5.setFrequency('O',1);
	ft5.setFrequency('S',1);
	ft5.setFrequency('V',1);

	cout << "V "<< (char) ft5.getChar(8)<<endl;

	ft2->clearTable();
	cout << ft2->toPrintableString()<<endl;

	delete ft;
	delete ft2;
	delete ft3;
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
