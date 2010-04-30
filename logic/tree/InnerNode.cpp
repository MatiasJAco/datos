/**
 * @file InnerNode.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "InnerNode.h"
#include <sstream>
using namespace std;


InnerNode::InnerNode(){}

InnerNode::InnerNode(unsigned int nodeNumber)
:Node(nodeNumber)
{
}

InnerNode::InnerNode(unsigned int nodeNumber,unsigned int level,Block* block,BPlusTree* pointerTree)
//:Node(nodeNumber,level,block,pointerTree)
:Node(nodeNumber,level,block)
{
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



loadResultEnum InnerNode::modify(const InputData & dato, const InputData & dato2)
{

	loadResultEnum result = NORMAL_LOAD;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData nodePointerKey(Node::UNDEFINED_NODE_NUMBER,dato.getKey());

	// Busco el elemento de nodo interno que contiene la referencia a la clave de dato.
	if (!findINodeData(nodePointerKey))
		throw "Error: llego clave a una referencia invalida";

	// Se lo pide al arbol
	Node* sucesor = this->m_tree->getNode(nodePointerKey.getLeftPointer());
	result=sucesor->modify(dato,dato2);
	if (result==OVERFLOW_LOAD){
		//TODO implementar este caso
	}else{
		if(result==UNDERFLOW_LOAD){
			//TODO implementar este caso
		};
	};

	return NORMAL_LOAD;
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
{
	loadResultEnum result = NORMAL_LOAD;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData nodePointerKey(Node::UNDEFINED_NODE_NUMBER,data.getKey());

	// Busco el elemento de nodo interno que contiene la referencia a la clave de dato.
	if (!findINodeData(nodePointerKey))
		throw "Error: llego clave a una referencia invalida";

	// Se lo pide al arbol
	Node* sucesor = this->m_tree->getNode(nodePointerKey.getLeftPointer());


	// Inserta en el hijo y regresa la clave a promover..
	result = sucesor->insert(data,promotedKey);

	// Si hubo overflow tuvo que promover una clave.
	if (result == OVERFLOW_LOAD)
	{
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
	}

	return result;
}

loadResultEnum InnerNode::remove(const InputData& data)
{
	loadResultEnum result = NORMAL_LOAD;

	// Crea un INodeData con la clave que llega, para realizar la busqueda, por donde ir recorriendo.
	INodeData thiskey(UNDEFINED_NODE_NUMBER,data.getKey());

	// Busca el nodo interno que referencia a esa clave
	if (!findINodeData(thiskey))
		throw "Error! llego una clave a una referencia invalida!";

	// traigo el sucesor de este innerNode y lo elimino.
	Node* sucesor = m_tree->getNode(thiskey.getLeftPointer());

	result = sucesor->remove(data);

	if (result == UNDERFLOW_LOAD)
	{
		bool hasRightBrother=false;
		bool leftJoin=true;
		bool balanced = false;
		Node* rightSibling;
		Node* leftSibling;
		INodeData joinBrother;

		// busco el hermano mayor a key para obtener el hijo derecho.
		INodeData bigBrother(UNDEFINED_NODE_NUMBER,thiskey.getKey());
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
			balanced = redistribute(sucesor,rightSibling,data,bigBrother,RIGHT_SIDE);
		};

		if (balanced)
			modifyINodeData(thiskey,bigBrother);

		// Si no pudo, busco el sibling izquierdo, el hijo del hermano menor.
		if (!balanced)
		{
			//Verifica que tenga hermano izquierdo.
			INodeData minorBrother(UNDEFINED_NODE_NUMBER,thiskey.getKey());
			findINodeData(minorBrother);
			unsigned int posicionNodo=this->buscarPosicionInnerPorClave(thiskey.getKey());
			if(posicionNodo!=1){
				this->getInPosition(&minorBrother,posicionNodo-1);
				joinBrother.setKey(minorBrother.getKey());
				joinBrother.setLeftPointer(minorBrother.getLeftPointer());
				leftSibling = m_tree->getNode(minorBrother.getLeftPointer());
				// Trato de balancear con el sibling izquierdo del sucesor.
				balanced = redistribute(sucesor,leftSibling,data,minorBrother,LEFT_SIDE);
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
				merge(sucesor,leftSibling,data,fusionatedNode,LEFT_SIDE);
				result = removeINodeData(joinBrother);
			}else{
				merge(sucesor,rightSibling,data,fusionatedNode,RIGHT_SIDE);
				result = removeINodeData(joinBrother);
				//Recupero clave del que borro y se a paso al que queda.
				joinBrother.setLeftPointer(thiskey.getLeftPointer());
				modifyINodeData(thiskey,joinBrother);

			};

		}

	}

	return result;
}





bool InnerNode::find(const InputData & key, InputData & data)
{
	bool found = false;

	// Elemento de nodo interno con referencia a la clave a insertar.
	INodeData nodePointerKey(Node::UNDEFINED_NODE_NUMBER,data.getKey());

	// Busca el nodo interno que referencia a esa clave
	if (!findINodeData(nodePointerKey))
		throw "Error! llego una clave a una referencia invalida!";

	// traigo el sucesor de este innerNode.
	Node* sucesor = m_tree->getNode(nodePointerKey.getLeftPointer());

	found = sucesor->find(key,data);


	return found;
}

loadResultEnum InnerNode::insertINodeData(const INodeData& iNodeData,INodeData& promotedKey)
{
	/// Trata de insertar un elemento INodeData y si dio overflow hace el split.
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	VarRegister currentRegister;
	INodeData currentData;

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[iNodeData.getSize()];
	VarRegister regData(iNodeData.toStream(valueReg),iNodeData.getSize());

	/// Busco donde insertar el dato dentro del bloque de nodo interno.
	m_block->restartCounter();
	unsigned int pos = 0;
	/// Tengo que avanzar primero los datos de control siempre.
	/// TODO ver si poner esto dentro de un metodo de Nodo.
	VarRegister level = m_block->getNextRegister();

	while (pos<m_block->getRegisterAmount()&&!found)
	{
		pos++;
		currentRegister = m_block->peekRegister();

		/// Transformo el registro a un INodeData
		currentData.toNodeData(currentRegister.getValue());
		if (currentData.getKey() >= iNodeData.getKey())
		{
			found = true;
			if (currentData.getKey() == iNodeData.getKey())
				throw "Duplicado en insert de Nodo Interno";
		}else

		currentRegister = m_block->getNextRegister();
	}

	/// Lo agrega al final si no lo encontro
	m_block->addRegister(regData,result);

	if (result == OVERFLOW_LOAD)
		split(iNodeData,pos,promotedKey);

	return result;
}


bool InnerNode::findINodeData(INodeData& innerNodeElem,bool less)
{
	bool found = false;
	INodeData currentData;

	VarRegister reg;
	//Busca al sucesor que puede tener el dato
	m_block->restartCounter();
	//Itera una vez para obviar el dato de control.
	VarRegister level = this->m_block->getNextRegister();
	unsigned int iterador;
	while(iterador<m_block->getRegisterAmount()&& !found )
	{
		iterador++;
		reg = this->m_block->peekRegister();
		// Transformo el registro a un INodeData
		currentData.toNodeData(reg.getValue());
		if(currentData.getKey()> innerNodeElem.getKey())
		{
			found = true;
		}

		if (!found||!less)
			// Si no lo encontro sigue iterando. Si lo encontro pero se pide el mayor, avanza uno.
			this->m_block->getNextRegister();
	}

	if(!less){
		reg = this->m_block->peekRegister();
		// Transformo el registro a un INodeData
		currentData.toNodeData(reg.getValue());
	};
	// Devuelve el menor a key o el mayor segun less.
	innerNodeElem.setKey(currentData.getKey());
	innerNodeElem.setLeftPointer(currentData.getLeftPointer());

	return found;
}


loadResultEnum InnerNode::removeINodeData(const INodeData& iNodeData)
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
			throw "No existe el elemento a remover";
	}


	return result;
}

loadResultEnum InnerNode::modifyINodeData(const INodeData& iNodeData)
{
	loadResultEnum result = NORMAL_LOAD;

	bool found = false;

	VarRegister currentRegister;
	INodeData currentData;

	// Creo el registro para poder insertarlo en el bloque.
	char* valueReg = new char[iNodeData.getSize()];
	VarRegister regData(iNodeData.toStream(valueReg),iNodeData.getSize());

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
				throw "No existe el elemento a modificar";

	if (result!= NORMAL_LOAD)
		throw "Esta devolviendo estado de carga anormal. No deberia, es de tamaño fijo y ya existia!";


	return result;
}

loadResultEnum InnerNode::modifyINodeData(const INodeData& iNodeData,const INodeData& newINodeData)
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
				throw "No existe el elemento a modificar";

	if (result!= NORMAL_LOAD)
		throw "Esta devolviendo estado de carga anormal. No deberia, es de tamaño fijo y ya existia!";


	return result;

}

bool InnerNode::split(const INodeData& data,unsigned int pos,INodeData& promotedKey)
{
	InnerNode* sibling = (InnerNode*)m_tree->newInnerNode(getLevel());
	Block* blockSibling = sibling->getBlock();

	char* valueReg = new char[data.getSize()];
	VarRegister reg(data.toStream(valueReg),data.getSize());

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
		fusionatedNode.setKey(data.getKey());
	}
	else
	{
		fusionatedNode.toNodeData(firstKey.getValue());
	}
	fusionatedNode.setLeftPointer(node->getNodeNumber());

	delete currentData;

	return retVal;
}
