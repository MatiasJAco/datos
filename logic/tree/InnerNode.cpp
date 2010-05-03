/**
 * @file InnerNode.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "InnerNode.h"
#include <sstream>
using namespace std;


InnerNode::InnerNode(unsigned int nodeNumber, unsigned int level, Block *block,const InputData& typeData)
:Node(nodeNumber,level,block,typeData)
{
	m_block->setFixedRegisterCount(1);
}

InnerNode::InnerNode(unsigned int nodeNumber,unsigned int level,Block* block,const InputData& typeData,BPlusTree* pointerTree)
//:Node(nodeNumber,level,block,pointerTree)
:Node(nodeNumber,level,block,typeData)
{
	m_block->setFixedRegisterCount(1);
	m_tree = pointerTree;
}

InnerNode::~InnerNode()
{
}



void InnerNode::getInPosition(INodeData * contenido, unsigned int position)
{
	//Busca al sucesor que puede tener el dato
	m_block->restartCounter();
	//Itera una vez para obviar el dato de control.
	VarRegister level = this->m_block->getNextRegister();
	VarRegister reg;
	unsigned int iterador=0;
	bool found=false;
    while(iterador < m_block->getRegisterAmount() && !found){
        reg = this->m_block->peekRegister();
        iterador++;
        // Transformo el registro a un INodeData
        contenido->toNodeData(reg.getValue());
        if(iterador == position){
            found = true;
        }else
        this->m_block->getNextRegister();
    }

}



loadResultEnum InnerNode::modify(const InputData & dato, const InputData & dato2,INodeData& promotedKey)
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
	Node* sucesor = this->m_tree->getNode(refkey.getLeftPointer());

	result=sucesor->modify(dato,dato2,promotedKey);

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

	if(result==UNDERFLOW_LOAD)
	{
		bool hasRightBrother = false;
		bool hasMinorBrother = false;

		bool balanced = false;
		Node* sibling;

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
			balanced = redistribute(sucesor,sibling,dato,keymodified,RIGHT_SIDE);
		}

		if (balanced)
			modifyINodeData(refkey,keymodified);

		// Si no pudo, busco el sibling izquierdo, el hijo del hermano menor.
		if (!balanced)
		{
			//Verifica que tenga hermano izquierdo.
			if (hasMinorBrother)
			{
				sibling = m_tree->getNode(minorBrother.getLeftPointer());
				balanced = redistribute(sucesor,sibling,dato,keymodified,LEFT_SIDE);
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
				merge(sucesor,sibling,dato,fusionatedNode,RIGHT_SIDE);
				result = removeINodeData(refkey);
				//Recupero clave del que borro y se a paso al que queda.
				bigBrother.setLeftPointer(fusionatedNode.getLeftPointer());
				modifyINodeData(bigBrother);
			}
			else
			{
				merge(sucesor,sibling,dato,fusionatedNode,LEFT_SIDE);
				result = removeINodeData(minorBrother);
				refkey.setLeftPointer(fusionatedNode.getLeftPointer());
				modifyINodeData(refkey);
			}
			// En la fusion se elimina el sibling, permanece el que produjo el underflow.
			m_tree->deleteNode(sibling);
		}

		if (sibling!=NULL)
			m_tree->saveNode(sibling);
	}

	if (sucesor!=NULL)
		m_tree->saveNode(sucesor);

	m_tree->saveNode(this);

	return result;
}

loadResultEnum InnerNode::modify(const InputData& data)
{
	return NORMAL_LOAD;
}


INodeData* InnerNode::divideLeaf(Node* aPartir,Node* destNode,const InputData& newData){
	//Para hijos hoja
	LeafNode* nodoAPartir=(LeafNode*)aPartir;
	char* valueReg = new char[newData.size()];
	VarRegister reg;
	nodoAPartir->getBlock()->getNextRegister();
	reg.setValue(newData.toStream(valueReg),newData.size());
	//Recorro para obtener la posicion.
    unsigned int posicion=buscarPosicionLeaf(nodoAPartir,newData);

	BlockManager::redistributeOverflow(aPartir->getBlock(),destNode->getBlock(),reg,posicion);
	//Devuelvo el primer elemento del nuevo nodo.
	destNode->getBlock()->restartCounter();
	//Saltea datos de control.
	destNode->getBlock()->getNextRegister();
	//Recupera primer registro.
	VarRegister regBuscado;
	InputData* conteBuscado;
	regBuscado=destNode->getBlock()->getNextRegister();
	conteBuscado->toData(regBuscado.getValue());
	INodeData* datoADevolver =new INodeData(destNode->getNodeNumber(),conteBuscado->getKey());
	return datoADevolver;

}

unsigned int InnerNode::buscarPosicionLeaf(LeafNode *& nodoAPartir,const InputData & newData){
	nodoAPartir->getBlock()->restartCounter();
	nodoAPartir->getBlock()->getNextRegister();
	bool found=false;
	unsigned int posicion=0;
	VarRegister regBuscado;
	InputData* conteBuscado;
	while(posicion<nodoAPartir->getBlock()->getRegisterAmount()&& !found ){
		posicion++;
		regBuscado=nodoAPartir->getBlock()->peekRegister();
		//Transformo el registro a un InputData
		conteBuscado->toData(regBuscado.getValue());
		if(newData.getKey()<conteBuscado->getKey()){
			found=true;
		}else{
			nodoAPartir->getBlock()->getNextRegister();
		};
	};
	nodoAPartir->getBlock()->restartCounter();
	return posicion;
}


unsigned int InnerNode::buscarPosicionInner(InnerNode *& nodoAPartir,INodeData & newData)
{
	nodoAPartir->getBlock()->restartCounter();
	nodoAPartir->getBlock()->getNextRegister();
	bool found = false;
	unsigned int posicion = 0;
	VarRegister regBuscado;
	INodeData *conteBuscado;
    while(posicion < nodoAPartir->getBlock()->getRegisterAmount() && !found){
        posicion++;
        regBuscado = nodoAPartir->getBlock()->peekRegister();
        conteBuscado->toNodeData(regBuscado.getValue());
        if(newData.getKey() < conteBuscado->getKey()){
            found = true;
        }else{
            nodoAPartir->getBlock()->getNextRegister();
        };
    };
    nodoAPartir->getBlock()->restartCounter();
    return posicion;
}

unsigned int InnerNode::buscarPosicionInnerPorClave(int key)
{
	this->getBlock()->restartCounter();
	this->getBlock()->getNextRegister();
	bool found = false;
	unsigned int posicion = 0;
	VarRegister regBuscado;
	InputData *conteBuscado;
    while(posicion < this->getBlock()->getRegisterAmount() && !found){
        posicion++;
        regBuscado = this->getBlock()->peekRegister();
        conteBuscado->toData(regBuscado.getValue());
        if(key < conteBuscado->getKey()){
            found = true;
        }else{
            this->getBlock()->getNextRegister();
        };
    };
    this->getBlock()->restartCounter();
    return posicion;
}

INodeData* InnerNode::divideInner(Node* aPartir,Node* destNode,INodeData& newData){
    InnerNode *nodoAPartir = (InnerNode*)(aPartir);
    char *valueReg = new char[newData.getSize()];
    VarRegister reg;
    nodoAPartir->getBlock()->getNextRegister();
    reg.setValue(newData.toStream(valueReg), newData.getSize());
    unsigned int posicion=buscarPosicionInner(nodoAPartir,newData);
    BlockManager::redistributeOverflow(aPartir->getBlock(), destNode->getBlock(), reg, posicion);
    destNode->getBlock()->restartCounter();
    destNode->getBlock()->getNextRegister();
    VarRegister regBuscado;
    INodeData* conteBuscado=new INodeData(0,0);
    regBuscado=destNode->getBlock()->getNextRegister();
	conteBuscado->toNodeData(regBuscado.getValue());
	INodeData* datoADevolver =new INodeData(destNode->getNodeNumber(),conteBuscado->getKey());
	return datoADevolver;

}


void InnerNode::join(Node* toDivide,Node* destNode,const InputData& newData){

}

bool InnerNode::balanceLeaf(Node* underNode,Node* toDonate,const InputData& newData){
	LeafNode* nodoUnderflow=(LeafNode*)underNode;
	char *valueReg = new char[newData.size()];
	VarRegister reg;
    reg.setValue(newData.toStream(valueReg), newData.size());
	//Busca Posicion
	unsigned int posicion=this->buscarPosicionLeaf(nodoUnderflow,newData);
	return BlockManager::redistributeUnderflow(underNode->getBlock(),toDonate->getBlock(),reg,posicion);

}

bool InnerNode::balanceInner(Node* underNode,Node* toDonate,INodeData& newData){
	InnerNode* nodoUnderflow=(InnerNode*)underNode;
	char *valueReg = new char[newData.getSize()];
	VarRegister reg;
	reg.setValue(newData.toStream(valueReg), newData.getSize());
	//Busca Posicion
	unsigned int posicion=this->buscarPosicionInner(nodoUnderflow,newData);
	return BlockManager::redistributeUnderflow(underNode->getBlock(),toDonate->getBlock(),reg,posicion);
}




void InnerNode::save(Node* node)
{
	m_tree->saveNode(node);
}

void InnerNode::joinLeaf(Node *underNode, Node *destNode, const InputData & newData){
	LeafNode* nodoUnderflow=(LeafNode*)underNode;
	char *valueReg = new char[newData.size()];
	VarRegister reg;
	reg.setValue(newData.toStream(valueReg), newData.size());
	//Busca Posicion
	unsigned int position=this->buscarPosicionLeaf(nodoUnderflow,newData);
	BlockManager::mergeBlocks(underNode->getBlock(),destNode->getBlock(),reg,position);

};

void InnerNode::joinInner(Node *underNode, Node *destNode,  INodeData*  newData){
	 	InnerNode* nodoUnderflow=(InnerNode*)underNode;
		char *valueReg = new char[newData->getSize()];
		VarRegister reg;
		reg.setValue(newData->toStream(valueReg), newData->getSize());
		//Busca Posicion
		unsigned int position=this->buscarPosicionInner(nodoUnderflow,*newData);
		BlockManager::mergeBlocks(underNode->getBlock(),destNode->getBlock(),reg,position);

};



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
		m_tree->saveNode(sucesor);

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
		Node* sibling;

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
			m_tree->saveNode(sibling);
	}

	m_tree->saveNode(sucesor);
	m_tree->saveNode(this);

	return result;
}


bool InnerNode::find(const InputData & key, InputData & data)
throw(NodeException)
{
	bool found = false;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData thiskey(Node::UNDEFINED_NODE_NUMBER,key.getKey());

	// Busca el nodo interno que referencia a esa clave
	INodeData refkey;
	if (!findINodeData(thiskey,refkey,BIGGER))
		throw NodeException(NodeException::INVALID_REF);;

	// traigo el sucesor de este innerNode.
	Node* sucesor = m_tree->getNode(refkey.getLeftPointer());

	found = sucesor->find(key,data);

	return found;
}

loadResultEnum InnerNode::insertINodeData(const INodeData& iNodeData,INodeData& promotedKey)
throw(NodeException)
{
	/// Trata de insertar un elemento INodeData y si dio overflow hace el split.
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

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

	if (iNodeData.getKey()==INodeData::UNDEFINED_KEY)
		m_block->jumpEndCounter();

	while (iNodeData.getKey()!=INodeData::UNDEFINED_KEY&&
			!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey()==INodeData::UNDEFINED_KEY||
			currentData.getKey()>= iNodeData.getKey())
		{
			found = true;
			if (currentData.getKey() == iNodeData.getKey())
				throw NodeException(NodeException::DUPLICATED_IN_INNER);
		}else

		currentRegister = m_block->getNextRegister();
	}


	unsigned int pos = m_block->getPosActual();


	/// Lo agrega al final si no lo encontro
	m_block->addRegister(regData,result);

	if (result == OVERFLOW_LOAD)
		split(iNodeData,pos,promotedKey);

	return result;
}


bool InnerNode::findINodeData(INodeData & innerNodeElem,INodeData & innerNodeFound, Condition condition)
{
	bool retFound=false;
	INodeData currentData;

	VarRegister reg;

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

				currentData.toNodeData(reg.getValue());

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
				currentData.toNodeData(reg.getValue());

				//Si es menor lo devuelvo
				if(currentData < innerNodeElem)
				{
					retFound=true;
					innerNodeFound = currentData;
				}

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
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo elimino
			found = true;
			m_block->deleteRegister(result);
		}else{
			m_block->getNextRegister();
		};

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
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo modifica
			found = true;
			m_block->modifyRegister(regData,result);
		}else
			this->m_block->getNextRegister();


	}
	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMINNER);

	return result;
}

loadResultEnum InnerNode::modifyINodeData(const INodeData& iNodeData,const INodeData& newINodeData)
throw (NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

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
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo modifica
			found = true;
			m_block->modifyRegister(regData,result);
		}
		else
			this->m_block->getNextRegister();


	}
	if (!found)
		throw NodeException(NodeException::INEXISTENT_ELEMINNER);

//	if (result!= NORMAL_LOAD)
//		throw NodeException(NodeException::ANOMALOUS_LOADRESULT);


	return result;
}

INodeData InnerNode::getNextINodeData()
{
	INodeData dataNode;

	VarRegister reg = m_block->getNextRegister();
	dataNode.toNodeData(reg.getValue());

	return dataNode;
}

unsigned int InnerNode::getAmountINodeData()
{
	unsigned int sizeblock = m_block->getRegisterAmount();

	// Le resto el dato de control.
	return (sizeblock-1);
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

	reg=blockSibling->getNextRegister();
	INodeData firstKey;
	firstKey.toNodeData(reg.getValue());

	// Obtiene la primer clave del sibling derecho y su numero de nodo.
	promotedKey.setKey(firstKey.getKey());
	promotedKey.setLeftPointer(sibling->getNodeNumber());
	this->modifyLastKey();

	this->m_tree->saveNode(sibling);
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
			};

	};

	retVal = BlockManager::balanceLoad(blockNode,blockSibling,side);
	VarRegister firstKey;

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
		/// porque InputData es abstracto.
		currentData->toData(firstKey.getValue());
		keyToModify.setKey(currentData->getKey());
	}
	else
	{
		blockRight->restartCounter();
		firstKey = blockRight->getRegisterN(1);
		keyToModify.toNodeData(firstKey.getValue());
	}

	delete currentData;

	return retVal;
}


bool InnerNode::merge(Node* node,Node* siblingNode,const InputData& data,INodeData& fusionatedNode,sideEnum side)
{
	//Intercambio puntero.



	bool retVal = false;
	VarRegister firstKey;
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

	if(!siblingNode->isLeaf()){
		if(side==RIGHT_SIDE){

			//busca primer elemento
			INodeData firstKey=this->getFirstKeyLeaf(siblingNode,data);
			InnerNode* enUnder=(InnerNode*)node;
			INodeData lastUnder=enUnder->getLastINodeData();
			firstKey.setLeftPointer(lastUnder.getLeftPointer());

			enUnder->modifyINodeData(lastUnder,firstKey);
		}else{
			//Busca el ultimo elemento
			//busca primer elemento
			INodeData firstKey=this->getFirstKeyLeaf(node,data);
			InnerNode* hermano=(InnerNode*)siblingNode;
			INodeData lastHermano=hermano->getLastINodeData();
			firstKey.setLeftPointer(lastHermano.getLeftPointer());

			hermano->modifyINodeData(lastHermano,firstKey);
		};

		};
	// Propiamente el merge.
	BlockManager::merge(blockNode,blockSibling,side);

	if (node->isLeaf())
	{
		blockNode->restartCounter();
		// paso los 3 datos de control de la hoja.
		firstKey = blockNode->getRegisterN(3);
		/// porque InputData es abstracto.
		currentData->toData(firstKey.getValue());
		fusionatedNode.setKey(currentData->getKey());
		((LeafNode*)node)->setNextLeaf(nextLeaf);

		if(side==LEFT_SIDE){
			if(((LeafNode*)node)->getNextLeaf()!=UNDEFINED_NODE_NUMBER){
			LeafNode*nextLeaf= (LeafNode*)this->m_tree->getNode(((LeafNode*)node)->getNextLeaf());
			nextLeaf->setPreviousLeaf(((LeafNode*)node)->getNodeNumber());
			this->m_tree->saveNode(nextLeaf);

		};
			if(prevLeaf!=UNDEFINED_NODE_NUMBER){
				LeafNode*previLeaf= (LeafNode*)this->m_tree->getNode(prevLeaf);
				previLeaf->setNextLeaf(((LeafNode*)node)->getNodeNumber());
				this->m_tree->saveNode(previLeaf);
			}
		}else{
			if(((LeafNode*)node)->getNextLeaf()!=UNDEFINED_NODE_NUMBER){
				LeafNode*nextLeaf= (LeafNode*)this->m_tree->getNode(((LeafNode*)node)->getNextLeaf());
				nextLeaf->setPreviousLeaf(((LeafNode*)node)->getNodeNumber());
				this->m_tree->saveNode(nextLeaf);
			};
		};
	}
	else
	{
		blockNode->restartCounter();
		// paso el dato de control del nivel.
		blockNode->getNextRegister();
		firstKey = blockNode->getNextRegister();
		fusionatedNode.toNodeData(firstKey.getValue());
	}

	fusionatedNode.setLeftPointer(node->getNodeNumber());

	delete currentData;

	return retVal;
}


void InnerNode::printContent(InputData& dato)
{
	INodeData data;
	VarRegister varR;
	unsigned int dataAmmount;
	unsigned int i=0;

	m_block->restartCounter();
	dataAmmount = m_block->getRegisterAmount();

	cout << "\t Numero nodo: " << getNodeNumber();
	varR = m_block->getNextRegister(true);
	cout << "\t Nivel: "<<ByteConverter::bytesToUInt(varR.getValue());
	cout << "\n Datos "<<endl;

	i = m_block->getPosActual();

	for(i = i; i < dataAmmount; i++)
	{
		varR = m_block->getNextRegister(true);
		data.toNodeData(varR.getValue());
		cout << data.getLeftPointer();
		cout << " (Clave:" << data.getKey() << ") ";
	}
	cout << endl;
}

void InnerNode::show(InputData& data){

	this->printContent(data);
	bool found=false;
	m_block->restartCounter();
	m_block->getNextRegister();
	VarRegister reg;
	INodeData currentData;
	Node* hijo;
	while(!m_block->isLastRegister()&& !found)
		{

			reg = this->m_block->peekRegister();
			// Transformo el registro a un INodeData
			currentData.toNodeData(reg.getValue());
			//Pido un hijo para decirle que se muestre.
			hijo =this->m_tree->getNode(currentData.getLeftPointer());
			hijo->show(data);

			this->m_block->getNextRegister();
		}
	delete hijo;

};

void InnerNode::modifyLastKey(){
	INodeData iNodeData;
	loadResultEnum result;
	m_block->restartCounter();
	int posUltimoReg=m_block->getRegisterAmount()-1;
	while (m_block->getPosActual()<posUltimoReg){
		m_block->getNextRegister();
	};
	VarRegister changeReg;
	changeReg=this->m_block->peekRegister();
	iNodeData.toNodeData(changeReg.getValue());
	iNodeData.setKey(INodeData::UNDEFINED_KEY);
	char* valueReg = new char[iNodeData.getSize()];
	iNodeData.toStream(valueReg);
	VarRegister regData(valueReg,iNodeData.getSize());
	m_block->modifyRegister(regData,result);

};

INodeData InnerNode::getFirstKeyLeaf(Node* searchNode,const InputData&  data){
	Node* sucesor=searchNode;
	Node* nodoIzquierdo;
	Block* bloqueIzquierdo=sucesor->getBlock();
	VarRegister reg;
	INodeData firstData;
	bloqueIzquierdo->restartCounter();
	bloqueIzquierdo->getNextRegister();
	reg=bloqueIzquierdo->getNextRegister();
	firstData.toNodeData(reg.getValue());


	if (!sucesor->isLeaf()){
		INodeData currentData;
		nodoIzquierdo=this->m_tree->getNode(firstData.getLeftPointer());

		while(!nodoIzquierdo->isLeaf()){
			//Obtener primer clave de la rama.
			bloqueIzquierdo =nodoIzquierdo->getBlock();
			//Salteo info de control.
			bloqueIzquierdo->restartCounter();
			bloqueIzquierdo->getNextRegister();
			reg=bloqueIzquierdo->getNextRegister();
			firstData.toNodeData(reg.getValue());
			nodoIzquierdo=this->m_tree->getNode(currentData.getLeftPointer());
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
		firstData.setKey(leftKey->getKey());

	};
return firstData;
}

INodeData InnerNode::getLastINodeData(){
	INodeData iNodeData;
	m_block->restartCounter();
	int posUltimoReg=m_block->getRegisterAmount()-1;
	while (m_block->getPosActual()<posUltimoReg){
		m_block->getNextRegister();
	};
	VarRegister reg=m_block->peekRegister();
	iNodeData.toNodeData(reg.getValue());
	return iNodeData;

};
