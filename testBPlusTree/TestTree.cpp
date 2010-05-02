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
//	testInsertRoot();

//	testInsertComplejo();


//	testInsertComplejo();
//	testRemove();
//	testModify();
//	testFind();
	testRemoveInnerNode();

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

	StringInputData data1(7,"11");
	StringInputData data2(33,"22");
	StringInputData data3(12,"33");
	StringInputData data4(25,"44");
	StringInputData data5(5,"55");
	StringInputData data6(98,"66");
	StringInputData data7(75,"77");
	StringInputData data8(48,"88");
	StringInputData data9(99,"99");
	StringInputData data10(64,"01");
	StringInputData data11(22,"02");
	StringInputData data12(37,"03");
	StringInputData data13(88,"04");
	StringInputData data14(55,"05");
	StringInputData data15(29,"06");
	StringInputData data16(26,"07");
	StringInputData data17(27,"08");
	StringInputData data18(18,"09");
	StringInputData data19(19,"10");
	StringInputData data20(20,"11");
	StringInputData data21(21,"12");
	StringInputData data22(80,"13");
	StringInputData data23(23,"08");
	StringInputData data24(24,"09");
	StringInputData data25(70,"10");
	StringInputData data26(71,"11");
	StringInputData data27(72,"12");
	StringInputData data28(28,"13");
	StringInputData data29(73,"09");
	StringInputData data30(30,"10");
	StringInputData data31(31,"11");
	StringInputData data32(66,"12");
	StringInputData data33(87,"13");
	StringInputData data34(34,"09");
	StringInputData data35(35,"10");
	StringInputData data36(36,"11");
	StringInputData data37(102,"12");
	StringInputData data38(38,"13");
	StringInputData data39(39,"09");
	StringInputData data40(40,"10");
	StringInputData data41(41,"11");
	StringInputData data42(42,"12");
	StringInputData data43(43,"13");
	StringInputData data44(44,"09");
	StringInputData data45(45,"10");
	StringInputData data46(46,"11");
	StringInputData data47(47,"12");
	StringInputData data48(91,"13");
	StringInputData data49(49,"09");
	StringInputData data50(50,"10");
	StringInputData data51(51,"11");
	StringInputData data52(52,"12");
	StringInputData data53(53,"13");
	StringInputData data54(54,"09");
	StringInputData data55(90,"10");
	StringInputData data56(56,"11");
	StringInputData data57(57,"12");
	StringInputData data58(58,"13");
	StringInputData data59(59,"13");
	StringInputData data60(1,"11");

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
	mainFixture->insert(data17);
	mainFixture->insert(data18);
	mainFixture->insert(data19);
	mainFixture->insert(data20);
	mainFixture->insert(data21);
	mainFixture->insert(data22);
	mainFixture->insert(data23);
	mainFixture->insert(data24);
	mainFixture->insert(data25);
	mainFixture->insert(data26);
	mainFixture->insert(data27);
	mainFixture->insert(data28);
	mainFixture->insert(data29);
	mainFixture->insert(data30);
	mainFixture->insert(data31);
	mainFixture->insert(data32);
	mainFixture->insert(data33);
	mainFixture->insert(data34);
	mainFixture->insert(data35);
	mainFixture->insert(data36);
	mainFixture->insert(data37);
	mainFixture->insert(data38);
	mainFixture->insert(data39);
	mainFixture->insert(data40);
	mainFixture->insert(data41);
	mainFixture->insert(data42);
	mainFixture->insert(data43);
	mainFixture->insert(data44);
	mainFixture->insert(data45);
	mainFixture->insert(data46);
	mainFixture->insert(data47);
	mainFixture->insert(data48);
	mainFixture->insert(data49);
	mainFixture->insert(data50);
	mainFixture->insert(data51);
	mainFixture->insert(data52);
	mainFixture->insert(data53);
	mainFixture->insert(data54);
	mainFixture->insert(data55);
	mainFixture->insert(data56);
	mainFixture->insert(data57);
	mainFixture->insert(data58);
	mainFixture->insert(data59);
	mainFixture->insert(data60);

//	Node* nodoroot = mainFixture->getNode(1);
//	Node* leaf2 = mainFixture->getNode(2);
//	Node* leaf3 = mainFixture->getNode(3);
//	Node* leaf4 = mainFixture->getNode(4);
//	Node* leaf5 = mainFixture->getNode(5);
//	Node* leaf6 = mainFixture->getNode(6);
//	Node* leaf7 = mainFixture->getNode(7);
//	Node* leaf8 = mainFixture->getNode(8);
//	Node* leaf9 = mainFixture->getNode(9);
//	Node* leaf10 = mainFixture->getNode(10);


	//Testeo de findInodeDATA
//	InnerNode* leaf10 = dynamic_cast<InnerNode*> (mainFixture->getNode(10));
//
//	leaf10->printContent(data);
//	INodeData search(3,3);
//	INodeData found;
//
//	if(!leaf10->findINodeData(search,found, InnerNode::EQUAL))
//		cout << "Error en el equal"<<endl;
//
//	if(!leaf10->findINodeData(search,found, InnerNode::BIGGER))
//		cout << "Error en el bigger"<<endl;
//
//	if(leaf10->findINodeData(search,found, InnerNode::MINOR))
//		cout << "Error en el minor"<<endl;
//
//	INodeData search2(3,7);
//	if(!leaf10->findINodeData(search2,found, InnerNode::EQUAL))
//		cout << "Error en el equal"<<endl;
//
//	if(!leaf10->findINodeData(search2,found, InnerNode::MINOR))
//		cout << "Error en el minor"<<endl;
//
//	if(leaf10->findINodeData(search2,found, InnerNode::BIGGER))
//		cout << "Error en el bigger"<<endl;
//
//	INodeData search3(3,5);
//
//	if(!leaf10->findINodeData(search3,found, InnerNode::BIGGER))
//		cout << "Error en el bigger"<<endl;

	mainFixture->showTree(data);
	mainFixture->deleteTree();

//	Node* leafsplit = mainFixture->getNode(3);
//
//	nodoroot->printContent(data);
//	leaf2->printContent(data);
//	leaf3->printContent(data);
//	leaf4->printContent(data);
//	leaf5->printContent(data);
//	leaf6->printContent(data);
//	leaf7->printContent(data);
//	leaf8->printContent(data);
//	leaf9->printContent(data);

}

void TestTree::testRemove()
{
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
	StringInputData data10(10,"100");
	StringInputData data11(22,"02");
	StringInputData data12(37,"03");
	StringInputData data13(88,"04");
	StringInputData data14(55,"05");
	StringInputData data15(29,"06");
	StringInputData data16(26,"07");
	StringInputData data17(27,"08");
	StringInputData data18(18,"09");
	StringInputData data19(19,"10");



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
	mainFixture->insert(data17);
	mainFixture->insert(data18);

	mainFixture->remove(data8);


//	mainFixture->showTree(data);

//	mainFixture->remove(data1);
//	mainFixture->remove(data2);
//	mainFixture->remove(data3);
//	mainFixture->remove(data4);
//	mainFixture->remove(data5);
//	mainFixture->remove(data6);



	mainFixture->showTree(data);

	mainFixture->deleteTree();
}

void TestTree::testModify(){

	cout << "\n\t\t*********testModify*********\t\t\n";

		StringInputData data;

		StringInputData data1(7,"11");
		StringInputData data2(33,"22");
		StringInputData data3(12,"33");
		StringInputData data4(25,"44");
		StringInputData data5(5,"55");
		StringInputData data6(98,"66");
		StringInputData data7(75,"77");
		StringInputData data8(48,"88");
		StringInputData data9(99,"99");
		StringInputData data10(64,"01");
//		StringInputData data11(22,"02");
//		StringInputData data12(37,"03");
//		StringInputData data13(88,"04");
//		StringInputData data14(55,"05");
//		StringInputData data15(29,"06");
//		StringInputData data16(26,"07");
//		StringInputData data17(27,"08");
//		StringInputData data18(18,"09");
//		StringInputData data19(19,"10");
//		StringInputData data20(20,"11");
//		StringInputData data21(21,"12");
//		StringInputData data22(80,"13");
//		StringInputData data23(23,"08");
//		StringInputData data24(24,"09");
//		StringInputData data25(70,"10");
//		StringInputData data26(71,"11");
//		StringInputData data27(72,"12");
//		StringInputData data28(28,"13");
//		StringInputData data29(73,"09");
//		StringInputData data30(30,"10");
//		StringInputData data31(31,"11");
//		StringInputData data32(66,"12");
//		StringInputData data33(87,"13");
//		StringInputData data34(34,"09");
//		StringInputData data35(35,"10");
//		StringInputData data36(36,"11");
//		StringInputData data37(102,"12");
//		StringInputData data38(38,"13");
//		StringInputData data39(39,"09");
//		StringInputData data40(40,"10");
//		StringInputData data41(41,"11");
//		StringInputData data42(42,"12");
//		StringInputData data43(43,"13");
//		StringInputData data44(44,"09");
//		StringInputData data45(45,"10");
//		StringInputData data46(46,"11");
//		StringInputData data47(47,"12");
//		StringInputData data48(91,"13");
//		StringInputData data49(49,"09");
//		StringInputData data50(50,"10");
//		StringInputData data51(51,"11");
//		StringInputData data52(52,"12");
//		StringInputData data53(53,"13");
//		StringInputData data54(54,"09");
//		StringInputData data55(90,"10");
//		StringInputData data56(56,"11");
//		StringInputData data57(57,"12");
//		StringInputData data58(58,"13");
//		StringInputData data59(59,"13");
//		StringInputData data60(1,"11");

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
//		mainFixture->insert(data11);
//		mainFixture->insert(data12);
//		mainFixture->insert(data13);
//		mainFixture->insert(data14);
//		mainFixture->insert(data15);
//		mainFixture->insert(data16);
//		mainFixture->insert(data17);
//		mainFixture->insert(data18);
//		mainFixture->insert(data19);
//		mainFixture->insert(data20);
//		mainFixture->insert(data21);
//		mainFixture->insert(data22);
//		mainFixture->insert(data23);
//		mainFixture->insert(data24);
//		mainFixture->insert(data25);
//		mainFixture->insert(data26);
//		mainFixture->insert(data27);
//		mainFixture->insert(data28);
//		mainFixture->insert(data29);
//		mainFixture->insert(data30);
//		mainFixture->insert(data31);
//		mainFixture->insert(data32);
//		mainFixture->insert(data33);
//		mainFixture->insert(data34);
//		mainFixture->insert(data35);
//		mainFixture->insert(data36);
//		mainFixture->insert(data37);
//		mainFixture->insert(data38);
//		mainFixture->insert(data39);
//		mainFixture->insert(data40);
//		mainFixture->insert(data41);
//		mainFixture->insert(data42);
//		mainFixture->insert(data43);
//		mainFixture->insert(data44);
//		mainFixture->insert(data45);
//		mainFixture->insert(data46);
//		mainFixture->insert(data47);
//		mainFixture->insert(data48);
//		mainFixture->insert(data49);
//		mainFixture->insert(data50);
//		mainFixture->insert(data51);
//		mainFixture->insert(data52);
//		mainFixture->insert(data53);
//		mainFixture->insert(data54);
//		mainFixture->insert(data55);
//		mainFixture->insert(data56);
//		mainFixture->insert(data57);
//		mainFixture->insert(data58);
//		mainFixture->insert(data59);
//		mainFixture->insert(data60);

		StringInputData datoMod(75,"10");
		StringInputData datoaMod(75,"");
		mainFixture->showTree(data);
		mainFixture->modifyElement(datoaMod,datoMod);
		mainFixture->showTree(data);
		mainFixture->deleteTree();

}

void TestTree::testFind(){

	cout << "\n\t\t*********testModify*********\t\t\n";

	StringInputData data;

	StringInputData data1(7,"11");
	StringInputData data2(33,"22");
	StringInputData data3(12,"33");
	StringInputData data4(25,"44");
	StringInputData data5(5,"55");
	StringInputData data6(98,"66");
	StringInputData data7(75,"77");
	StringInputData data8(48,"88");
	StringInputData data9(99,"99");
	StringInputData data10(64,"01");
	StringInputData data11(22,"02");
	StringInputData data12(37,"03");
	StringInputData data13(88,"04");
	StringInputData data14(55,"05");
	StringInputData data15(29,"06");
	StringInputData data16(26,"07");
	StringInputData data17(27,"08");
	StringInputData data18(18,"09");



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
	mainFixture->insert(data17);
	mainFixture->insert(data18);

	mainFixture->showTree(data);
	StringInputData datoDevuelto(0,"");
	//Busca 1.
	StringInputData datoABuscar(1,"");
	mainFixture->find(datoABuscar,datoDevuelto);
	//Busca 22.
	datoABuscar.setKey(22);
	mainFixture->find(datoABuscar,datoDevuelto);
	//Busca 125.
	datoABuscar.setKey(125);
	mainFixture->find(datoABuscar,datoDevuelto);

	mainFixture->deleteTree();



}

void TestTree::testRemoveInnerNode()
{
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
	StringInputData data10(64,"01");
	StringInputData data11(22,"02");
	StringInputData data12(37,"03");
	StringInputData data13(88,"04");
	StringInputData data14(55,"05");
	StringInputData data15(29,"06");
	StringInputData data16(26,"07");
	StringInputData data17(27,"08");
	StringInputData data18(18,"09");
	StringInputData data19(19,"10");
	StringInputData data20(20,"11");


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
	mainFixture->insert(data17);
	mainFixture->insert(data18);
	mainFixture->insert(data19);
	mainFixture->insert(data20);

	mainFixture->showTree(data);



	cout<<endl<<"----------------------"<<endl;


	mainFixture->remove(data1);
	mainFixture->remove(data2);
	mainFixture->remove(data3);
//	mainFixture->remove(data4);
//	mainFixture->remove(data5);
//	mainFixture->remove(data6);
//	mainFixture->remove(data7);
//	mainFixture->remove(data8);
//	mainFixture->remove(data9);
//	mainFixture->remove(data10);
//	mainFixture->remove(data11);
//	mainFixture->remove(data12);
//	mainFixture->remove(data13);
//	mainFixture->remove(data14);
//	mainFixture->remove(data15);
//	mainFixture->remove(data16);
//	mainFixture->remove(data17);
//	mainFixture->remove(data18);
//	mainFixture->remove(data19);
//	mainFixture->remove(data20);

	mainFixture->showTree(data);

	mainFixture->deleteTree();
}
