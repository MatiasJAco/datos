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

	m_root = getNode(1);

	if (m_root == NULL)
	{
		/// Creo la raiz.
		unsigned int nodeNumber = Node::UNDEFINED_NODE_NUMBER;
		block = getNewNodeBlock(&nodeNumber);
		m_root = new LeafNode(nodeNumber);
		m_root->setBlock(block);
		saveNode(m_root);
	}
}

BPlusTree::BPlusTree(string nameFile,unsigned int sizeNodes,double branchFactor)
{
	m_sizeNodes = sizeNodes;
	m_branchFactor = branchFactor;
	file.open(nameFile,sizeNodes);

	m_root = getNode(1);

	if (m_root == NULL)
	{
		/// Creo la raiz.
		unsigned int nodeNumber = Node::UNDEFINED_NODE_NUMBER;
		block = getNewNodeBlock(&nodeNumber);
		m_root = new LeafNode(nodeNumber);
		m_root->setBlock(block);
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
			node = new LeafNode(nodeNumber);
		}
		else
		{
			node = new InnerNode(nodeNumber,level);
		}

		node->setBlock(block);
	}

	return node;
}

void BPlusTree::saveNode(Node* node)
{
	Block* block = node->getBlock();

	file.saveBlock(block);
}

Block* BPlusTree::getNewNodeBlock(unsigned int& nodeNumber)
{
	Block* block = file.getNewBlock();
	nodeNumber = block->getBlockNumber();

	return block;
}


int BPlusTree::getNodeQuantity()
{
	throw "Hay que sacarlo, no es necesario!";
}



