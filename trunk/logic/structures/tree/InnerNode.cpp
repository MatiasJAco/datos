/**
 * @file InnerNode.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "InnerNode.h"
#include <sstream>
using namespace std;


InnerNode::InnerNode(unsigned int nodeNumber, unsigned int level, Block *block)
:Node(nodeNumber,level,block)
{
	m_block->setFixedRegisterCount(1);
}

InnerNode::InnerNode(unsigned int nodeNumber,unsigned int level,Block* block,BPlusTree* pointerTree)
//:Node(nodeNumber,level,block,pointerTree)
:Node(nodeNumber,level,block)
{
	m_block->setFixedRegisterCount(1);
	m_tree = pointerTree;
	m_block->getRegisterN(1);
}

InnerNode::~InnerNode()
{
}

loadResultEnum InnerNode::modify(const InputData & dato, const InputData & newData,INodeData& promotedKey)
throw (NodeException)
{

	loadResultEnum result = NORMAL_LOAD;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData thiskey(Node::UNDEFINED_NODE_NUMBER,dato.getKey());

	// Busco el elemento de nodo interno que contiene la referencia a la clave de dato.
	INodeData refkey;
	if (!findINodeData(thiskey,refkey,BIGGER))
		throw NodeException(NodeException::INVALID_REF);

	// Se lo pide al arbol
	Node* sucesor = m_tree->getNode(refkey.getLeftPointer());

	try{
		result = sucesor->modify(dato,newData,promotedKey);
	}
	catch(NodeException e)
	{
		throw;
	}


	if (result==OVERFLOW_LOAD){
		// Busca el INodeData mayor al promotedKey y es seteada dentro de la misma.

		// Hace el intercambio de claves y punteros. Modifica el puntero de bigger
		INodeData bigger(UNDEFINED_NODE_NUMBER,promotedKey.getKey());
		findINodeData(promotedKey,bigger,BIGGER);
		//findINodeData(bigger,false);

		INodeData newINodeData(bigger.getLeftPointer(),promotedKey.getKey());
		bigger.setLeftPointer(promotedKey.getLeftPointer());

		modifyINodeData(bigger);

		/// Devuelve el resultado de haber insertado una clave,
		/// promoted Key es modificado despues del insert.
		result = insertINodeData(newINodeData,promotedKey);

	}

	if (result == UNDERFLOW_LOAD)
		{
			result = NORMAL_LOAD;
			bool hasRightBrother = false;
			bool hasMinorBrother = false;

			bool balanced = false;
			Node* sibling=NULL;

			INodeData keymodified;

			INodeData joinBrother;

			// busco el hermano mayor a key para obtener el hijo derecho.
			INodeData bigBrother;
			hasRightBrother = findINodeData(refkey,bigBrother,BIGGER);

			INodeData minorBrother;
			hasMinorBrother = findINodeData(refkey,minorBrother,MINOR);

			//Verifico que tenga hermano derecho.
			if(hasRightBrother)
			{
				// Trato de balancear con el derecho.
				// Al redistribuir me devuelve la clave que hay que promover y modificar en thiskey.
				sibling = m_tree->getNode(bigBrother.getLeftPointer());
				balanced = redistribute(sucesor,sibling,newData,keymodified,RIGHT_SIDE);
			}

			if (balanced)
				modifyINodeData(refkey,keymodified);

			// Si no pudo, busco el sibling izquierdo, el hijo del hermano menor.
			if (!balanced)
			{
				//Verifica que tenga hermano izquierdo.
				if (hasMinorBrother)
				{

					if (sibling!=NULL)
					delete sibling;

					sibling = m_tree->getNode(minorBrother.getLeftPointer());
					balanced = redistribute(sucesor,sibling,newData,keymodified,LEFT_SIDE);
				}

				if (balanced)
					modifyINodeData(minorBrother,keymodified);
			}

			// Si no pudo balancear, fusiona.
			if (!balanced)
			{
				INodeData fusionatedNode;

				if(hasRightBrother)
				{
					merge(sucesor,sibling,newData,fusionatedNode,RIGHT_SIDE);
					result = removeINodeData(refkey);
					//Recupero clave del que borro y se a paso al que queda.
					bigBrother.setLeftPointer(fusionatedNode.getLeftPointer());
					modifyINodeData(bigBrother);
				}
				else
				{
					merge(sibling,sucesor,newData,fusionatedNode,LEFT_SIDE);
					result = removeINodeData(minorBrother);
					refkey.setLeftPointer(fusionatedNode.getLeftPointer());
					modifyINodeData(refkey);
				}
				// En la fusion se elimina el sibling, permanece el que produjo el underflow.
				m_tree->deleteNode(sibling);
			}

			if (sibling!=NULL)
			{
				m_tree->saveNode(sibling);
				delete sibling;
			}
		}

	if (sucesor!=NULL)
	{
		m_tree->saveNode(sucesor);
		delete sucesor;
	}

	m_tree->saveNode(this);

	return result;
}

loadResultEnum InnerNode::modify(const InputData& data)
{
	return NORMAL_LOAD;
}


void InnerNode::save(Node* node)
{
	m_tree->saveNode(node);
}

/**********************************************************************************/

loadResultEnum InnerNode::insert(const InputData& data,INodeData& promotedKey)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData thiskey(Node::UNDEFINED_NODE_NUMBER,data.getKey());

	// Busco el elemento de nodo interno que contiene la referencia a la clave de dato.
	INodeData refkey;
	if (!findINodeData(thiskey,refkey,BIGGER))
		throw NodeException(NodeException::INVALID_REF);

	// Se lo pide al arbol
	Node* sucesor = this->m_tree->getNode(refkey.getLeftPointer());


	try
	{
		// Inserta en el hijo y regresa la clave a promover..
		result = sucesor->insert(data,promotedKey);
	}
	catch(NodeException e)
	{
		throw;
	}

	// Si hubo overflow tuvo que promover una clave.
	if (result == OVERFLOW_LOAD)
	{
		// Busca el INodeData mayor al promotedKey y es seteada dentro de la misma.

		// Hace el intercambio de claves y punteros. Modifica el puntero de bigger
		INodeData bigger;
		findINodeData(promotedKey,bigger,BIGGER);

		INodeData newINodeData(bigger.getLeftPointer(),promotedKey.getKey());
		bigger.setLeftPointer(promotedKey.getLeftPointer());

		modifyINodeData(bigger);

		/// Devuelve el resultado de haber insertado una clave,
		/// promoted Key es modificado despues del insert.
		try
		{
			result = insertINodeData(newINodeData,promotedKey);
		}
		catch(NodeException e)
		{
			throw;
		}
	}

	if (sucesor!=NULL)
	{
		m_tree->saveNode(sucesor);
		delete sucesor;
	}

	m_tree->saveNode(this);

	return result;
}

loadResultEnum InnerNode::remove(const InputData& data)
throw(NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	// Crea un INodeData con la clave que llega, para realizar la busqueda, por donde ir recorriendo.
	INodeData thiskey(UNDEFINED_NODE_NUMBER,data.getKey());

	// Busca el nodo interno que referencia a esa clave
	INodeData refkey;
	if (!findINodeData(thiskey,refkey,BIGGER))
		throw NodeException(NodeException::INVALID_REF);

	// traigo el sucesor de este innerNode y lo elimino.
	Node* sucesor = m_tree->getNode(refkey.getLeftPointer());

	try
	{
		result = sucesor->remove(data);
	}
	catch(NodeException e)
	{
		throw;
	}

	if (result == UNDERFLOW_LOAD)
	{	result=NORMAL_LOAD;
		bool hasRightBrother = false;
		bool hasMinorBrother = false;

		bool balanced = false;
		Node* sibling=NULL;

		INodeData keymodified;

		INodeData joinBrother;

		// busco el hermano mayor a key para obtener el hijo derecho.
		INodeData bigBrother;
		hasRightBrother = findINodeData(refkey,bigBrother,BIGGER);

		INodeData minorBrother;
		hasMinorBrother = findINodeData(refkey,minorBrother,MINOR);

		//Verifico que tenga hermano derecho.
		if(hasRightBrother)
		{
			// Trato de balancear con el derecho.
			// Al redistribuir me devuelve la clave que hay que promover y modificar en thiskey.
			sibling = m_tree->getNode(bigBrother.getLeftPointer());
			balanced = redistribute(sucesor,sibling,data,keymodified,RIGHT_SIDE);
		}

		if (balanced)
			modifyINodeData(refkey,keymodified);

		// Si no pudo, busco el sibling izquierdo, el hijo del hermano menor.
		if (!balanced)
		{
			//Verifica que tenga hermano izquierdo.
			if (hasMinorBrother)
			{

				if (sibling!=NULL)
					delete sibling;
				sibling = m_tree->getNode(minorBrother.getLeftPointer());
				balanced = redistribute(sucesor,sibling,data,keymodified,LEFT_SIDE);
			}

			if (balanced)
				modifyINodeData(minorBrother,keymodified);
		}

		// Si no pudo balancear, fusiona.
		if (!balanced)
		{
			INodeData fusionatedNode;

			if(hasRightBrother)
			{
				merge(sucesor,sibling,data,fusionatedNode,RIGHT_SIDE);
				result = removeINodeData(refkey);
				//Recupero clave del que borro y se a paso al que queda.
				bigBrother.setLeftPointer(fusionatedNode.getLeftPointer());
				modifyINodeData(bigBrother);
			}
			else
			{
				merge(sibling,sucesor,data,fusionatedNode,LEFT_SIDE);
				result = removeINodeData(minorBrother);
				refkey.setLeftPointer(fusionatedNode.getLeftPointer());
				modifyINodeData(refkey);
			}
			// En la fusion se elimina el sibling, permanece el que produjo el underflow.

			m_tree->deleteNode(sibling);
		}

		if (sibling!=NULL)
		{
			m_tree->saveNode(sibling);
			delete sibling;
		}
	}

	m_tree->saveNode(sucesor);
	delete sucesor;

	m_tree->saveNode(this);

	return result;
}


bool InnerNode::find(std::string key, InputData & data)
throw(NodeException)
{
	bool found = false;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData thiskey(Node::UNDEFINED_NODE_NUMBER,key);

	// Busca el nodo interno que referencia a esa clave
	INodeData refkey;
	if (!findINodeData(thiskey,refkey,BIGGER))
		throw NodeException(NodeException::INVALID_REF);;

	// traigo el sucesor de este innerNode.
	Node* sucesor = m_tree->getNode(refkey.getLeftPointer());

	found = sucesor->find(key,data);

	// Solo quiero mantener en memoria el current. El resto lo elimino una vez encontrado.
	if (sucesor!=m_tree->getCurrent())
	{
		delete sucesor;
		sucesor = NULL;
	}

	return found;
}

loadResultEnum InnerNode::insertINodeData(const INodeData& iNodeData,INodeData& promotedKey)
throw(NodeException)
{
	/// Trata de insertar un elemento INodeData y si dio overflow hace el split.
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	INodeData currentData;

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[iNodeData.getSize()];
	iNodeData.toStream(valueReg);
	VarRegister regData(valueReg,iNodeData.getSize());

	/// Busco donde insertar el dato dentro del bloque de nodo interno.
	m_block->restartCounter();

	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();




	if (strcmp(iNodeData.getKey().c_str(),INodeData::UNDEFINED_KEY.c_str())==0)
		m_block->jumpEndCounter();



	while (strcmp(iNodeData.getKey().c_str(),INodeData::UNDEFINED_KEY.c_str())!=0 &&
			!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentValue = currentRegister.getValue(); // hace alloc
		currentData.toNodeData(currentValue);


		if (strcmp(currentData.getKey().c_str(),INodeData::UNDEFINED_KEY.c_str())==0 ||
			currentData.getKey()>= iNodeData.getKey())
		{
			found = true;
			if (currentData.getKey() == iNodeData.getKey())
				throw NodeException(NodeException::DUPLICATED_IN_INNER);
		}else

		currentRegister = m_block->getNextRegister();

		delete [] currentValue;
	}


	unsigned int pos = m_block->getPosActual();


	/// Lo agrega al final si no lo encontro
	m_block->addRegister(regData,result);

	if (result == OVERFLOW_LOAD)
		split(iNodeData,pos,promotedKey);

	delete[] valueReg;

	return result;
}


bool InnerNode::findINodeData(INodeData & innerNodeElem,INodeData & innerNodeFound, Condition condition)
{
	bool retFound=false;
	INodeData currentData;

	VarRegister reg;
	char* valueReg = NULL;

	if(m_block->getRegisterAmount() > 1)
	{
		m_block->restartCounter();


		if(condition!= MINOR)
		{
			//Itera una vez para obviar el dato de control.
			VarRegister level = m_block->getNextRegister();

			//Obtengo el primer InodeData
			reg = m_block->peekRegister();

			//Si no es el ultimo bloque y no encontro el elemento
			while(!m_block->isLastRegister()&&!retFound)
			{
				reg = m_block->peekRegister();
				valueReg = reg.getValue(); //hace alloc
				currentData.toNodeData(valueReg);

				if(condition  == EQUAL)
				{
					//Comparo si es igual o si es el ultimo registro
					if(currentData == innerNodeElem)
					{
						retFound=true;
						innerNodeFound = currentData;
					}
				}
				else
				{
					//Comparo si es mayor o si es el ultimo registro
					if(currentData > innerNodeElem)
					{
						retFound=true;
						innerNodeFound = currentData;
					}
				}
				//Pido el siguiente
				reg = m_block->getNextRegister();
				delete[] valueReg;
			}
		}
		else
		{
			//Salto al final
			m_block->jumpLastRegister();

			//Evito el ultimo registro, ya que tiene key -1
			m_block->getPreviousRegister();

			//Mientras no lo encuentre y no llegue a los datos de control
			while(!m_block->isFirstRegister()&&!retFound)
			{
				//Pido el dato y retrocedo el iterador
				reg = m_block->getPreviousRegister();
				valueReg = reg.getValue();
				currentData.toNodeData(valueReg);

				//Si es menor lo devuelvo
				if(currentData < innerNodeElem)
				{
					retFound=true;
					innerNodeFound = currentData;
				}

				delete[] valueReg;
			}

		}
	}

	return retFound;
}


loadResultEnum InnerNode::removeINodeData(const INodeData& iNodeData)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	INodeData currentData;

	/// Busco donde insertar el dato dentro del bloque de nodo interno.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentValue = currentRegister.getValue();
		currentData.toNodeData(currentValue);
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo elimino
			found = true;
			m_block->deleteRegister(result);
		}
		else
		{
			m_block->getNextRegister();
		}

		delete [] currentValue;
	}

	if (!found)
			throw NodeException(NodeException::INEXISTENT_ELEMINNER);

	return result;
}

loadResultEnum InnerNode::modifyINodeData(const INodeData& iNodeData)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	INodeData currentData;

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[iNodeData.getSize()];
	iNodeData.toStream(valueReg);
	VarRegister regData(valueReg,iNodeData.getSize());

	/// Busco donde insertar el dato dentro del bloque de nodo interno.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
//	VarRegister pointers = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentValue = currentRegister.getValue();
		currentData.toNodeData(currentValue);
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo modifica
			found = true;
			m_block->modifyRegister(regData,result);
		}else
			this->m_block->getNextRegister();

		delete[] currentValue;

	}
	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMINNER);

	delete[] valueReg;

	return result;
}

loadResultEnum InnerNode::modifyINodeData(const INodeData& iNodeData,const INodeData& newINodeData)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	char* currentValue = NULL;
	VarRegister currentRegister;
	INodeData currentData;

	// Creo el registro del segundo parametro para poder insertarlo en el bloque.
	char* valueReg = new char[newINodeData.getSize()];
	newINodeData.toStream(valueReg);
	VarRegister regData(valueReg,newINodeData.getSize());

	/// Busco donde insertar el dato dentro del bloque de nodo interno.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
//	VarRegister pointers = m_block->getNextRegister();

	while (!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentValue = currentRegister.getValue();
		currentData.toNodeData(currentValue);
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo modifica
			found = true;
			m_block->modifyRegister(regData,result);
		}
		else
			this->m_block->getNextRegister();

		delete[] currentValue;
	}

	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMINNER);

//	if (result!= NORMAL_LOAD)
//		throw NodeException(NodeException::ANOMALOUS_LOADRESULT);

	delete[] valueReg;

	return result;
}

bool InnerNode::split(const INodeData& data,unsigned int pos,INodeData& promotedKey)
{
	InnerNode* sibling = m_tree->newInnerNode(getLevel());
	Block* blockSibling = sibling->getBlock();

	char* valueReg = new char[data.getSize()];
	data.toStream(valueReg);
	VarRegister reg(valueReg,data.getSize());

	BlockManager::redistributeOverflow(m_block,blockSibling,reg,pos);
	//Recupera primer elemento del neuvo nodo.
	blockSibling->restartCounter();
	//Saltea datos de control
	blockSibling->getNextRegister();

	delete [] valueReg;

	reg = blockSibling->getNextRegister();
	valueReg = reg.getValue();
	INodeData firstKey;
	firstKey.toNodeData(valueReg);

	// Obtiene la primer clave del sibling derecho y su numero de nodo.
	promotedKey.setKey(firstKey.getKey());
	promotedKey.setLeftPointer(sibling->getNodeNumber());
	this->modifyLastKey();

	this->m_tree->saveNode(sibling);

	delete sibling;

	delete[] valueReg;

	return true;
}

bool InnerNode::redistribute(Node* node,Node* siblingNode,const InputData& data,INodeData& keyToModify,sideEnum side)
{
	bool retVal = false;
	InputData* currentData = data.newInstance();

	Block* blockRight = NULL;
	Block* blockNode = node->getBlock();
	Block* blockSibling = siblingNode->getBlock();

	if(!siblingNode->isLeaf()){

		if(side==RIGHT_SIDE){

			//busca primer elemento del hermano
			INodeData firstKey=this->getFirstKeyLeaf(siblingNode,data);
			InnerNode* enUnder=(InnerNode*)node;
			INodeData lastUnder=enUnder->getLastINodeData();
			firstKey.setLeftPointer(lastUnder.getLeftPointer());

			enUnder->modifyINodeData(lastUnder,firstKey);

		}else{
			//Busca el primer elemento del nodo en underflow

			INodeData firstKey=this->getFirstKeyLeaf(node,data);
			InnerNode* hermano=(InnerNode*)siblingNode;
			INodeData lastHermano=hermano->getLastINodeData();
			firstKey.setLeftPointer(lastHermano.getLeftPointer());

			hermano->modifyINodeData(lastHermano,firstKey);
		}
	}

	retVal = BlockManager::balanceLoad(blockNode,blockSibling,side);
	VarRegister firstKey;
	char* valueReg = NULL;

	if (side == RIGHT_SIDE)
	{
		blockRight = blockSibling;
		keyToModify.setLeftPointer(node->getNodeNumber());
	}
	else
	{
		blockRight = blockNode;
		keyToModify.setLeftPointer(siblingNode->getNodeNumber());
	}


	if (node->isLeaf())
	{
		blockRight->restartCounter();
		firstKey = blockRight->getRegisterN(3);
		valueReg = firstKey.getValue();
		/// porque InputData es abstracto.
		currentData->toData(valueReg);
		keyToModify.setKey(currentData->getKey());
		delete [] valueReg;
	}
	else
	{
		blockRight->restartCounter();
		firstKey = blockRight->getRegisterN(1);
		valueReg = firstKey.getValue();
		keyToModify.toNodeData(valueReg);
		delete[] valueReg;
	}

	delete currentData;

	return retVal;
}


bool InnerNode::merge(Node* node,Node* siblingNode,const InputData& data,INodeData& fusionatedNode,sideEnum side)
{
	//Intercambio puntero.

	bool retVal = false;
	VarRegister firstKey;
	char* valueReg = NULL;

	InputData* currentData = data.newInstance();

	// Bloques de los nodos a fusionar.
	Block* blockNode = node->getBlock();
	Block* blockSibling = siblingNode->getBlock();

	// Guardo los datos de control acerca de los punteros
	// siguiente y anterior, en el caso en se esten fusionando hojas.
	unsigned int nextLeaf = UNDEFINED_NODE_NUMBER;
	unsigned int prevLeaf = UNDEFINED_NODE_NUMBER;

	if (node->isLeaf())
	{
		if (side == RIGHT_SIDE)
		{
			nextLeaf = ((LeafNode*)siblingNode)->getNextLeaf();
		}
		else
		{
			nextLeaf = ((LeafNode*)siblingNode)->getNextLeaf();
			prevLeaf=((LeafNode*)node)->getPreviousLeaf();
		}
	}

	if(!siblingNode->isLeaf())
	{
		if(side==RIGHT_SIDE){

			//busca primer elemento
			INodeData firstKey=this->getFirstKeyLeaf(siblingNode,data);
			InnerNode* enUnder=(InnerNode*)node;
			INodeData lastUnder = enUnder->getLastINodeData();
			firstKey.setLeftPointer(lastUnder.getLeftPointer());

			enUnder->modifyINodeData(lastUnder,firstKey);
		}
		else{
			//Busca el ultimo elemento
			//busca primer elemento
			INodeData firstKey = this->getFirstKeyLeaf(node,data);
			InnerNode* hermano = (InnerNode*)siblingNode;
			INodeData lastHermano = hermano->getLastINodeData();
			firstKey.setLeftPointer(lastHermano.getLeftPointer());

			hermano->modifyINodeData(lastHermano,firstKey);
		}

		}
	// Propiamente el merge.
	BlockManager::merge(blockNode,blockSibling,side);

	if (node->isLeaf())
	{
		blockNode->restartCounter();
		// paso los 3 datos de control de la hoja.
		firstKey = blockNode->getRegisterN(3);
		/// porque InputData es abstracto.
		valueReg = firstKey.getValue();
		currentData->toData(valueReg);
		fusionatedNode.setKey(currentData->getKey());
		delete[] valueReg;

		((LeafNode*)node)->setNextLeaf(nextLeaf);

		if(side==LEFT_SIDE){

			if(((LeafNode*)node)->getNextLeaf()!=UNDEFINED_NODE_NUMBER)
			{
			LeafNode* nextLeaf= (LeafNode*)m_tree->getNode(((LeafNode*)node)->getNextLeaf());
			nextLeaf->setPreviousLeaf(((LeafNode*)node)->getNodeNumber());
			m_tree->saveNode(nextLeaf);
			delete nextLeaf;
			}

			if(prevLeaf!=UNDEFINED_NODE_NUMBER)
			{
				LeafNode* previLeaf= (LeafNode*)m_tree->getNode(prevLeaf);
				previLeaf->setNextLeaf(((LeafNode*)node)->getNodeNumber());
				m_tree->saveNode(previLeaf);
				delete previLeaf;
			}

		}
		else
		{
			if(((LeafNode*)node)->getNextLeaf()!=UNDEFINED_NODE_NUMBER)
			{
				LeafNode* nextLeaf= (LeafNode*)this->m_tree->getNode(((LeafNode*)node)->getNextLeaf());
				nextLeaf->setPreviousLeaf(((LeafNode*)node)->getNodeNumber());
				m_tree->saveNode(nextLeaf);
				delete nextLeaf;

			}
		}
	}
	else
	{
		blockNode->restartCounter();
		// paso el dato de control del nivel.
		blockNode->getNextRegister();
		firstKey = blockNode->getNextRegister();
		valueReg = firstKey.getValue();
		fusionatedNode.toNodeData(valueReg);
		delete valueReg;
	}

	fusionatedNode.setLeftPointer(node->getNodeNumber());

	delete currentData;

	return retVal;
}


void InnerNode::printContent()
{
	INodeData data;
	VarRegister varR;
	char* valueReg = NULL;
	unsigned int dataAmmount;
	unsigned int i=0;

	m_block->restartCounter();
	dataAmmount = m_block->getRegisterAmount();

	cout << "\t Numero nodo: " << getNodeNumber();
	varR = m_block->getNextRegister(true);
	valueReg = varR.getValue();
	cout << "\t Nivel: "<<ByteConverter::bytesToUInt(valueReg);
	cout << "\n Datos "<<endl;

	delete [] valueReg;

	i = m_block->getPosActual();

	for(i = i; i < dataAmmount; i++)
	{
		varR = m_block->getNextRegister(true);
		valueReg = varR.getValue();
		data.toNodeData(valueReg);
		cout << data.getLeftPointer();
		cout << " (Clave:" << data.getKey() << ") ";
		delete[] valueReg;
	}
	cout << endl;
}

void InnerNode::show(){

	StringInputData data;
	this->printContent();

	bool found = false;
	m_block->restartCounter();
	m_block->getNextRegister();

	char* valueReg = NULL;
	VarRegister reg;
	INodeData currentData;
	Node* hijo;

	while(!m_block->isLastRegister()&& !found)
		{

			reg = m_block->peekRegister();
			valueReg = reg.getValue();
			// Transformo el registro a un INodeData
			currentData.toNodeData(valueReg);
			//Pido un hijo para decirle que se muestre.
			hijo = m_tree->getNode(currentData.getLeftPointer());

			hijo->show();

			if (hijo!=NULL)
				delete hijo;

			m_block->getNextRegister();

			delete[] valueReg;
		}
}

void InnerNode::modifyLastKey()
{
	INodeData iNodeData;
	loadResultEnum result;

	m_block->restartCounter();

	int posUltimoReg=m_block->getRegisterAmount()-1;

	while (m_block->getPosActual()<posUltimoReg){
		m_block->getNextRegister();
	};

	VarRegister changeReg = this->m_block->peekRegister();
	char* changeValue = changeReg.getValue(); //hace alloc

	iNodeData.toNodeData(changeValue);


	iNodeData.setKey(INodeData::UNDEFINED_KEY);


	delete [] changeValue;

	char* valueReg = new char[iNodeData.getSize()];
	iNodeData.toStream(valueReg);
	VarRegister regData(valueReg,iNodeData.getSize());

	m_block->modifyRegister(regData,result);

	delete[] valueReg;

}

INodeData InnerNode::getFirstKeyLeaf(Node* searchNode,const InputData&  data){

	Node* sucesor = searchNode;
	Node* nodoIzquierdo;
	Block* bloqueIzquierdo = sucesor->getBlock();

	VarRegister reg;
	char* valueReg = NULL;
	INodeData firstData;

	bloqueIzquierdo->restartCounter();
	bloqueIzquierdo->getNextRegister();
	reg = bloqueIzquierdo->getNextRegister();
	valueReg = reg.getValue();
	firstData.toNodeData(valueReg);

	delete [] valueReg;

	if (!sucesor->isLeaf())
	{
		INodeData currentData;
		nodoIzquierdo = m_tree->getNode(firstData.getLeftPointer());
		bloqueIzquierdo = nodoIzquierdo->getBlock();

		while(!nodoIzquierdo->isLeaf()){

			//Salteo info de control.
			bloqueIzquierdo->restartCounter();
			bloqueIzquierdo->getNextRegister();

			reg = bloqueIzquierdo->getNextRegister();
			valueReg = reg.getValue();
			firstData.toNodeData(valueReg);

			delete nodoIzquierdo;
			nodoIzquierdo = m_tree->getNode(currentData.getLeftPointer());
			bloqueIzquierdo = nodoIzquierdo->getBlock();

			delete [] valueReg;

		}
		InputData* leftKey = data.newInstance();
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

		firstData.setKey(leftKey->getKey());

		delete leftKey;

		if (nodoIzquierdo!=NULL)
			delete nodoIzquierdo;

		if (valueReg!=NULL)
			delete[] valueReg;

	}

	return firstData;
}

INodeData InnerNode::getLastINodeData(){
	INodeData iNodeData;

	m_block->restartCounter();
	int posUltimoReg = m_block->getRegisterAmount()-1;

	while (m_block->getPosActual()<posUltimoReg){
		m_block->getNextRegister();
	};

	VarRegister reg = m_block->peekRegister();
	char* valueReg = reg.getValue();
	iNodeData.toNodeData(valueReg);

	delete [] valueReg;

	return iNodeData;

};


bool InnerNode::getFirstData(InputData & data){
		bool retval=false;
		m_block->restartCounter();
		m_block->getNextRegister();

		char* valueReg = NULL;
		VarRegister reg;
		INodeData currentData;
		Node* hijo;

		reg = m_block->peekRegister();
		valueReg = reg.getValue();
		// Transformo el registro a un INodeData
		currentData.toNodeData(valueReg);
		//Pido el primer hijo y le pido el primer elemento.
		hijo = m_tree->getNode(currentData.getLeftPointer());
		retval=hijo->getFirstData(data);

		if (hijo!=m_tree->getCurrent())
		{
			delete hijo;
			hijo = NULL;
		}


		delete[] valueReg;

return retval;

};
