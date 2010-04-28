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



loadResultEnum InnerNode::remove(const InputData & dato){
	//	comparo el dato con las claves

		VarRegister reg;
		loadResultEnum resultOperation=NORMAL_LOAD;
		bool found=false;

		//Busca al sucesor que puede tener el dato
		m_block->restartCounter();
		//Itera una vez para obviar el dato de control.
		VarRegister level = this->m_block->getNextRegister();
		INodeData* contenido=new INodeData(0,0);
		INodeData* hermano=new INodeData(0,0);

		while(!m_block->isLastRegister()&& !found ){

			reg=this->m_block->getNextRegister();
			// Transformo el registro a un INodeData
			contenido->toNodeData(reg.getValue());
			if(contenido->getKey()>dato.getKey()){
				found=true;
			}

		};

	//Se lo pide al arbol
	Node* sucesor=this->m_tree->getNode(contenido->getLeftPointer());
		loadResultEnum result=sucesor->remove(dato);
	if (result==UNDERFLOW_LOAD){
	//intentar balancear con el hermano derecho

			reg=this->m_block->getNextRegister();
			hermano->toNodeData(reg.getValue());

			Node* hermanoEqui=this->m_tree->getNode(hermano->getLeftPointer());


		    if(!this->balanceLeaf(sucesor,hermanoEqui,dato)){
			//sino fusionar
				this->join(sucesor,hermanoEqui,dato);
				//Reemplazo la clave del nodo siguiente a ambos en el nodo fusionado.

				contenido->setKey(hermano->getKey());
				INodeData* contBuscado=new INodeData(0,0);
				//Busco el registro correspondiente al nodo fusionado y lo modifico.
				while(!m_block->isLastRegister()&& !found ){
					reg=this->m_block->peekRegister();
					// Transformo el registro a un INodeData
					contBuscado->toNodeData(reg.getValue());
					if(contenido->getKey()<contBuscado->getKey()){
						found=true;
					}else{
							this->m_block->getNextRegister();
					};

				};

				VarRegister registroModificado;
				char* valueReg = new char[contenido->getSize()];
				registroModificado.setValue(contenido->toStream(valueReg),contenido->getSize());
				this->m_block->modifyRegister(reg);

				this->m_block->deleteRegister(resultOperation);
			}


		//
	//
	}
	return resultOperation;
}

loadResultEnum InnerNode::modify(const InputData & dato, const InputData & dato2)
{
	return NORMAL_LOAD;
}

loadResultEnum InnerNode::modify(const InputData& data)
{
	return NORMAL_LOAD;
}

bool InnerNode::find(const InputData & key,InputData & data) const
{
	return true;
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
		if(currentData.getKey()>= innerNodeElem.getKey())
		{
			found = true;
		}

		if (!found||!less)
			// Si no lo encontro sigue iterando. Si lo encontro pero se pide el mayor, avanza uno.
			this->m_block->getNextRegister();
	}

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

	// falta lo de la redistribucion o fusion.


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
