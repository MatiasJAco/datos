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
	Block* block = file.getBlock(0);

	if (block==NULL)
	{
		block = file.getNewBlock();
	}
	///TODO ver cuando es creada por primera vez.
	m_root = NodeFactory::newNode(block);
}

BPlusTree::BPlusTree(string nameFile,unsigned int sizeNodes,double branchFactor)
{
	m_sizeNodes = sizeNodes;
	m_branchFactor = branchFactor;
	file.open(nameFile,sizeNodes);
}

Node *BPlusTree::getNode(const unsigned int nodeNumber)
{
	Node* node = NULL;

	Block* block = file.getBlock(nodeNumber);

	if (block!=NULL)
		node = NodeFactory::newNode(block);

	return node;
}

void BPlusTree::saveNode(Node* node)
{
	Block* block = node->getBlock();

	file.saveBlock(block);
}


int BPlusTree::getNodeQuantity()
{
	throw "Hay que sacarlo, no es necesario!";
}




