/**
 * @file main.cpp
 *
 *  @date: 26/04/2010
 *  @author: kira
 */



#include "../logic/input/StringInputData.h"
#include "../physical/utils/ByteConverter.h"

int main( int argc, char **argv)
{
	StringInputData *fixture = new StringInputData();

	std::string key = "3";
    string value = "algo";

	fixture->setKey(key);
	fixture->setValue(value);

	char* streamData = new char[fixture->size()];

	fixture->toStream(streamData);

	StringInputData data;
	data.toData(streamData);

	cout << "new key "<<data.getKey()<<endl;
	cout << "new data "<<data.getValue()<<endl;

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
