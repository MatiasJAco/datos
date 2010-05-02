/*
 * LeafNode.cpp
 *
 *  Created on: 17/04/2010
 *      Author: matias
 */

#include "LeafNode.h"

LeafNode::LeafNode(unsigned int nodeNumber,Block* block,const InputData& typeData)
:Node(nodeNumber,Node::LEAF_LEVEL,block,typeData)
{
	if (m_block->getRegisterAmount()<3)
		{
		VarRegister prevPointer,nextPointer;

		prevPointer.setValue(UNDEFINED_NODE_NUMBER);
		nextPointer.setValue(UNDEFINED_NODE_NUMBER);

		m_block->addRegister(prevPointer);
		m_block->addRegister(nextPointer);
		}
}

LeafNode::LeafNode(unsigned int nodeNumber,Block* block,const InputData& typeData,BPlusTree* pointerTree)
:Node(nodeNumber,Node::LEAF_LEVEL,block,typeData)
{
	m_tree = pointerTree;

	if (m_block->getRegisterAmount()<3)
	{
		VarRegister prevPointer,nextPointer;

		prevPointer.setValue(UNDEFINED_NODE_NUMBER);
		nextPointer.setValue(UNDEFINED_NODE_NUMBER);

		m_block->addRegister(prevPointer);
		m_block->addRegister(nextPointer);
	}
}


LeafNode::~LeafNode()
{
}


loadResultEnum LeafNode::insert(const InputData& data,INodeData& promotedKey)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	VarRegister currentRegister;
	InputData* currentData = data.newInstance();

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[data.size()];
	VarRegister regData(data.toStream(valueReg),data.size());

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
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() >= data.getKey())
		{
			found = true;

			if (currentData->getKey() == data.getKey())
				throw NodeException(NodeException::DUPLICATED_IN_LEAF);
		}else
		/// Seria mejor que en Block me pudiera correr en uno: algo asi como it++
		/// con un metodo.
		m_block->getNextRegister();
	}

	unsigned int pos = m_block->getPosActual();
	/// Lo agrega al final si no lo encontro
	m_block->addRegister(regData,result);

	if (result == OVERFLOW_LOAD)
	{
		split(data,pos,promotedKey);
		setNextLeaf(promotedKey.getLeftPointer());
	}

	m_tree->saveNode(this);

	return result;
}


loadResultEnum LeafNode::remove(const InputData& data)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;
	bool found = false;

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
		currentRegister = m_block->getNextRegister();

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() == data.getKey())
		{
			found = true;
			m_block->deleteRegister(result);
		}
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

	VarRegister currentRegister;
	InputData* currentData = newdata.newInstance();

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[newdata.size()];
	VarRegister regNuevo(newdata.toStream(valueReg),newdata.size());

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

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() == newdata.getKey())
		{
			found = true;
			m_block->modifyRegister(regNuevo,result);
		}
	}

	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMLEAF);

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
	VarRegister regNuevo(data.toStream(valueReg),data.size());

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

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() == data.getKey())
		{
			found = true;
			m_block->modifyRegister(regNuevo,result);
		}
	}

	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMLEAF);

	delete currentData;

	return result;
}


bool LeafNode::find(const InputData & key,InputData & data)
throw (NodeException)
{
	bool found = false;

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
		currentRegister = m_block->getNextRegister();

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() == key.getKey())
		{
			found = true;

			if (data.size() > currentData->size())
			{
				data.setKey(currentData->getKey());
				data.setValue(currentData->getValue());
			}
			else
				throw NodeException(NodeException::INSUFFICIENT_ALLOCK_PARAM);
		}
	}

	delete currentData;

	return found;
}

bool LeafNode::split(const InputData& data,unsigned int pos,INodeData& promotedKey)
{
	LeafNode* sibling = (LeafNode*)m_tree->newLeafNode();
	Block* blockSibling = sibling->getBlock();

	char* valueReg = new char[data.size()];
	data.toStream(valueReg);
	VarRegister reg(valueReg,data.size());

	BlockManager::redistributeOverflow(m_block,blockSibling,reg,pos);

	blockSibling->restartCounter();

	///Saltea datos de control.
	blockSibling->getNextRegister();
	blockSibling->getNextRegister();
	blockSibling->getNextRegister();

	//Recupera el primer registro de datos.
	reg = blockSibling->getNextRegister();

	InputData* firstKey = data.newInstance();
	firstKey->toData(reg.getValue());

	// Obtiene la primer clave del sibling derecho y su numero de nodo.
	promotedKey.setKey(firstKey->getKey());
	promotedKey.setLeftPointer(sibling->getNodeNumber());

	sibling->setPreviousLeaf(this->getNodeNumber());

	m_tree->saveNode(sibling);

	return true;
}


void LeafNode::printContent(InputData& data)
{
	VarRegister varR;
	unsigned int dataAmmount;
	unsigned int i=0;

	m_block->restartCounter();
	dataAmmount = m_block->getRegisterAmount();

	cout << "\t Numero nodo: " << getNodeNumber();
	varR = m_block->getNextRegister(true);
	cout << "\t Nivel: "<<ByteConverter::bytesToUInt(varR.getValue());
	varR = m_block->getNextRegister(true);
	cout << "\t Nodo anterior: "<< ByteConverter::bytesToInt(varR.getValue());
	varR = m_block->getNextRegister(true);
	cout << "\t Nodo siguiente: "<< ByteConverter::bytesToInt(varR.getValue());
	cout << "\n Datos "<<endl;

	i = m_block->getPosActual();

	for(i = i; i < dataAmmount; i++)
	{
		varR = m_block->getNextRegister(true);
		data.toData(varR.getValue());
		cout<< "Clave:"<<data.getKey()<<" Datos:"<<data.getValue()<<endl;
	}


}

std::string LeafNode::toStringData(InputData & typedata)
{
	std::string retStr = "";

	VarRegister varR;
	unsigned int dataAmmount;
	unsigned int i = 0;

	m_block->restartCounter();
	dataAmmount = m_block->getRegisterAmount();

	varR = m_block->getNextRegister(true);
	retStr+= "\t Nivel: "+ ByteConverter::bytesToUInt(varR.getValue());
	varR = m_block->getNextRegister(true);
	retStr += "\t Nodo anterior: " + ByteConverter::bytesToInt(varR.getValue());
	varR = m_block->getNextRegister(true);
	retStr += "\t Nodo siguiente: "+ ByteConverter::bytesToInt(varR.getValue());
	retStr +=  "\n Datos \n";

	i = m_block->getPosActual();

	for(i = i; i < dataAmmount; i++)
	{
		varR = m_block->getNextRegister(true);
		typedata.toData(varR.getValue());
		retStr+= typedata.toString();
	}

	return retStr;
}


unsigned int LeafNode::getNextLeaf()
{
	unsigned int nextLeaf = UNDEFINED_NODE_NUMBER;

	m_block->restartCounter();
	m_block->getNextRegister();

	VarRegister prevReg,nextReg;
	prevReg = m_block->getNextRegister();
	nextReg = m_block->getNextRegister();

	nextLeaf = ByteConverter::bytesToUInt(nextReg.getValue());

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

	prevLeaf = ByteConverter::bytesToUInt(prevReg.getValue());

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

void LeafNode::show(InputData &data){

	this->printContent(data);


}
