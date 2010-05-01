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

#ifndef TESTTREE_H_
#define TESTTREE_H_

class TestTree {
public:
	TestTree();
	virtual ~TestTree();

public:
	void run();

protected:
	void testRecoverLeaf();
	void testInsertLeafSinOverflow();
	void testInsertRoot();

	void testInsertComplejo();

private:
	BPlusTree* mainFixture;
};

#endif /* TESTLEAFNODE_H_ */
