/**
 * @file BPlusTree.cpp
 *
 *  @date: 24/04/2010
 *  @author: kira
 */
#include "BPlusTree.h"

using namespace std;

const string BPlusTree::FILENAME_DEFAULT = "arbolbmas.dat";

BPlusTree::BPlusTree()
{
	m_sizeNodes = SIZENODE_DEFAULT;
	m_branchFactor = BRANCHFACTOR_DEFAULT;
	file.open(FILENAME_DEFAULT,SIZENODE_DEFAULT);
}

BPlusTree::BPlusTree(unsigned int sizeNodes,double branchFactor)
{
	m_sizeNodes = sizeNodes;
	m_branchFactor = branchFactor;
	file.open(FILENAME_DEFAULT,sizeNodes);

	/// Creo la raiz y la guardo, o la leo de disco.
	/// Obtengo el block 0 que es la raiz

	m_root = getNode(ROOT_NODENUMBER);

	if (m_root == NULL)
	{
		/// Creo la raiz.
		m_root = newLeafNode();
		saveNode(m_root);
	}
}


BPlusTree::~BPlusTree()
{
	file.close();
}


BPlusTree::BPlusTree(string nameFile,unsigned int sizeNodes,double branchFactor)
{
	m_sizeNodes = sizeNodes;
	m_branchFactor = branchFactor;
	file.open(nameFile,sizeNodes);

	m_root = getNode(ROOT_NODENUMBER);

	if (m_root == NULL)
	{
		/// Creo la raiz.
		m_root = newLeafNode();
		saveNode(m_root);
	}
}


Node *BPlusTree::getNode(const unsigned int nodeNumber)
{
	Node* node = NULL;

	Block* block = file.getBlock(nodeNumber);

	if (block!=NULL)
	{
		Node* node = NULL;

		unsigned int nodeNumber = block->getBlockNumber();
		unsigned int level = Node::readLevel(*block);

		if (level == Node::LEAF_LEVEL)
		{
			node = new LeafNode(nodeNumber,block);
		}
		else
		{
			node = new InnerNode(nodeNumber,level,block,this);
		}
	}

	return node;
}

void BPlusTree::saveNode(Node* node)
{
	Block* block = node->getBlock();

	file.saveBlock(block);
}

Node* BPlusTree::newInnerNode(unsigned int level)
{
	Block* block = file.getNewBlock();
	unsigned int nodeNumber = block->getBlockNumber();

	Node* node = new InnerNode(nodeNumber,level,block,this);

	return node;
}

Node* BPlusTree::newLeafNode()
{
	Block* block = file.getNewBlock();
	unsigned int nodeNumber = block->getBlockNumber();

	Node* node = new LeafNode(nodeNumber,block);

	return node;
}
