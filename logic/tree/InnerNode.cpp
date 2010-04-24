/**
 * @file InnerNode.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "InnerNode.h"
#include <sstream>
using namespace std;


InnerNode::InnerNode(){};

InnerNode::InnerNode(unsigned int level,unsigned int size,double branch)
:Node(level,size,branch){
};

InnerNode::InnerNode(unsigned int number,unsigned int level,unsigned int size,double branch)
:Node(number,level,size,branch){

};

bool InnerNode::find(const InputData & dato,const InputData & dato2) const
{
	return true;
}


bool InnerNode::insert(const InputData & dato){
//	comparo el dato con las claves
	//char* clave = NULL;
	int claveInt;
	int punteroIzq;
	char* reg;
	int claveBuscada=dato.getKey();
//encuentra al sucesor que puede tener el dato
	do{
		reg=this->m_bloque->getNextRegister().getValue();
		punteroIzq=	ByteConverter::bytesToInt(reg);
		claveInt = ByteConverter::bytesToInt(reg+sizeof(int));

	}while((claveBuscada > claveInt ) );

	this->m_bloque->restartCounter();
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


		do{


			regActual=this->m_bloque->getNextRegister();

			claveInt = ByteConverter::bytesToInt(regActual.getValue()+sizeof(int));

		}while((claveBuscada > claveInt ));

		if (claveBuscada<contenido->getKey()){
				INodeData* nuevoContenido= new INodeData(m_tree->getNodeQuantity(),contenido->getKey());
				contenido->setKey(dato.getKey());
				char* stream;
				regActual.setValue(contenido->toStream(stream),sizeof(*contenido));
				VarRegister* nuevoRegistro=new VarRegister(nuevoContenido->toStream(stream),sizeof(*nuevoContenido));

				this->m_bloque->addRegister(*nuevoRegistro);
		};

	}


	return true;
}

bool InnerNode::remove(const InputData & dato){
	//	if (sucesor->underflow()){
	//		//intentar balancear
	//		//sino fusionar
	//

	return true;
}

bool InnerNode::modify(const InputData & dato, const InputData & dato2)
{
	return true;
}

unsigned int InnerNode::getUsedSpace()
{
	return 0;
}


bool InnerNode::isLeaf(){
	return false;
	};

void InnerNode::divide(Node* destNode){
};
