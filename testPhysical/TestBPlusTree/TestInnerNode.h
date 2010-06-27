/**
 * @file TestInnerNode.h
 *
 *  @date: 29/04/2010
 *  @author: kira
 */

#include "../logic/input/InputData.h"
#include "../logic/input/StringInputData.h"

#include "../logic/structures/tree/InnerNode.h"
#include "../logic/structures/tree/dataNode/INodeData.h"
#include "../physical/file/Block.h"

#ifndef TESTINNERNODE_H_
#define TESTINNERNODE_H_

class TestInnerNode {
public:
	TestInnerNode();
	virtual ~TestInnerNode();

public:
	void run();

protected:
	void testInsert();

private:
	InnerNode* node;

};

#endif /* TESTINNERNODE_H_ */
