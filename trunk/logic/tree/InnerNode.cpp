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


bool InnerNode::insert(const InputData & dato)
{
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

void InnerNode::divide(){


}

