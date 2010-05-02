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
	INodeData nodePointerKey(Node::UNDEFINED_NODE_NUMBER,dato.getKey());

	// Busco el elemento de nodo interno que contiene la referencia a la clave de dato.
	if (!findINodeData(nodePointerKey))
		throw NodeException(NodeException::INVALID_REF);

	// Se lo pide al arbol
	Node* sucesor = this->m_tree->getNode(nodePointerKey.getLeftPointer());
	result=sucesor->modify(dato,dato2,promotedKey);
	if (result==OVERFLOW_LOAD){
		// Busca el INodeData mayor al promotedKey y es seteada dentro de la misma.

		// Hace el intercambio de claves y punteros. Modifica el puntero de bigger
		INodeData bigger(UNDEFINED_NODE_NUMBER,promotedKey.getKey());
		findINodeData(bigger,false);

		INodeData newINodeData(bigger.getLeftPointer(),promotedKey.getKey());
		bigger.setLeftPointer(promotedKey.getLeftPointer());

		modifyINodeData(bigger);

		/// Devuelve el resultado de haber insertado una clave,
		/// promoted Key es modificado despues del insert.
		result = insertINodeData(newINodeData,promotedKey);

	}else{
		if(result==UNDERFLOW_LOAD){
			//TODO implementar este caso
			bool hasRightBrother=false;
			bool leftJoin=true;
			bool balanced = false;
			Node* rightSibling;
			Node* leftSibling;
			INodeData joinBrother;

			// busco el hermano mayor a key para obtener el hijo derecho.
			INodeData bigBrother(UNDEFINED_NODE_NUMBER,nodePointerKey.getKey());
			findINodeData(bigBrother,false);
			//Verifico que tenga hermano derecho.
			if(!this->m_block->hasNextRegister()){
				hasRightBrother=false;
			}

			if(hasRightBrother){
				joinBrother.setKey(bigBrother.getKey());
				joinBrother.setLeftPointer(bigBrother.getLeftPointer());
				// Trato de balancear con el derecho.
				// Al redistribuir me devuelve la clave que hay que promover y modificar en thiskey.
				rightSibling = m_tree->getNode(bigBrother.getLeftPointer());
				balanced = redistribute(sucesor,rightSibling,dato,bigBrother,RIGHT_SIDE);
			};

			if (balanced)
				modifyINodeData(nodePointerKey,bigBrother);

			// Si no pudo, busco el sibling izquierdo, el hijo del hermano menor.
			if (!balanced)
			{
				//Verifica que tenga hermano izquierdo.
				INodeData minorBrother(UNDEFINED_NODE_NUMBER,nodePointerKey.getKey());
				findINodeData(minorBrother);
				unsigned int posicionNodo=this->buscarPosicionInnerPorClave(nodePointerKey.getKey());
				if(posicionNodo!=1){
					this->getInPosition(&minorBrother,posicionNodo-1);
					joinBrother.setKey(minorBrother.getKey());
					joinBrother.setLeftPointer(minorBrother.getLeftPointer());
					leftSibling = m_tree->getNode(minorBrother.getLeftPointer());
					// Trato de balancear con el sibling izquierdo del sucesor.
					balanced = redistribute(sucesor,leftSibling,dato,minorBrother,LEFT_SIDE);
				}else
					leftJoin=false;

					if (balanced)
						modifyINodeData(joinBrother,minorBrother);
			}

			// Si no pudo balancear, fusiona.
			if (!balanced)
			{
				INodeData fusionatedNode;
				if(leftJoin){
					merge(sucesor,leftSibling,dato,fusionatedNode,LEFT_SIDE);
					result = removeINodeData(joinBrother);
				}else{
					merge(sucesor,rightSibling,dato,fusionatedNode,RIGHT_SIDE);
					result = removeINodeData(joinBrother);
					//Recupero clave del que borro y se a paso al que queda.
					joinBrother.setLeftPointer(nodePointerKey.getLeftPointer());
					modifyINodeData(nodePointerKey,joinBrother);

				};

			}
		};
	};

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
	INodeData nodePointerKey(Node::UNDEFINED_NODE_NUMBER,data.getKey());

	// Busco el elemento de nodo interno que contiene la referencia a la clave de dato.
	if (!findINodeData(nodePointerKey))
		throw NodeException(NodeException::INVALID_REF);

	// Se lo pide al arbol
	Node* sucesor = this->m_tree->getNode(nodePointerKey.getLeftPointer());


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
		INodeData bigger(UNDEFINED_NODE_NUMBER,promotedKey.getKey());
		findINodeData(bigger/**,false**/);

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

	return result;
}

loadResultEnum InnerNode::remove(const InputData& data)
throw(NodeException)
{
	loadResultEnum result = NORMAL_LOAD;

	// Crea un INodeData con la clave que llega, para realizar la busqueda, por donde ir recorriendo.
	INodeData thiskey(UNDEFINED_NODE_NUMBER,data.getKey());

	// Busca el nodo interno que referencia a esa clave
	if (!findINodeData(thiskey))
		throw NodeException(NodeException::INVALID_REF);

	// traigo el sucesor de este innerNode y lo elimino.
	Node* sucesor = m_tree->getNode(thiskey.getLeftPointer());

	try
	{
		result = sucesor->remove(data);
	}
	catch(NodeException e)
	{
		throw;
	}

	if (result == UNDERFLOW_LOAD)
	{
		bool hasRightBrother = false;
		bool hasMinorBrother = false;

//		bool leftJoin = true;
		bool balanced = false;
		Node* rightSibling,*leftSibling;

		INodeData keymodified;

		INodeData joinBrother;

		// busco el hermano mayor a key para obtener el hijo derecho.
		INodeData bigBrother;
		hasRightBrother = findINodeData(thiskey,bigBrother,BIGGER);

		INodeData minorBrother;
		hasMinorBrother = findINodeData(thiskey,minorBrother,MINOR);

		//Verifico que tenga hermano derecho.
		if(hasRightBrother)
		{
//			joinBrother.setKey(bigBrother.getKey());
//			joinBrother.setLeftPointer(bigBrother.getLeftPointer());

			// Trato de balancear con el derecho.
			// Al redistribuir me devuelve la clave que hay que promover y modificar en thiskey.
			rightSibling = m_tree->getNode(bigBrother.getLeftPointer());
			balanced = redistribute(sucesor,rightSibling,data,keymodified,RIGHT_SIDE);
		}

		if (balanced)
			modifyINodeData(thiskey,keymodified);

		// Si no pudo, busco el sibling izquierdo, el hijo del hermano menor.
		if (!balanced)
		{
			//Verifica que tenga hermano izquierdo.
			if (hasMinorBrother)
				balanced = redistribute(sucesor,leftSibling,data,keymodified,LEFT_SIDE);


//			// Me busca el hermano menor.
//			unsigned int posicionNodo=this->buscarPosicionInnerPorClave(thiskey.getKey());
//			if(posicionNodo!=1){
//				this->getInPosition(&minorBrother,posicionNodo-1);
//				joinBrother.setKey(minorBrother.getKey());
//				joinBrother.setLeftPointer(minorBrother.getLeftPointer());
//
//				leftSibling = m_tree->getNode(minorBrother.getLeftPointer());
//				// Trato de balancear con el sibling izquierdo del sucesor.
//				balanced = redistribute(sucesor,leftSibling,data,keymodified,LEFT_SIDE);
//			}else
//				leftJoin=false;



			if (balanced)
//				modifyINodeData(joinBrother,keymodified);
				modifyINodeData(minorBrother,keymodified);

		}

		// Si no pudo balancear, fusiona.
		if (!balanced)
		{
			INodeData fusionatedNode;

			if(hasRightBrother)
			{
				merge(sucesor,rightSibling,data,fusionatedNode,RIGHT_SIDE);
//				result = removeINodeData(joinBrother);
				result = removeINodeData(thiskey);
				//Recupero clave del que borro y se a paso al que queda.
//				joinBrother.setLeftPointer(thiskey.getLeftPointer());
//				modifyINodeData(thiskey,joinBrother);
				modifyINodeData(bigBrother,fusionatedNode);
			}
			else
			{
				//
				merge(sucesor,leftSibling,data,fusionatedNode,LEFT_SIDE);
//				result = removeINodeData(joinBrother);
				result = removeINodeData(minorBrother);
				modifyINodeData(thiskey,fusionatedNode);
			}
		}

	}

	return result;
}





bool InnerNode::find(const InputData & key, InputData & data)
throw(NodeException)
{
	bool found = false;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData nodePointerKey(Node::UNDEFINED_NODE_NUMBER,key.getKey());

	// Busca el nodo interno que referencia a esa clave
	if (!findINodeData(nodePointerKey))
		throw NodeException(NodeException::INVALID_REF);;

	// traigo el sucesor de este innerNode.
	Node* sucesor = m_tree->getNode(nodePointerKey.getLeftPointer());

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

	if (iNodeData.getKey()==UNDEFINED_KEY)
		m_block->jumpEndCounter();

	while (iNodeData.getKey()!=UNDEFINED_KEY&&
			!m_block->isLastRegister()&&!found)
	{
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey()==UNDEFINED_KEY||
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

	m_tree->saveNode(this);

	return result;
}


bool InnerNode::findINodeData(INodeData& innerNodeElem,bool less)
{
	bool found = false;
	INodeData currentData(UNDEFINED_NODE_NUMBER,UNDEFINED_KEY);

	VarRegister reg;
	//Busca al sucesor que puede tener el dato
	m_block->restartCounter();
	//Itera una vez para obviar el dato de control.
	VarRegister level = this->m_block->getNextRegister();

	while(!m_block->isLastRegister()&& !found )
	{

		reg = this->m_block->peekRegister();
		// Transformo el registro a un INodeData
		currentData.toNodeData(reg.getValue());
		// UNDEFINED_KEY es la clave mayor a cualquier elemento.
		if(currentData.getKey()> innerNodeElem.getKey()||
		   currentData.getKey()==UNDEFINED_KEY)
		{
			found = true;
		}

		if (!found||!less)
			// Si no lo encontro sigue iterando. Si lo encontro pero se pide el mayor, avanza uno.
			this->m_block->getNextRegister();
	}

	innerNodeElem.setKey(currentData.getKey());
	innerNodeElem.setLeftPointer(currentData.getLeftPointer());

	return found;
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

				currentData.toNodeData(reg.getValue());

				if(condition  == EQUAL)
				{
					//Comparo si es igual o si es el ultimo registro
					if(currentData.getKey()== innerNodeElem.getKey()||  currentData.getKey()==UNDEFINED_KEY)
					{
						retFound=true;
						innerNodeFound = currentData;
					}
				}
				else
				{
					//Comparo si es mayor o si es el ultimo registro
					if(currentData.getKey()>innerNodeElem.getKey()||  currentData.getKey()==UNDEFINED_KEY)
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
				if(currentData.getKey()< innerNodeElem.getKey())
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
		currentRegister = m_block->getNextRegister();

		/// Transformo el registro a un INodeData
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey() == iNodeData.getKey())
		{
			// lo elimino
			found = true;
			m_block->deleteRegister(result);
		}

		if (!found)
			throw NodeException(NodeException::INEXISTENT_ELEMINNER);
	}


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
	VarRegister regData(newINodeData.toStream(valueReg),newINodeData.getSize());

	/// Busco donde insertar el dato dentro del bloque de nodo interno.
	m_block->restartCounter();
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();
//	VarRegister pointers = m_block->getNextRegister();
	unsigned int iterador=0;
	while (iterador<m_block->getRegisterAmount()&&!found)
	{
		iterador++;
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

	if (result!= NORMAL_LOAD)
		throw NodeException(NodeException::ANOMALOUS_LOADRESULT);


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

	Block* blockNode = node->getBlock();
	Block* blockSibling = siblingNode->getBlock();

	retVal = BlockManager::balanceLoad(blockNode,blockSibling,side);
	VarRegister firstKey;

	if(side==RIGHT_SIDE){
		// paso el dato de control
		blockSibling->getNextRegister();
		firstKey = blockSibling->getNextRegister();
		}else{
			// paso el dato de control
			blockNode->restartCounter();
			blockNode->getNextRegister();
			VarRegister firstKey = blockNode->getNextRegister();
		};

	if (node->isLeaf())
	{
		/// porque InputData es abstracto.
		currentData->toData(firstKey.getValue());
		keyToModify.setKey(currentData->getKey());
	}
	else
	{
		keyToModify.toNodeData(firstKey.getValue());
	}
	if(side==RIGHT_SIDE){
		keyToModify.setLeftPointer(node->getNodeNumber());
		}else{
			keyToModify.setLeftPointer(siblingNode->getNodeNumber());
		};

	delete currentData;

	return retVal;
}


bool InnerNode::merge(Node* node,Node* siblingNode,const InputData& data,INodeData& fusionatedNode,sideEnum side)
{
	bool retVal = false;
	InputData* currentData = data.newInstance();

	Block* blockNode = node->getBlock();
	Block* blockSibling = siblingNode->getBlock();

	BlockManager::merge(blockNode,blockSibling,side);

	// paso el dato de control
	blockNode->getNextRegister();
	VarRegister firstKey = blockNode->getNextRegister();

	if (node->isLeaf())
	{
		/// porque InputData es abstracto.
		currentData->toData(firstKey.getValue());
		fusionatedNode.setKey(currentData.getKey());
	}
	else
	{
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
	iNodeData.setKey(UNDEFINED_KEY);
	char* valueReg = new char[iNodeData.getSize()];
	iNodeData.toStream(valueReg);
	VarRegister regData(valueReg,iNodeData.getSize());
	m_block->modifyRegister(regData,result);

};
