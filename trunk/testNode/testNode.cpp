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

//	if(lf->getUsedSpace()!=0)
//		cout << "Error en GetUsedSpace 1"<<endl;

	StringRegister s(1,"Hola");
	StringRegister s2(2,"Mundo");
	StringRegister s3(3,"S");
	StringRegister s4(2,"af");
	StringRegister s5(5,"fadsfads");

	lf->insert(s);
	lf->insert(s2);
	lf->insert(s3);
	lf->insert(s4);
	lf->insert(s5);

//	if( lf->getUsedSpace()!=9)
//		cout << "Error en GetUsedSpace 2"<<endl;

	cout << *lf << endl;

	KeyInt k(3);
	lf->remove(k);

	cout << *lf<< endl;

	KeyInt k2(1);
	StringRegister sk;
	lf->find(k2,sk);

	cout << sk<< endl;

	KeyInt k3(2);
	StringRegister sm(6,"Celeste");
	lf->modify(k3,sm);

	cout << *lf<< endl;




	delete lf;
	return 0;
}
