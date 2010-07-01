/*
 * LeafNode.cpp
 *
 *  Created on: 17/04/2010
 *      Author: matias
 */

#include "LeafNode.h"

LeafNode::LeafNode(unsigned int nodeNumber,Block* block)
:Node(nodeNumber,Node::LEAF_LEVEL,block)
{
	m_block->setFixedRegisterCount(3);

	if (m_block->getRegisterAmount()<3)
		{

		VarRegister prevPointer,nextPointer;

		prevPointer.setValue(UNDEFINED_NODE_NUMBER);
		nextPointer.setValue(UNDEFINED_NODE_NUMBER);

		m_block->addRegister(prevPointer);
		m_block->addRegister(nextPointer);
		}
	m_block->getRegisterN(3);
}

LeafNode::LeafNode(unsigned int nodeNumber,Block* block,BPlusTree* pointerTree)
:Node(nodeNumber,Node::LEAF_LEVEL,block)
{
	m_tree = pointerTree;
	m_block->setFixedRegisterCount(3);
	if (m_block->getRegisterAmount()<3)
	{

		VarRegister prevPointer,nextPointer;

		prevPointer.setValue(UNDEFINED_NODE_NUMBER);
		nextPointer.setValue(UNDEFINED_NODE_NUMBER);

		m_block->addRegister(prevPointer);
		m_block->addRegister(nextPointer);
	}
	m_block->getRegisterN(3);
}


LeafNode::~LeafNode()
{
}


loadResultEnum LeafNode::insert(const InputData& data,INodeData& promotedKey)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	InputData* currentData = data.newInstance();

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[data.size()];
	data.toStream(valueReg);
	VarRegister regData(valueReg,data.size());


	/// Busco donde insertar el dato dentro del bloque de hoja.
	m_block->restartCounter();

	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister pointerprev = m_block->getNextRegister();
	VarRegister pointernext = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un InputData
		currentValue = currentRegister.getValue();	// hace alloc
		currentData->toData(currentValue);
		if (currentData->getKey() >= data.getKey())
		{
			found = true;

			if (currentData->getKey() == data.getKey())
				throw NodeException(NodeException::DUPLICATED_IN_LEAF);
		}else
		/// Seria mejor que en Block me pudiera correr en uno: algo asi como it++
		/// con un metodo.
		m_block->getNextRegister();

		delete[] currentValue;
	}

	unsigned int pos = m_block->getPosActual();
	/// Lo agrega al final si no lo encontro
	m_block->addRegister(regData,result);

	if (result == OVERFLOW_LOAD)
	{
		split(data,pos,promotedKey);

		//Actualiza puntero a anterior delque antes estaba a su derecha.
		if(this->getNextLeaf()!=UNDEFINED_NODE_NUMBER){
			LeafNode* formerSibling=(LeafNode*)this->m_tree->getNode(this->getNextLeaf());
			formerSibling->setPreviousLeaf(promotedKey.getLeftPointer());
			this->m_tree->saveNode(formerSibling);

			if (formerSibling!=m_tree->getCurrent())
			{
				delete formerSibling;
				formerSibling = NULL;
			}
		};

		setNextLeaf(promotedKey.getLeftPointer());

	}

	delete[] valueReg;

	delete currentData;


	return result;
}


loadResultEnum LeafNode::remove(const InputData& data)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;
	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	InputData* currentData = data.newInstance();

	/// Busco el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister prevPointer = m_block->getNextRegister();
	VarRegister nextPointer = m_block->getNextRegister();


	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un InputData
		currentValue = currentRegister.getValue();
		currentData->toData(currentValue);
		if (currentData->getKey() == data.getKey())
		{
			found = true;
			m_block->deleteRegister(result);
		}
		m_block->getNextRegister();
		delete[] currentValue;
	}

	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMLEAF);

	delete currentData;

	return result;
}

loadResultEnum LeafNode::modify(const InputData & dato, const InputData & newdata,INodeData& promotedKey)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;
	bool found = false;

	// Deberian ser sobre la misma clave.
	if (dato.getKey() != newdata.getKey())
		throw NodeException(NodeException::BAD_CALL_OPERATION);

	char* currentValue = NULL;
	VarRegister currentRegister;
	InputData* currentData = newdata.newInstance();

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[newdata.size()];
	newdata.toStream(valueReg);
	VarRegister regNuevo(valueReg,newdata.size());

	/// Busco el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister prevPointer = m_block->getNextRegister();
	VarRegister nextPointer = m_block->getNextRegister();

	currentRegister = m_block->peekRegister();

	while (!m_block->isLastRegister()&&!found)
	{

		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un InputData
		currentValue = currentRegister.getValue();
		currentData->toData(currentValue);
		if (currentData->getKey() == newdata.getKey())
		{
			found = true;
			m_block->modifyRegister(regNuevo,result);

		}
		else
			m_block->getNextRegister();

		delete[] currentValue;
	}

	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMLEAF);

	unsigned int pos = m_block->getPosActual();

	if (result == OVERFLOW_LOAD)
		{	this->remove(newdata);
			split(newdata,pos,promotedKey);
			//Actualiza puntero a anterior delque antes estaba a su derecha.
			if(this->getNextLeaf()!=UNDEFINED_NODE_NUMBER){
				LeafNode* formerSibling=(LeafNode*)this->m_tree->getNode(this->getNextLeaf());
				formerSibling->setPreviousLeaf(promotedKey.getLeftPointer());
				this->m_tree->saveNode(formerSibling);

				if (formerSibling!=m_tree->getCurrent())
				{
					delete formerSibling;
					formerSibling = NULL;
				}
			};
			setNextLeaf(promotedKey.getLeftPointer());
		}

	delete[] valueReg;

	delete currentData;

	return result;
}

loadResultEnum LeafNode::modify(const InputData & data)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;
	bool found = false;

	VarRegister currentRegister;
	InputData* currentData = data.newInstance();

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[data.size()];
	data.toStream(valueReg);
	VarRegister regNuevo(valueReg,data.size());

	/// Busco el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister prevPointer = m_block->getNextRegister();
	VarRegister nextPointer = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() == data.getKey())
		{
			found = true;
			m_block->modifyRegister(regNuevo,result);
		}
		m_block->getNextRegister();
	}

	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMLEAF);

	delete currentData;

	return result;
}


bool LeafNode::find(std::string key,InputData & data)
throw (NodeException)
{
	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	InputData* currentData = data.newInstance();

	bool keyFound=false;
	/// Busco el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister prevPointer = m_block->getNextRegister();
	VarRegister nextPointer = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->getNextRegister();
		currentValue = currentRegister.getValue();
		/// Transformo el registro a un InputData
		currentData->toData(currentValue);
		if (currentData->getKey() >= key)
		{
			found = true;

			if (currentData->getKey() == key)
				keyFound=true;
//			if (data.size() < currentData->size())
//			{
				data.setKey(currentData->getKey());
				data.setValue(currentData->getValue());
//			}
//			else
//				throw NodeException(NodeException::INSUFFICIENT_ALLOCK_PARAM);
		}

		delete[] currentValue;

	}
	//Si llega al final del nodo sin encontrar el elemento o uno de clave mayor,
	//devuelve el de clave mas grande del nodo
	if(!found){
		data.setKey(currentData->getKey());
		data.setValue(currentData->getValue());
	};

	m_tree->setCurrent(this);

	delete currentData;

	return keyFound;
}

bool LeafNode::split(const InputData& data,unsigned int pos,INodeData& promotedKey)
{
	LeafNode* sibling = (LeafNode*)m_tree->newLeafNode();
	Block* blockSibling = sibling->getBlock();

	char* valueReg = new char[data.size()];
	data.toStream(valueReg);
	VarRegister reg(valueReg,data.size());

	BlockManager::redistributeOverflow(m_block,blockSibling,reg,pos);
	delete[] valueReg;


	blockSibling->restartCounter();

	///Saltea datos de control.
	blockSibling->getNextRegister();
	blockSibling->getNextRegister();
	blockSibling->getNextRegister();

	//Recupera el primer registro de datos.
	reg = blockSibling->getNextRegister();

	InputData* firstKey = data.newInstance();
	valueReg = reg.getValue(); //hace alloc
	firstKey->toData(valueReg);

	// Obtiene la primer clave del sibling derecho y su numero de nodo.
	promotedKey.setKey(firstKey->getKey());
	promotedKey.setLeftPointer(sibling->getNodeNumber());

	sibling->setPreviousLeaf(this->getNodeNumber());
	sibling->setNextLeaf(this->getNextLeaf());

	m_tree->saveNode(sibling);

	delete firstKey;

	if (sibling!=m_tree->getCurrent())
	{
		delete sibling;
		sibling = NULL;
	}

	delete[] valueReg;

	return true;
}


void LeafNode::printContent()
{
	StringInputData data;
	VarRegister varR;
	char* valueReg = NULL;
	unsigned int dataAmmount;
	unsigned int i=0;

	m_block->restartCounter();
	dataAmmount = m_block->getRegisterAmount();

	cout << "\t Numero nodo: " << getNodeNumber();
	varR = m_block->getNextRegister(true);
	valueReg = varR.getValue(); //hace alloc
	cout << "\t Nivel: "<<ByteConverter::bytesToUInt(valueReg);
	delete[] valueReg;

	varR = m_block->getNextRegister(true);
	valueReg = varR.getValue();//hace alloc
	cout << "\t Nodo anterior: "<< ByteConverter::bytesToInt(valueReg);
	delete[] valueReg;

	varR = m_block->getNextRegister(true);
	valueReg = varR.getValue();//hace alloc
	cout << "\t Nodo siguiente: "<< ByteConverter::bytesToInt(valueReg);
	delete[] valueReg;

	cout << "\n Datos "<<endl;

	i = m_block->getPosActual();

	for(i = i; i < dataAmmount; i++)
	{
		varR = m_block->getNextRegister(true);
		valueReg = varR.getValue();
		data.toData(valueReg);
		cout<< "Clave:"<<data.getKey()<<" Datos:"<<data.getValue()<<endl;
		delete [] valueReg;
	}


}


unsigned int LeafNode::getNextLeaf()
{
	unsigned int nextLeaf = UNDEFINED_NODE_NUMBER;

	m_block->restartCounter();
	m_block->getNextRegister();

	VarRegister prevReg,nextReg;
	prevReg = m_block->getNextRegister();
	nextReg = m_block->getNextRegister();

	char* valueReg = nextReg.getValue();

	nextLeaf = ByteConverter::bytesToUInt(valueReg);

	delete [] valueReg;

	return nextLeaf;
}

unsigned int LeafNode::getPreviousLeaf()
{
	unsigned int prevLeaf = UNDEFINED_NODE_NUMBER;

	m_block->restartCounter();
	m_block->getNextRegister();

	VarRegister prevReg,nextReg;
	prevReg = m_block->getNextRegister();
	nextReg = m_block->getNextRegister();

	char* valueReg = prevReg.getValue();

	prevLeaf = ByteConverter::bytesToUInt(valueReg);

	delete[] valueReg;

	return prevLeaf;
}

unsigned int LeafNode::setNextLeaf(unsigned int nodeNumber)
{
	unsigned int nextleaf = Node::UNDEFINED_NODE_NUMBER;

	m_block->restartCounter();

	m_block->getNextRegister();
	m_block->getNextRegister();

	VarRegister reg;

	reg.setValue(nodeNumber);

	m_block->modifyRegister(reg);


	return nextleaf;
}


unsigned int LeafNode::setPreviousLeaf(unsigned int nodeNumber)
{
	unsigned int prevleaf = Node::UNDEFINED_NODE_NUMBER;

	m_block->restartCounter();

	m_block->getNextRegister();

	VarRegister reg;

	reg.setValue(nodeNumber);

	m_block->modifyRegister(reg);

	return prevleaf;
}

void LeafNode::show(){

	this->printContent();


}

bool LeafNode::getNextData(InputData& data)
{
	bool retVal = false;

	VarRegister reg;
	char* currentValue = NULL;
	InputData* currentData = data.newInstance();


	if (!m_block->isLastRegister())
	{
		reg = m_block->getNextRegister();
		currentValue = reg.getValue();
		currentData->toData(currentValue);

		data.setKey(currentData->getKey());
		data.setValue(currentData->getValue());

		delete[] currentValue;

		retVal = true;
	}

	delete currentData;

	return retVal;
}

bool LeafNode::getPreviousData(InputData& data)
{
	bool retVal = false;

	VarRegister reg;
	char* currentValue = NULL;
	InputData* currentData = data.newInstance();


	if (m_block->getPosActual()!=3)
	{
		reg = m_block->getPreviousRegister();
		currentValue = reg.getValue();
		currentData->toData(currentValue);

		data.setKey(currentData->getKey());
		data.setValue(currentData->getValue());

		delete[] currentValue;

		retVal = true;
	}

	delete currentData;

	return retVal;
}

bool LeafNode::getFirstData(InputData & data){
	char* currentValue = NULL;
		VarRegister currentRegister;
		InputData* currentData = data.newInstance();
		/// Busco el primer dato dentro del bloque de hoja.
		m_block->restartCounter();
		/// Tengo que avanzar primero los datos de control siempre.
		/// TODO ver si poner esto dentro de un metodo de Nodo.
		VarRegister level = m_block->getNextRegister();
		VarRegister prevPointer = m_block->getNextRegister();
		VarRegister nextPointer = m_block->getNextRegister();

		currentRegister = m_block->getNextRegister();
		currentValue = currentRegister.getValue();
		/// Transformo el registro a un InputData
		currentData->toData(currentValue);
		data.setKey(currentData->getKey());
		data.setValue(currentData->getValue());
		m_block->isLastRegister();
		delete[] currentValue;
		m_tree->setCurrent(this);
		delete currentData;

		return true;

};
