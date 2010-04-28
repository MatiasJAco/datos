/*
 * LeafNode.cpp
 *
 *  Created on: 17/04/2010
 *      Author: matias
 */

#include "LeafNode.h"

LeafNode::LeafNode()
{
}

LeafNode::LeafNode(unsigned int nodeNumber)
:Node(nodeNumber)
{
}

LeafNode::LeafNode(unsigned int nodeNumber,Block* block,BPlusTree* pointerTree)
//:Node(nodeNumber,Node::LEAF_LEVEL,block,pointerTree)
:Node(nodeNumber,Node::LEAF_LEVEL,block)
{
	m_tree = pointerTree;

	VarRegister prevPointer,nextPointer;

	prevPointer.setValue(UNDEFINED_NODE_NUMBER);
	nextPointer.setValue(UNDEFINED_NODE_NUMBER);

	m_block->addRegister(prevPointer);
	m_block->addRegister(nextPointer);
}


LeafNode::~LeafNode()
{
}


INodeData*  LeafNode::insert(const InputData & dato,loadResultEnum& result)
{
	result = NORMAL_LOAD;
	bool found = false;

	VarRegister currentRegister;
	InputData* currentData = dato.newInstance();

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[dato.size()];
	VarRegister regData(dato.toStream(valueReg),dato.size());

	/// Busco donde insertar el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister pointers = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() >= dato.getKey())
		{
			found = true;

			if (currentData->getKey() == dato.getKey())
				throw "Duplicado en insert de Hoja";
		}
		/// Seria mejor que en Block me pudiera correr en uno: algo asi como it++
		/// con un metodo.
		currentRegister = m_block->getNextRegister();
	}
	/// Lo agrega al final si no lo encontro
	m_block->addRegister(regData,result);

//	if (result == OVERFLOW_LOAD)
//		split(promotedKey);


	delete currentData;

//	return promotedKey;

	return new INodeData(0,0);
}

loadResultEnum LeafNode::remove(const InputData & dato)
{
	loadResultEnum result = NORMAL_LOAD;
	bool found = false;

	VarRegister currentRegister;
	InputData* currentData = dato.newInstance();

	/// Busco el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister pointers = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->getNextRegister();

		/// Transformo el registro a un InputData
		currentData->toData(currentRegister.getValue());
		if (currentData->getKey() == dato.getKey())
		{
			found = true;
			m_block->deleteRegister(result);
		}
	}

	if (!found)
		throw "No existe el elemento a remover";

	delete currentData;

	return result;
}

loadResultEnum LeafNode::modify(const InputData & dato, const InputData & newdata)
{
	loadResultEnum result = NORMAL_LOAD;
	bool found = false;


	if (dato.getKey() != newdata.getKey())
		throw "La modificacion es sobre un elemento con la misma clave!";

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
	VarRegister pointers = m_block->getNextRegister();

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
		throw "No existe el elemento a modificar";

	delete currentData;

	return result;
}

loadResultEnum LeafNode::modify(const InputData & data)
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
	VarRegister pointers = m_block->getNextRegister();

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
		throw "No existe el elemento a modificar";

	delete currentData;

	return result;
}


bool LeafNode::find(const InputData & key,InputData & data) const
{
	bool found = false;

	VarRegister currentRegister;
	InputData* currentData = data.newInstance();

	/// Busco el dato dentro del bloque de hoja.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
	VarRegister pointers = m_block->getNextRegister();

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
				throw "Espacio insuficiente para guardar el dato buscado";
		}
	}

	delete currentData;

	return found;
}

bool LeafNode::split_(INodeData& promotedKey)
{
//	LeafNode* sibling = m_tree->newLeafNode();
//	Block* blockSibling = sibling->getBlock();


//	BlockManager::redistributeOverflow(m_block,blockSibling,reg,posicion);

	return true;
}


void LeafNode::printContent(InputData & data)
{
	VarRegister varR;
	unsigned int dataAmmount;
	unsigned int i=0;

	m_block->restartCounter();
	dataAmmount = m_block->getRegisterAmount();

	varR = m_block->getNextRegister(true);
	cout << "Nivel: "<<ByteConverter::bytesToUInt(varR.getValue());
	cout << "Datos "<<endl;

	for(i=1; i < dataAmmount; i++)
	{
		varR = m_block->getNextRegister(true);
		data.toData(varR.getValue());
		cout<< "Clave:"<<data.getKey()<<" Datos:"<<data.getValue()<<endl;
	}


}



unsigned int LeafNode::getNext()
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

unsigned int LeafNode::getPrevious()
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

