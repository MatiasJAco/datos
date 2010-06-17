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

	m_currentNode = NULL;

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

	m_currentNode = NULL;
}

BPlusTree::~BPlusTree()
{
	file.close();

	if (m_root!=NULL)
		delete m_root;

	if (m_currentNode!=NULL)
		delete m_currentNode;
}

bool BPlusTree::insert(std::string clave, std::string valor)
throw (ManagerException)
{
	StringInputData data;
	data.setKey(clave);
	data.setValue(valor);

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

		sucesor->setNodeNumber(sucesor->getNodeNumber());
		m_root->setNodeNumber(m_root->getNodeNumber());



		INodeData firstKey;
		INodeData newKey;


		if (!sucesor->isLeaf()){

			INodeData currentData;
			VarRegister reg;
			char* valueReg = NULL;

			Node* nodoIzquierdo = this->getNode(promotedKey.getLeftPointer());
			Block* bloqueIzquierdo = nodoIzquierdo->getBlock();

			while(!nodoIzquierdo->isLeaf()){
			//Obtener primer clave de la rama.

				//Salteo info de control.
				bloqueIzquierdo->restartCounter();
				bloqueIzquierdo->getNextRegister();

				reg = bloqueIzquierdo->getNextRegister();
				valueReg = reg.getValue();	//hace alloc
				currentData.toNodeData(valueReg);

				delete nodoIzquierdo;
				nodoIzquierdo = this->getNode(currentData.getLeftPointer());
				bloqueIzquierdo = nodoIzquierdo->getBlock();

				delete[] valueReg;
			}

			//Encuentro la primer hoja de la segunda rama.
			bloqueIzquierdo = nodoIzquierdo->getBlock();

			//Salteo info de control.
			bloqueIzquierdo->restartCounter();
			bloqueIzquierdo->getNextRegister();
			bloqueIzquierdo->getNextRegister();
			bloqueIzquierdo->getNextRegister();
			reg = bloqueIzquierdo->getNextRegister();

			InputData* leftKey = data.newInstance();
			valueReg = reg.getValue();
			leftKey->toData(valueReg);
			promotedKey.setKey(leftKey->getKey());
			delete leftKey;


			if (nodoIzquierdo!=NULL)
				delete nodoIzquierdo;

			if (valueReg!=NULL)
				delete[] valueReg;

		}

		firstKey.setLeftPointer(sucesor->getNodeNumber());
		firstKey.setKey(promotedKey.getKey());
		newKey.setLeftPointer(promotedKey.getLeftPointer());


		newKey.setKey(INodeData::UNDEFINED_KEY);



		// habria que hacer casteo dinamico.
		result = ((InnerNode*)m_root)->insertINodeData(firstKey,promotedKey);
		result = ((InnerNode*)m_root)->insertINodeData(newKey,promotedKey);

		saveNode(sucesor);

		if (sucesor->isLeaf()){
		//Actualiza puntero izquierdo del nodo surgido en overflow.
		LeafNode* nodoDerecho = (LeafNode*)this->getNode(newKey.getLeftPointer());
		nodoDerecho->setPreviousLeaf(sucesor->getNodeNumber());
		saveNode(nodoDerecho);
		delete nodoDerecho;
		};

		delete sucesor;

		// La raiz esta insertando el minimo de claves, no puede ser overflow.
		if (result == OVERFLOW_LOAD)
			throw NodeException(NodeException::ANOMALOUS_LOADRESULT);

	}

	saveNode(m_root);

	return retVal;
}

bool BPlusTree::remove(std::string clave) throw (ManagerException)
{
	StringInputData data;
	data.setKey(clave);
	data.setValue("");

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

	if((this->m_root->getBlock()->getRegisterAmount()==2)&&(!this->m_root->isLeaf())){

		INodeData currentData;
		VarRegister currentRegister;
		char* currentValue = NULL;

		unsigned int currentLevel = this->m_root->getLevel();

		//Obtengo el unico hijo
		Block* rootBlock = this->m_root->getBlock();
		rootBlock->restartCounter();
		//Salteo datos de control.
		rootBlock->getNextRegister();

		currentRegister =  rootBlock->getNextRegister();
		currentValue = currentRegister.getValue();
		currentData.toNodeData(currentValue);

		Node* sucesor = this->getNode(currentData.getLeftPointer());
		Block* blockSucesor = sucesor->getBlock();

		//Cambio los numeros de bloque.
		BlockManager::exchangeBlock(rootBlock,blockSucesor);

		//Intercambio los punteros
		Node* auxPointer;
		auxPointer = m_root;
		m_root = sucesor;
		sucesor = auxPointer;

		this->deleteNode(sucesor);
		m_root->setLevel(currentLevel-1);


		delete auxPointer;
		delete [] currentValue;

	}

	this->saveNode(m_root);

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

//	delete node;

}



void BPlusTree::showTree(InputData& data){

	this->m_root->show(data);

};

void BPlusTree::deleteTree()
{
	file.deleteFile();
}

bool BPlusTree::modify(const InputData & dato, const InputData & dato2) throw (ManagerException){
	bool retVal = true;
	INodeData promotedKey;
	unsigned int level = Node::UNDEFINED_NODE_LEVEL;
	loadResultEnum result = NORMAL_LOAD;
	try
	{
	result=this->m_root->modify(dato,dato2,promotedKey);
	}
	catch (NodeException e)
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
			sucesor->setNodeNumber(sucesor->getNodeNumber());
			m_root->setNodeNumber(m_root->getNodeNumber());

			INodeData firstKey;
			INodeData newKey;

			if (!sucesor->isLeaf()){
				INodeData currentData;

				char* valueReg = NULL;
				VarRegister reg;
				Node* nodoIzquierdo= this->getNode(promotedKey.getLeftPointer());
				Block* bloqueIzquierdo = nodoIzquierdo->getBlock();

				while(!nodoIzquierdo->isLeaf()){
				//Obtener primer clave de la rama.
					//Salteo info de control.
					bloqueIzquierdo->restartCounter();
					bloqueIzquierdo->getNextRegister();
					reg = bloqueIzquierdo->getNextRegister();

					valueReg = reg.getValue();
					currentData.toNodeData(valueReg);

					delete nodoIzquierdo;
					nodoIzquierdo = this->getNode(currentData.getLeftPointer());
					bloqueIzquierdo = nodoIzquierdo->getBlock();

					delete[] valueReg;
				}

				InputData* leftKey = dato.newInstance();
				//Encuentro la primer hoja de la segunda rama.
				bloqueIzquierdo = nodoIzquierdo->getBlock();
				//Salteo info de control.
				bloqueIzquierdo->restartCounter();
				bloqueIzquierdo->getNextRegister();
				bloqueIzquierdo->getNextRegister();
				bloqueIzquierdo->getNextRegister();

				reg = bloqueIzquierdo->getNextRegister();
				valueReg = reg.getValue();
				leftKey->toData(valueReg);
				promotedKey.setKey(leftKey->getKey());

				delete leftKey;


				if (nodoIzquierdo!=NULL)
					delete nodoIzquierdo;

				if (valueReg!=NULL)
					delete[] valueReg;

			}
			firstKey.setLeftPointer(sucesor->getNodeNumber());
			firstKey.setKey(promotedKey.getKey());
			newKey.setLeftPointer(promotedKey.getLeftPointer());


			newKey.setKey(INodeData::UNDEFINED_KEY);


			// habria que hacer casteo dinamico.
			result = ((InnerNode*)m_root)->insertINodeData(firstKey,promotedKey);
			result = ((InnerNode*)m_root)->insertINodeData(newKey,promotedKey);

			saveNode(sucesor);
			delete sucesor;

			// La raiz esta insertando el minimo de claves, no puede ser overflow.
			if (result == OVERFLOW_LOAD)
				throw NodeException(NodeException::ANOMALOUS_LOADRESULT);
		}

	if((this->m_root->getBlock()->getRegisterAmount()==2)&&(!this->m_root->isLeaf())){

		INodeData currentData;
		char* currentValue = NULL;
		unsigned int currentLevel= this->m_root->getLevel();

		//Obtengo el unico hijo
		Block* rootBlock= this->m_root->getBlock();
		rootBlock->restartCounter();

		//Salteo datos de control.
		rootBlock->getNextRegister();
		VarRegister currentRegister;

		currentRegister = rootBlock->getNextRegister();
		currentValue = currentRegister.getValue();
		currentData.toNodeData(currentValue);

		Node* sucesor = this->getNode(currentData.getLeftPointer());
		Block* blockSucesor = sucesor->getBlock();
		//Cambio los numeros de bloque.
		BlockManager::exchangeBlock(rootBlock,blockSucesor);

		//Intercambio los punteros
		Node* auxPointer;
		auxPointer = m_root;
		m_root = sucesor;
		sucesor = auxPointer;

		this->deleteNode(sucesor);
		m_root->setLevel(currentLevel-1);

		delete auxPointer;
		delete[] currentValue;

	}

	saveNode(m_root);

	return retVal;

}

bool BPlusTree::find(const InputData & key, InputData & data)throw(ManagerException){

	bool retVal = true;

	try
	{
		retVal = m_root->find(key,data);
	}
	catch(NodeException e)
	{
		throw BPlusTreeException(e);
	}

	return retVal;
}

bool BPlusTree::getNext(InputData& data)
{
	bool retVal = false;

	unsigned int nodeNumber = Node::UNDEFINED_NODE_NUMBER;

	if (m_currentNode!=NULL)
	{
		// Obtiene el dato actual.
		retVal = m_currentNode->getNextData(data);

		// Si ya no tiene mas para leer de la propia hoja, sigue en la siguiente.
		if (!retVal)
		{
			nodeNumber = m_currentNode->getNextLeaf();

			if (nodeNumber!=Node::UNDEFINED_NODE_NUMBER )
			{
				delete m_currentNode;

				m_currentNode = (LeafNode*)getNode(nodeNumber);

				// Leo de la hoja.
				retVal = m_currentNode->getNextData(data);
			}
		}
	}

	return retVal;
}


void BPlusTree::setCurrent(LeafNode* node)
{
	m_currentNode = node;
}

