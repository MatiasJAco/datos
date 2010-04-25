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

bool InnerNode::find(const InputData & dato,const InputData & dato2) const
{
	return true;
}


loadResultEnum InnerNode::insert(const InputData & dato){
//	comparo el dato con las claves

	int claveInt;
	int punteroIzq;
	char* reg;
	int claveBuscada=dato.getKey();
//encuentra al sucesor que puede tener el dato
	//Itera una vez para obviar el dato de control.
	this->m_block->getNextRegister();

	do{
		reg=this->m_block->getNextRegister().getValue();
		punteroIzq=	ByteConverter::bytesToInt(reg);
		claveInt = ByteConverter::bytesToInt(reg+sizeof(int));

	}while((claveBuscada > claveInt ) );

	this->m_block->restartCounter();

	INodeData* contenido=new INodeData(punteroIzq,claveInt);

//se lo pide al arbol
	Node* sucesor=this->m_tree->getNode(contenido->getLeftPointer());
	sucesor->insert(dato);
	if (sucesor->overflow()){
//crear nodo y redistribuir

		if(sucesor->isLeaf()){
			LeafNode* nuevoNodo=NULL;
			sucesor->divide(nuevoNodo);

		}else{
			InnerNode* nuevoNodo=NULL;
			sucesor->divide(nuevoNodo);
		};
		VarRegister regActual;

		//Itera una vez para obviar el dato de control.
		this->m_block->getNextRegister();
		do{


			regActual=this->m_block->getNextRegister();

			claveInt = ByteConverter::bytesToInt(regActual.getValue()+sizeof(int));

		}while((claveBuscada > claveInt ));

		if (claveBuscada<contenido->getKey()){
				INodeData* nuevoContenido= new INodeData(m_tree->getNodeQuantity(),contenido->getKey());
				contenido->setKey(dato.getKey());
				char* stream;
				regActual.setValue(contenido->toStream(stream),sizeof(*contenido));
				VarRegister* nuevoRegistro=new VarRegister(nuevoContenido->toStream(stream),sizeof(*nuevoContenido));

				this->m_block->addRegister(*nuevoRegistro);
		};
	}

	return NORMAL_LOAD;
}

loadResultEnum InnerNode::remove(const InputData & dato){
	//	comparo el dato con las claves

	int claveInt;
	int punteroIzq;
	char* reg;
	int claveBuscada=dato.getKey();
	//encuentra al sucesor que puede tener el dato
	//Itera una vez para obviar el dato de control.
	this->m_block->getNextRegister();
	do{
		reg=this->m_block->getNextRegister().getValue();
		punteroIzq=	ByteConverter::bytesToInt(reg);
		claveInt = ByteConverter::bytesToInt(reg+sizeof(int));
	}while((claveBuscada > claveInt ) );

	this->m_block->restartCounter();

	INodeData* contenido=new INodeData(punteroIzq,claveInt);

	//se lo pide al arbol
	Node* sucesor=this->m_tree->getNode(contenido->getLeftPointer());
	sucesor->remove(dato);
	if (sucesor->underflow()){
	//		//intentar balancear con el hermano derecho

			reg=this->m_block->getNextRegister().getValue();
			punteroIzq=	ByteConverter::bytesToInt(reg);
			claveInt = ByteConverter::bytesToInt(reg+sizeof(int));
			int cantNecesaria=sucesor->getBranchFactor()-sucesor->getUsedSpace();
			Node* hermanoEqui=this->m_tree->getNode(contenido->getLeftPointer());
			if(hermanoEqui->falseRemove(cantNecesaria)){
				hermanoEqui->donate(sucesor,cantNecesaria);

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


