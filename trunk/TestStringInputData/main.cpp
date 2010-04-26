/**
 * @file main.cpp
 *
 *  @date: 26/04/2010
 *  @author: kira
 */



#include "../logic/input/StringInputData.h"

int main( int argc, char **argv)
{
	StringInputData *fixture = new StringInputData();

	int key = 3;
    string value = "paytiti";

	fixture->setKey(key);
	fixture->setValue(value);

	char* streamData = new char[fixture->size()];

	fixture->toStream(streamData);

	StringInputData data;
	data.toData(streamData);

	bool eqkey = key==data.getKey();
	bool eqvalue = value==data.getValue();

	if (!eqkey)
		cout << "fallo en key"<< endl;
	else
		cout << "ok en key" << endl;

	if (!eqvalue)
		cout << "fallo en value" << endl;
	else
		cout << "ok en value" << endl;

	return 0;
}
