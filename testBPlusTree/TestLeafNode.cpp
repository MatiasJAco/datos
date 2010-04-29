/**
 * @file TestLeafNode.cpp
 *
 *  @date: 26/04/2010
 *  @author: kira
 */

#include "TestLeafNode.h"

TestLeafNode::TestLeafNode() {
	// TODO Auto-generated constructor stub
	mainFixture = new BPlusTree("arbol.dat",128,0.5);

}

TestLeafNode::~TestLeafNode() {
	// TODO Auto-generated destructor stub
	if (mainFixture!=NULL)
		delete mainFixture;
}



void TestLeafNode::run()
{
	testRecoverLeaf();
}

void TestLeafNode::testRecoverLeaf()
{
	LeafNode* leaf = (LeafNode*)mainFixture->newLeafNode();
	StringInputData data;

	data.setKey(40);
	data.setValue("hola");

//	leaf->insert(data);
	mainFixture->saveNode(leaf);

	unsigned int nodeNumber = leaf->getNodeNumber();

	LeafNode* leafRecovered = (LeafNode*)mainFixture->getNode(nodeNumber);

	if (leafRecovered->getLevel()==leaf->getLevel())
		cout << "OK. EN OBTENER NIVEL"<< endl;
	else
		cout << "FAILED!. EN OBTENER NIVEL"<< endl;

	if (leafRecovered->getNodeNumber()==leaf->getNodeNumber())
		cout << "OK. EN OBTENER NUMERO DE NODO"<< endl;
	else
		cout << "FAILED!. EN OBTENER NUMERO DE NODO"<< endl;

	delete leaf;
	delete leafRecovered;

}

void TestLeafNode::testInsert()
{

}
