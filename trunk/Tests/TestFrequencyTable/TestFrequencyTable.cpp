/*
 * TestFrequencyTable.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: Alex
 */

#include "TestFrequencyTable.h"
#include "../application/compresion/common/FrequencyTable.h"
#include "../application/compresion/common/CharFrequency.h"
#include <iostream>

using namespace std;


TestFrequencyTable::TestFrequencyTable() {
}

TestFrequencyTable::~TestFrequencyTable() {
}

void TestFrequencyTable::testFreqTable() {
	FrequencyTable *ft;
	FrequencyTable *ft2;
	FrequencyTable *ft3;
	FrequencyTable ft4;
	FrequencyTable ft5;
	FrequencyTable ft6;
	std::string serial, deserial;

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

	std::cout << serial<<std::endl;

	ft2->deserialize(serial);
	ft2->increaseFrequency(ESC_CHAR,4);

	std::cout << ft2->toString()<<std::endl;


	std::cout<<"cum frec "<< ft->getCumFrequency('c')<<std::endl;
	std::cout<<"cum frec2 "<< ft->getCumFrequency('j')<<std::endl;
	std::cout<< "frec "<<ft->getFrequency('c')<<std::endl;
	std::cout<< "frec2 "<<ft->getFrequency('j')<<std::endl;
	std::cout <<"char"<< (char) 98<<std::endl;
	std::cout <<"esc char"<<ft2->getFrequency(ESC_CHAR)<<std::endl;
	std::cout <<"total1"<< ft->getFrequencyTotal()<<std::endl;
	std::cout <<"total2"<< ft2->getFrequencyTotal()<<std::endl;

	//ft->excludeFromTable(*ft2);

	ft4 = ft->excludeFromTable(*ft3);

	std::cout << "ft4 " << ft4.toString()<<std::endl;
	ft5.setFrequency('D',3);
	ft5.setFrequency('I',3);
	ft5.setFrequency('O',1);
	ft5.setFrequency('S',1);
	ft5.setFrequency('V',1);

	cout << "V "<< (char) ft5.getChar(8)<<endl;

	ft2->clearTable();
	cout << ft2->toPrintableString()<<endl;
	cout << ft2->getCharCount()<<endl;

	cout << ft4.toPrintableString()<<endl;
	cout << ft4.getCharCount()<<endl;

	ft6.setFrequency('a',2);
	ft6.setFrequency(ESC_CHAR,2);
	cout << ft6.getCharCount()<<endl;

	delete ft;
	delete ft2;
	delete ft3;
}
