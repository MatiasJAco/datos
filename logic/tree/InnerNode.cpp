/**
 * @file InnerNode.cpp
 *
 *  @date: 17/04/2010
 *  @author: kira
 */

#include "InnerNode.h"

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
	//comparo el dato con las claves
//	int cont=0;
//	char* clave =NULL;
//	int claveBuscada=dato.getKey();
//	do{
//
//	this->m_bloque->getNextRegister().serialize(clave);
//	if (claveBuscada<(int)clave)
//		cont++;
//
//	}while((claveBuscada=!(int)clave) &&(claveBuscada<(int)clave) );
//
//
//	//encuentra al sucesor que puede tener el dato
//	InnerNode* sucesor= new InnerNode();
//	sucesor->insert(dato);
//	if (sucesor->underflow()){
//		//intentar balancear
//		//sino fusionar
//
//	}else
//		if (sucesor->overflow()){
//			//crear nodo y redistribuir
//		}



	return true;
}

bool InnerNode::remove(const InputData & dato)
{
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

void InnerNode::divide(){


}

