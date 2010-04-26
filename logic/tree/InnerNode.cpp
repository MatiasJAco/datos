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

InnerNode::InnerNode(unsigned int nodeNumber,unsigned int level)
:Node(nodeNumber,level)
{
}


loadResultEnum InnerNode::insert(const InputData & dato){
//	comparo el dato con las claves

	VarRegister reg;
	int claveBuscada=dato.getKey();
	bool found=false;

	//Busca al sucesor que puede tener el dato
	m_block->restartCounter();
	//Itera una vez para obviar el dato de control.
	VarRegister level = this->m_block->getNextRegister();
	INodeData* contenido=new INodeData(0,0);

	while(!m_block->isLastRegister()&& !found ){

		reg=this->m_block->getNextRegister();
		// Transformo el registro a un INodeData
		contenido->toNodeData(reg.getValue());
		if(contenido->getKey()<dato.getKey()){
			found=true;
		}

	};

//Se lo pide al arbol
	Node* sucesor=this->m_tree->getNode(contenido->getLeftPointer());
	loadResultEnum result=sucesor->insert(dato);

	if (result==OVERFLOW_LOAD){

	//crear nodo y redistribuir
		int newNodeNumber=0;
		if(sucesor->isLeaf()){


			LeafNode* nuevoNodo=(LeafNode*)this->m_tree->newLeafNode();
			sucesor->divide(nuevoNodo);
			newNodeNumber=nuevoNodo->getNodeNumber();

		}else{
			InnerNode* nuevoNodo=(InnerNode*)this->m_tree->newInnerNode(sucesor->getLevel());
			sucesor->divide(nuevoNodo);
			newNodeNumber=nuevoNodo->getNodeNumber();
		};
		VarRegister regActual;

		//Itera una vez para obviar el dato de control.
		this->m_block->restartCounter();
		this->m_block->getNextRegister();

		while(!m_block->isLastRegister()&& !found ){

			reg=this->m_block->getNextRegister();
			// Transformo el registro a un INodeData
			contenido->toNodeData(reg.getValue());
			if(contenido->getKey()<dato.getKey()){
				found=true;
			}
		}

		if (claveBuscada<contenido->getKey()){
				INodeData* nuevoContenido= new INodeData(newNodeNumber,contenido->getKey());
				contenido->setKey(dato.getKey());
				char* stream;
				reg.setValue(contenido->toStream(stream),sizeof(*contenido));
				VarRegister* nuevoRegistro=new VarRegister(nuevoContenido->toStream(stream),sizeof(*nuevoContenido));

				this->m_block->addRegister(*nuevoRegistro);
		};

	};
	return NORMAL_LOAD;
}

loadResultEnum InnerNode::remove(const InputData & dato){
	//	comparo el dato con las claves

		VarRegister reg;

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
			if(contenido->getKey()<dato.getKey()){
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
		//	int cantNecesaria=sucesor->getBranchFactor()-sucesor->getUsedSpace();
			Node* hermanoEqui=this->m_tree->getNode(hermano->getLeftPointer());

			if(hermanoEqui->remove(dato)!=UNDERFLOW_LOAD){
			//	hermanoEqui->donate(sucesor,cantNecesaria);

			}else{
			//sino fusionar
				sucesor->join(hermanoEqui);
			}


		//
	//
	}
	return NORMAL_LOAD;
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

unsigned int InnerNode::getUsedSpace()
{
	throw "Hay que quitar este metodo! se hace control desde el Block";
	return 0;
}


void InnerNode::divide(Node* destNode){
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}


void InnerNode::join(Node* fusionNode){
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}

void InnerNode::donate(Node* destNode,unsigned int toDonate)
{
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}

bool InnerNode::falseRemove(unsigned int toRemove)
{
	throw "Todos estos metodos hay que reveerlos con la interfaz BlockManager y Block!!";
}


