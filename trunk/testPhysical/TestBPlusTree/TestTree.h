/**
 * @file TestLeafNode.h
 *
 *  @date: 26/04/2010
 *  @author: kira
 */

#include "../logic/structures/tree/BPlusTree.h"
#include "../logic/structures/tree/LeafNode.h"
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
	void testGetFirstElement();
	void testRecoverLeaf();
	void testInsertLeafSinOverflow();
	void testInsertRoot();
	void testModify();
	void testFind();
	void testInsertComplejo();
	void testRemove();
	void testRemoveInnerNode();
	void testFindInodeData();
	void testReadNext();
	void testReadPrevious();


private:
	BPlusTree* mainFixture;
};

#endif /* TESTLEAFNODE_H_ */
