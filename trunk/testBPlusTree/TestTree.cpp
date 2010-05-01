/**
 * @file TestLeafNode.cpp
 *
 *  @date: 26/04/2010
 *  @author: kira
 */

#include "TestTree.h"

TestTree::TestTree() {
	// TODO Auto-generated constructor stub
	StringInputData typedata(4,"hola");
	mainFixture = new BPlusTree("arbol.dat",92,0.5,typedata);

}

TestTree::~TestTree() {
	// TODO Auto-generated destructor stub
	if (mainFixture!=NULL)
		delete mainFixture;
}



void TestTree::run()
{
//	testRecoverLeaf();
//	testInsertLeafSinOverflow();
	testInsertRoot();
//	testInsertComplejo();
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

}

void TestTree::testInsertLeafSinOverflow()
{
	cout << "\n\t\t*********testInsertLeaf*********\t\t\n";

	LeafNode* leaf = (LeafNode*)mainFixture->newLeafNode();

	StringInputData data;
	StringInputData data1(1,"11");
	StringInputData data2(2,"22");
	StringInputData data3(3,"33");
	StringInputData data4(4,"44");
	StringInputData data5(5,"55");
	StringInputData data6(6,"66");

	INodeData promotedKey;

	leaf->insert(data1,promotedKey);
	leaf->insert(data2,promotedKey);
	leaf->insert(data3,promotedKey);
	leaf->insert(data4,promotedKey);
	leaf->insert(data5,promotedKey);
	leaf->insert(data6,promotedKey);

	cout << "Espacio bloque: "<< leaf->getBlock()->getUsedSpace();

//	leaf->printContent(data&);


	cout << "hoja nueva: " << promotedKey.getKey() << "-" << promotedKey.getLeftPointer() << endl;

	LeafNode* leafsplit = (LeafNode*)mainFixture->getNode(promotedKey.getLeftPointer());

//	leafsplit->printContent(data);

	//	cout << leaf->toStringData(data);


	mainFixture->deleteNode(leaf);
	mainFixture->deleteNode(leafsplit);
}

void TestTree::testInsertRoot()
{
	cout << "\n\t\t*********testInsertRoot*********\t\t\n";

	StringInputData data;
	StringInputData data1(1,"11");
	StringInputData data2(2,"22");
	StringInputData data3(3,"33");
	StringInputData data4(4,"44");
	StringInputData data5(5,"55");
	StringInputData data6(6,"66");

	mainFixture->insert(data1);
	mainFixture->insert(data2);
	mainFixture->insert(data3);
	mainFixture->insert(data4);
	mainFixture->insert(data5);
	mainFixture->insert(data6);

	mainFixture->showTree(data);

//	Node* nodoroot = mainFixture->getNode(1);
//	Node* leaforig = mainFixture->getNode(2);
//	Node* leafsplit = mainFixture->getNode(3);
//
//	nodoroot->printContent(data);
//	leaforig->printContent(data);
//	leafsplit->printContent(data);



	cout << "\n\t\t*********testInsertRoot*********\t\t\n";
}

void TestTree::testInsertComplejo()
{
	cout << "\n\t\t*********testInsertComplejo*********\t\t\n";

	StringInputData data;
	StringInputData data1(1,"11");
	StringInputData data2(2,"22");
	StringInputData data3(3,"33");
	StringInputData data4(4,"44");
	StringInputData data5(5,"55");
	StringInputData data6(6,"66");
	StringInputData data7(7,"77");
	StringInputData data8(8,"88");
	StringInputData data9(9,"99");
	StringInputData data10(10,"01");
	StringInputData data11(11,"02");
	StringInputData data12(12,"03");
	StringInputData data13(13,"04");
	StringInputData data14(14,"05");
	StringInputData data15(15,"06");
	StringInputData data16(16,"07");



	mainFixture->insert(data1);
	mainFixture->insert(data2);
	mainFixture->insert(data3);
	mainFixture->insert(data4);
	mainFixture->insert(data5);
	mainFixture->insert(data6);
	mainFixture->insert(data7);
	mainFixture->insert(data8);
	mainFixture->insert(data9);
	mainFixture->insert(data10);
	mainFixture->insert(data11);
	mainFixture->insert(data12);
	mainFixture->insert(data13);
	mainFixture->insert(data14);
	mainFixture->insert(data15);
	mainFixture->insert(data16);

	Node* nodoroot = mainFixture->getNode(1);
	Node* leaf2 = mainFixture->getNode(2);
	Node* leaf3 = mainFixture->getNode(3);
	Node* leaf4 = mainFixture->getNode(4);
	Node* leaf5 = mainFixture->getNode(5);
	Node* leaf6 = mainFixture->getNode(6);
	Node* leaf7 = mainFixture->getNode(7);
	Node* leaf8 = mainFixture->getNode(8);
	Node* leaf9 = mainFixture->getNode(9);
	Node* leaf10 = mainFixture->getNode(10);


//	Node* leafsplit = mainFixture->getNode(3);

	nodoroot->printContent(data);
	leaf2->printContent(data);
	leaf3->printContent(data);
	leaf4->printContent(data);
	leaf5->printContent(data);
	leaf6->printContent(data);
	leaf7->printContent(data);
	leaf8->printContent(data);
	leaf9->printContent(data);
	leaf10->printContent(data);





}

