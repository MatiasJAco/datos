/**
 * @file TestInnerNode.cpp
 *
 *  @date: 29/04/2010
 *  @author: kira
 */

#include "TestInnerNode.h"

TestInnerNode::TestInnerNode() {
	// TODO Auto-generated constructor stub
	StringInputData typedata(5,"hola");
	Block* block = new Block(8,64,0.5);
	InnerNode* node = new InnerNode(8,1,block,typedata);

}

TestInnerNode::~TestInnerNode() {
	// TODO Auto-generated destructor stub
	if (node!=NULL)
		delete node;
}

void TestInnerNode::testInsert()
{
	INodeData elemNodo1(0,0);
	INodeData elemNodo2(0,0);
	INodeData elemNodo3(0,0);
	INodeData elemNodo4(0,0);
	INodeData elemNodo5(0,0);

	INodeData promotedKey;

	node->insertINodeData(elemNodo1,promotedKey);
	node->insertINodeData(elemNodo2,promotedKey);
	node->insertINodeData(elemNodo3,promotedKey);
	node->insertINodeData(elemNodo4,promotedKey);
	node->insertINodeData(elemNodo5,promotedKey);


}
