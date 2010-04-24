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
	char* clave =NULL;
	int claveBuscada=dato.getKey();
	INodeData* contenido=new INodeData(0,0);
	do{
	clave=this->m_bloque->getNextRegister().getValue();
	this->castear(*contenido,clave);


	}while((claveBuscada<(int)clave) );
	this->m_bloque->restartCounter();

//encuentra al sucesor que puede tener el dato
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
		VarRegister regAnterior;
		int cont=0;
		do{
			regAnterior=regActual;
			cont++;
			regActual=this->m_bloque->getNextRegister();
			this->castear(*contenido,regActual.getValue());
		}while(claveBuscada>contenido->getKey() );

		if (claveBuscada<contenido->getKey()){
				INodeData* nuevoContenido= new INodeData((sucesor->getNodeNumber()+1),contenido->getKey());
				contenido->setKey(dato.getKey());
				char* stream;
				regActual.setValue(contenido->toStream(stream),sizeof(*contenido));
				nuevoContenido->getKey();

		};



//
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



bool InnerNode::castear(INodeData& contenido,char * stream)
{
	bool retVal=false;

	if(stream!=NULL)
	{


		int key=0;
		memcpy(&key,stream,sizeof(key));

		int  leftPointer=0;

		memcpy(&leftPointer,stream+sizeof(int),sizeof(int));
		contenido.setKey(key);
		contenido.setLeftPointer(leftPointer);

		retVal=true;
	}
	return retVal;
}

bool InnerNode::isLeaf(){
	return false;
	};

void InnerNode::divide(Node* destNode){
};
