/**
 * @file BPlusTree.cpp
 *
 *  @date: 24/04/2010
 *  @author: kira
 */
#include "BPlusTree.h"

using namespace std;

const string BPlusTree::FILENAME_DEFAULT = "arbolbmas.dat";


BPlusTree::BPlusTree(unsigned int sizeNodes,float branchFactor,const InputData& typeData)
:m_typeData(typeData)
{
	m_sizeNodes = sizeNodes;
	m_branchFactor = branchFactor;

	file.open(FILENAME_DEFAULT,sizeNodes,branchFactor);

	/// Creo la raiz y la guardo, o la leo de disco.
	/// Obtengo el block 0 que es la raiz

	m_root = getNode(ROOT_NODENUMBER);

	if (m_root == NULL)
	{
		/// Creo la raiz.
		m_root = newLeafNode();
		saveNode(m_root);
	}

	m_currentNode = m_root;
}

BPlusTree::BPlusTree(string nameFile,unsigned int sizeNodes,float branchFactor,const InputData& typeData)
:m_typeData(typeData)
{
	m_sizeNodes = sizeNodes;
	m_branchFactor = branchFactor;

	file.open(nameFile,sizeNodes, branchFactor);

	m_root = getNode(ROOT_NODENUMBER);

	if (m_root == NULL)
	{
		/// Creo la raiz.
		m_root = newLeafNode();
		saveNode(m_root);
	}

	m_currentNode = m_root;
}

BPlusTree::~BPlusTree()
{
	file.close();
}

bool BPlusTree::insert(const InputData& data)
throw (BPlusTreeException)
{
	bool retVal = true;

	loadResultEnum result = NORMAL_LOAD;

	unsigned int level = Node::UNDEFINED_NODE_LEVEL;
	INodeData promotedKey;

	if (m_root == NULL)
		throw BPlusTreeException(BPlusTreeException::INNEXISTENT_ROOT);

	try
	{
		result = m_root->insert(data,promotedKey);
	}
	catch(NodeException &e)
	{
		throw BPlusTreeException(e);
	}

	if (result == OVERFLOW_LOAD)
	{

		level = m_root->getLevel();

		/// La raiz se transforma en nodo interno.
		Node* sucesor = m_root;
		m_root = (InnerNode*)newInnerNode(level+1);

		// le cambio el numero de nodo al sucesor y mantengo el definido para la raiz.
		BlockManager::exchangeBlock(m_root->getBlock(),sucesor->getBlock());
		sucesor->nodeNumber(sucesor->getNodeNumber());
		m_root->nodeNumber(m_root->getNodeNumber());

		INodeData firstKey;
		INodeData newKey;
		if (!sucesor->isLeaf()){
			INodeData currentData;
			VarRegister reg;
			Node* nodoIzquierdo=this->getNode(promotedKey.getLeftPointer());
			Block* bloqueIzquierdo;
			while(!nodoIzquierdo->isLeaf()){
			//Obtener primer clave de la rama.

				bloqueIzquierdo =nodoIzquierdo->getBlock();
				//Salteo info de control.
				bloqueIzquierdo->restartCounter();
				bloqueIzquierdo->getNextRegister();
				reg=bloqueIzquierdo->getNextRegister();
				currentData.toNodeData(reg.getValue());
				nodoIzquierdo=this->getNode(currentData.getLeftPointer());
			};
			InputData* leftKey=data.newInstance();
			//Encuentro la primer hoja de la segunda rama.
			bloqueIzquierdo =nodoIzquierdo->getBlock();
			//Salteo info de control.
			bloqueIzquierdo->restartCounter();
			bloqueIzquierdo->getNextRegister();
			bloqueIzquierdo->getNextRegister();
			bloqueIzquierdo->getNextRegister();
			reg=bloqueIzquierdo->getNextRegister();
			leftKey->toData(reg.getValue());
			promotedKey.setKey(leftKey->getKey());

		};
		firstKey.setLeftPointer(sucesor->getNodeNumber());
		firstKey.setKey(promotedKey.getKey());
		newKey.setLeftPointer(promotedKey.getLeftPointer());
		newKey.setKey(Node::UNDEFINED_KEY);

		// habria que hacer casteo dinamico.
		result = ((InnerNode*)m_root)->insertINodeData(firstKey,promotedKey);
		result = ((InnerNode*)m_root)->insertINodeData(newKey,promotedKey);

		saveNode(sucesor);

		saveNode(m_root);

		// La raiz esta insertando el minimo de claves, no puede ser overflow.
		if (result == OVERFLOW_LOAD)
			throw NodeException(NodeException::ANOMALOUS_LOADRESULT);
	}

	return retVal;
}

bool BPlusTree::remove(const InputData& data) throw (BPlusTreeException)
{
	bool retVal = true;
	loadResultEnum result = NORMAL_LOAD;

	// TODO manejo de baja del nivel de profundidad.

	if (m_root == NULL)
		throw BPlusTreeException(BPlusTreeException::INNEXISTENT_ROOT);

	try
	{
		result = m_root->remove(data);
	}
	catch(NodeException &e)
	{
		throw BPlusTreeException(e);
	}

	return retVal;
}


Node *BPlusTree::getNode(const unsigned int nodeNumber)
{
	Node* node = NULL;

	Block* block = file.getBlock(nodeNumber);

	if (block!=NULL)
	{
		unsigned int nodeNumber = block->getBlockNumber();
		unsigned int level = Node::readLevel(*block);

		if (level == Node::LEAF_LEVEL)
		{
			node = new LeafNode(nodeNumber,block,m_typeData,this);
		}
		else
		{
			node = new InnerNode(nodeNumber,level,block,m_typeData,this);
		}
	}

	return node;
}

void BPlusTree::saveNode(Node* node)
{
	Block* block = node->getBlock();

	file.saveBlock(block);
}

InnerNode* BPlusTree::newInnerNode(unsigned int level)
{
	Block* block = file.getNewBlock();
	unsigned int nodeNumber = block->getBlockNumber();

	InnerNode* node = new InnerNode(nodeNumber,level,block,m_typeData,this);

	return node;
}

LeafNode* BPlusTree::newLeafNode()
{
	Block* block = file.getNewBlock();
	unsigned int nodeNumber = block->getBlockNumber();

	LeafNode* node = new LeafNode(nodeNumber,block,m_typeData,this);

	return node;
}

void BPlusTree::deleteNode(Node* node) throw (BPlusTreeException)
{
	if (node == NULL)
		throw BPlusTreeException(BPlusTreeException::DELETED_FREENODE);

	unsigned int nodeNumber = node->getNodeNumber();

	file.deleteBlock(nodeNumber);

	delete node;

}



void BPlusTree::showTree(InputData& data){

	this->m_root->show(data);

};

void BPlusTree::deleteTree()
{
	file.deleteFile();
}

bool BPlusTree::modifyElement(const InputData & dato, const InputData & dato2) throw (BPlusTreeException){
	bool retVal = true;
	INodeData promotedKey;
	this->m_root->modify(dato,dato2,promotedKey);
	return retVal;
}

bool BPlusTree::find(const InputData & key, InputData & data)throw(BPlusTreeException){

	bool retVal=true;
	if(this->m_root->find(key,data)){
		cout<<endl<<"Elemento encontrado:"<<endl;
	}else{
		cout<<endl<<"No se encontro el elemento, se devuelve el de clave mayor:"<<endl;
	};

	cout<<"Clave: "<<data.getKey()<<endl;
	cout<<"Dato: "<<data.getValue()<<endl;
	return retVal;

}

