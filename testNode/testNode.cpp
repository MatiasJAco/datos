/*
 * testNode.cpp
 *
 *  Created on: 03/04/2010
 *      Author: kira
 */

#include "../common/tree/LeafNode.cpp"
#include "../application/entities/StringRegister.h"

using namespace std;

int main(int argc, char *argv[])
{
	LeafNode *lf = new  LeafNode(0,512,50);

	if(lf->getUsedSpace()!=0)
		cout << "Error en GetUsedSpace 1"<<endl;

	StringRegister s(1,"Hola");
	lf->insert(s);

	if( lf->getUsedSpace()!=9)
		cout << "Error en GetUsedSpace 2"<<endl;

	cout << *lf;


	delete lf;
	return 0;
}
