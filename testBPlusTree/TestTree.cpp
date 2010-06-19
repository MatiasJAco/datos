/**
 * @file TestLeafNode.cpp
 *
 *  @date: 26/04/2010
 *  @author: kira
 */

#include "TestTree.h"

TestTree::TestTree() {
	mainFixture = new BPlusTree("arbol.dat",95,0.5);

}

TestTree::~TestTree() {
	if (mainFixture!=NULL)
		delete mainFixture;
}



void TestTree::run()
{
//	testRecoverLeaf();
//	testInsertLeafSinOverflow();
//	testInsertRoot();

//	testInsertComplejo();

//	testInsertComplejo();

	testRemove();
//	testModify();
//	testFind();
//	testFindInodeData();
//	testRemoveInnerNode();
//	testReadNext();

}

void TestTree::testReadNext()
{
	cout << "\n\t\t*********testReadNext*********\t\t\n";
	StringInputData data;
	mainFixture->insert("1","11");
	mainFixture->insert("2","22");
	mainFixture->insert("3","33");
	mainFixture->insert("4","44");
	mainFixture->insert("5","55");
	mainFixture->insert("6","66");
	mainFixture->insert("7","77");
	mainFixture->insert("8","88");
	mainFixture->insert("9","99");



	mainFixture->find("3",data);
	mainFixture->print();

	// Mientras pueda obtener un dato.
	while (mainFixture->getNext(data))
	{
		cout << "Clave: " << data.getKey() << endl;
		cout << "Value: " << data.getValue() << endl;
	}

	mainFixture->deleteTree();

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
	StringInputData data1("1","11");
	StringInputData data2("2","22");
	StringInputData data3("3","33");
	StringInputData data4("4","44");
	StringInputData data5("5","55");
	StringInputData data6("6","66");

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

	mainFixture->insert("1","11");
	mainFixture->insert("2","22");
	mainFixture->insert("3","33");
	mainFixture->insert("4","44");
	mainFixture->insert("5","55");
	mainFixture->insert("6","66");

	mainFixture->print();

	Node* nodoroot = mainFixture->getNode(1);
	Node* leaforig = mainFixture->getNode(2);
	Node* leafsplit = mainFixture->getNode(3);

	nodoroot->printContent();
	leaforig->printContent();
	leafsplit->printContent();



	cout << "\n\t\t*********testInsertRoot*********\t\t\n";
}

void TestTree::testInsertComplejo()
{
	cout << "\n\t\t*********testInsertComplejo*********\t\t\n";

	mainFixture->insert("a","11");
	mainFixture->insert("b","22");
	mainFixture->insert("c","33");
	mainFixture->insert("ca","44");
	mainFixture->insert("ba","55");
	mainFixture->insert("*","66");
	mainFixture->insert("cos","77");
	mainFixture->insert("d","88");


	Node* nodoroot = mainFixture->getNode(1);
	Node* leaf2 = mainFixture->getNode(2);
	Node* leaf3 = mainFixture->getNode(3);
	Node* leaf4 = mainFixture->getNode(4);
	Node* leaf5 = mainFixture->getNode(5);
	Node* leaf6 = mainFixture->getNode(6);
	Node* leaf7 = mainFixture->getNode(7);
	Node* leaf8 = mainFixture->getNode(8);



	//Testeo de findInodeDATA
	InnerNode* leaf10 = dynamic_cast<InnerNode*> (mainFixture->getNode(10));

	leaf10->printContent();
	INodeData search(3,"3");
	INodeData found;

	if(!leaf10->findINodeData(search,found, InnerNode::EQUAL))
		cout << "Error en el equal"<<endl;

	if(!leaf10->findINodeData(search,found, InnerNode::BIGGER))
		cout << "Error en el bigger"<<endl;

	if(leaf10->findINodeData(search,found, InnerNode::MINOR))
		cout << "Error en el minor"<<endl;

	INodeData search2(3,"7");
	if(!leaf10->findINodeData(search2,found, InnerNode::EQUAL))
		cout << "Error en el equal"<<endl;

	if(!leaf10->findINodeData(search2,found, InnerNode::MINOR))
		cout << "Error en el minor"<<endl;

	if(leaf10->findINodeData(search2,found, InnerNode::BIGGER))
		cout << "Error en el bigger"<<endl;

	INodeData search3(3,"5");

	if(!leaf10->findINodeData(search3,found, InnerNode::BIGGER))
		cout << "Error en el bigger"<<endl;

	mainFixture->print();
	mainFixture->deleteTree();

	nodoroot->printContent();
	leaf2->printContent();
	leaf3->printContent();
	leaf4->printContent();
	leaf5->printContent();
	leaf6->printContent();
	leaf7->printContent();
	leaf8->printContent();

}

void TestTree::testFindInodeData()
{
	StringInputData data;


	mainFixture->insert("1","11");
	mainFixture->insert("2","22");
	mainFixture->insert("3","33");
	mainFixture->insert("4","44");
	mainFixture->insert("5","55");
	mainFixture->insert("6","66");
	mainFixture->insert("7","77");
	mainFixture->insert("8","88");
	mainFixture->insert("9","99");
	mainFixture->insert("10","100");
	mainFixture->insert("22","02");
	mainFixture->insert("37","03");
	mainFixture->insert("88","04");
	mainFixture->insert("55","05");
	mainFixture->insert("29","06");
	mainFixture->insert("26","07");
	mainFixture->insert("27","08");
	mainFixture->insert("18","09");

	//mainFixture->remove(data8);


	mainFixture->print();

	mainFixture->remove("1");

	InnerNode* leaf9 = dynamic_cast<InnerNode*> (mainFixture->getNode(9));

	leaf9->printContent();
	INodeData search(3,"-1");
	INodeData found;
	if(!leaf9->findINodeData(search,found, InnerNode::MINOR))
		cout << "Error en el equal"<<endl;


	mainFixture->print();

	mainFixture->deleteTree();
}


void TestTree::testRemove()
{


	mainFixture->insert("a","11");
	mainFixture->insert("ca","22");
	mainFixture->insert("r","33");
	mainFixture->insert("ro","44");
	mainFixture->insert("poy","55");
	mainFixture->insert("pp","66");
	mainFixture->insert("reti","77");
	mainFixture->insert("e","88");
	mainFixture->insert("A","99");
	mainFixture->insert("n","100");
	mainFixture->insert("l","02");
	mainFixture->insert("ava","03");
	mainFixture->insert("aba","04");
	mainFixture->insert("m","05");
	mainFixture->insert("rq","06");
	mainFixture->insert("w","07");
	mainFixture->insert("*","08");
	mainFixture->insert("@","09");
	mainFixture->insert("h","10");





	mainFixture->remove("a");
	mainFixture->remove("ca");



	mainFixture->print();

	mainFixture->deleteTree();
}

void TestTree::testModify(){

	cout << "\n\t\t*********testModify*********\t\t\n";
	//StringInputData data;

		StringInputData data1("a","11");
		StringInputData data2("*","22");
		StringInputData data3("*@","33");
		StringInputData data4("1","44");
		StringInputData data5("po","55");
		StringInputData data6("t","00000000000000000");
		StringInputData data7("mn","77");
		StringInputData data8("n","88");
		StringInputData data9("re","99");
		StringInputData data10("b","01");
		StringInputData data11("ñ","0000000000000000");
		StringInputData data12();
		StringInputData data13();
		StringInputData data14();
		StringInputData data15();
		StringInputData data16();
		StringInputData data17();
		StringInputData data18();
		StringInputData data19();
		StringInputData data20();


		mainFixture->insert("a","11");
		mainFixture->insert("*","22");
		mainFixture->insert("*@","33");
		mainFixture->insert("1","44");
		mainFixture->insert("po","55");
		mainFixture->print();
		mainFixture->insert("t","00000000000000000");
		mainFixture->print();
		mainFixture->insert("mn","77");
		mainFixture->insert("n","88");
		mainFixture->insert("re","99");
		mainFixture->insert("b","01");
		mainFixture->insert("ñ","0000000000000000");
//		mainFixture->insert("37","03");
//		mainFixture->insert("88","04");
//		mainFixture->insert("55","05");
//		mainFixture->insert("29","06");
//		mainFixture->insert("26","07");
//		mainFixture->insert("27","08");
//		mainFixture->insert("18","09");
//		mainFixture->insert("19","10");
//		mainFixture->insert("20","11");



		mainFixture->print();
		mainFixture->modify("t","10");
		mainFixture->print();

		mainFixture->modify("po","10r00000000000000000");
		mainFixture->print();

		mainFixture->modify("a","10000000000000000000");
		mainFixture->print();

		mainFixture->modify("ñ","10");
		mainFixture->print();

	mainFixture->deleteTree();

}

void TestTree::testFind(){

	cout << "\n\t\t*********testModify*********\t\t\n";

	StringInputData data;

	mainFixture->insert("7","11");
	mainFixture->insert("33","22");
	mainFixture->insert("12","33");
	mainFixture->insert("25","44");
	mainFixture->insert("5","55");
	mainFixture->insert("98","66");
	mainFixture->insert("75","77");
	mainFixture->insert("48","88");
	mainFixture->insert("99","99");
	mainFixture->insert("64","01");
	mainFixture->insert("22","02");
	mainFixture->insert("37","03");
	mainFixture->insert("88","04");
	mainFixture->insert("55","05");
	mainFixture->insert("29","06");
	mainFixture->insert("26","07");
	mainFixture->insert("27","08");
	mainFixture->insert("18","09");

	mainFixture->print();
	StringInputData datoDevuelto("0","");
	//Busca 1.
	StringInputData datoABuscar("1","");
	mainFixture->find("1",datoDevuelto);
	//Busca 22.
	datoABuscar.setKey("22");
	mainFixture->find("22",datoDevuelto);
	//Busca 25.
	datoABuscar.setKey("25");
	mainFixture->find("25",datoDevuelto);

	mainFixture->deleteTree();



}

void TestTree::testRemoveInnerNode()
{
	StringInputData data;
	StringInputData data1();
	StringInputData data2();
	StringInputData data3();
	StringInputData data4();
	StringInputData data5();
	StringInputData data6();
	StringInputData data7();
	StringInputData data8();
	StringInputData data9();
	StringInputData data10();
	StringInputData data11();
	StringInputData data12();
	StringInputData data13();
	StringInputData data14();
	StringInputData data15();
	StringInputData data16();
	StringInputData data17();
	StringInputData data18();
	StringInputData data19();
	StringInputData data20();


	mainFixture->insert("1","11");
	mainFixture->insert("2","22");
	mainFixture->insert("3","33");
	mainFixture->insert("4","44");
	mainFixture->insert("5","55");
	mainFixture->insert("6","66");
	mainFixture->insert("7","77");
	mainFixture->insert("8","88");
	mainFixture->insert("9","99");
	mainFixture->insert("64","01");
	mainFixture->insert("22","02");
	mainFixture->insert("37","03");
	mainFixture->insert("88","04");
	mainFixture->insert("55","05");
	mainFixture->insert("29","06");
	mainFixture->insert("26","07");
	mainFixture->insert("27","08");
	mainFixture->insert("18","09");
	mainFixture->insert("19","10");
	mainFixture->insert("20","11");

	mainFixture->print();



	cout<<endl<<"----------------------"<<endl;


	mainFixture->remove("1");
	mainFixture->remove("2");
	mainFixture->remove("3");
//	mainFixture->remove("4");
//	mainFixture->remove("5");
//	mainFixture->remove("6");
//	mainFixture->remove("7");
//	mainFixture->remove("8");
//	mainFixture->remove("9");
//	mainFixture->remove("64");
//	mainFixture->remove("22");
//	mainFixture->remove("37");
//	mainFixture->remove("88");
//	mainFixture->remove("55");
//	mainFixture->remove("29");
//	mainFixture->remove("26");
//	mainFixture->remove("27");
//	mainFixture->remove("18");
//	mainFixture->remove("19");
//	mainFixture->remove("20");

	mainFixture->print();

	mainFixture->deleteTree();
}
