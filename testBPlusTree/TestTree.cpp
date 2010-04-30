/**
 * @file TestLeafNode.cpp
 *
 *  @date: 26/04/2010
 *  @author: kira
 */

#include "TestTree.h"

TestTree::TestTree() {
	// TODO Auto-generated constructor stub
	mainFixture = new BPlusTree("arbol.dat",64,0.5);

}

TestTree::~TestTree() {
	// TODO Auto-generated destructor stub
	if (mainFixture!=NULL)
		delete mainFixture;
}



void TestTree::run()
{
	testRecoverLeaf();
	testInsertLeaf();
}

void TestTree::testRecoverLeaf()
{
	cout << "\n\t\t*********TestRecoverLeaf*********\t\t\n";

	LeafNode* leaf = (LeafNode*)mainFixture->newLeafNode();
	StringInputData data;

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


	mainFixture->deleteNode(leaf);

	delete leafRecovered;

	cout << "\n\t\t*********TestRecoverLeaf*********\t\t\n";

}

void TestTree::testInsertLeaf()
{
	cout << "\n\t\t*********testInsertLeaf*********\t\t\n";

	LeafNode* leaf = (LeafNode*)mainFixture->newLeafNode();

	StringInputData data1(1,"11");
	StringInputData data2(2,"22");
	StringInputData data3(3,"33");
	StringInputData data4(4,"44");
	StringInputData data5(5,"55");

	INodeData promotedKey;

	leaf->insert(data1,promotedKey);
	leaf->insert(data2,promotedKey);
	leaf->insert(data3,promotedKey);
	leaf->insert(data4,promotedKey);
	leaf->insert(data5,promotedKey);

	StringInputData data;

	leaf->printContent(data);

	mainFixture->deleteNode(leaf);

	cout << "\n\t\t*********testInsertLeaf*********\t\t\n";
}
