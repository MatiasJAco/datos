/**
 * @file TestLeafNode.h
 *
 *  @date: 26/04/2010
 *  @author: kira
 */

#include "../logic/tree/BPlusTree.h"
#include "../logic/tree/LeafNode.h"
#include "../logic/input/InputData.h"
#include "../logic/input/StringInputData.h"

#ifndef TESTLEAFNODE_H_
#define TESTLEAFNODE_H_

class TestLeafNode {
public:
	TestLeafNode();
	virtual ~TestLeafNode();

public:
	void run();

protected:
	void testRecoverLeaf();
	void testInsert();

private:
	BPlusTree* mainFixture;
};

#endif /* TESTLEAFNODE_H_ */
