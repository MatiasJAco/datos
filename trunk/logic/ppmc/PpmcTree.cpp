/*
 * PpmcTree.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#include "PpmcTree.h"

PpmcTree::PpmcTree() : Ppmc(this->tree = new BPlusTree("arbol.dat",95,0.5)) {}

PpmcTree::~PpmcTree() {
	delete this->tree;
}

bool PpmcTree::compress(std::string path,int context){
	int result=0;
	std::string newContext="";
	while(result!=1){
		char readed;//=this->readNextCharacter(result);
		if(result!=1){
			newContext=newContext+readed;
			bool exists =false;
			exists=this->existsCharacterInContext(newContext,newContext);
			if (exists)
				this->increaseFrequency(newContext,newContext);
			};
		};
	std::cout<<path;
	return true;
}

bool PpmcTree::deCompress(const std::string & path){
	return false;
}

void PpmcTree::getStatistics(){

};


void PpmcTree::showContexts(){
	this->tree->print();
};

