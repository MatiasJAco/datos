/*
 * PpmcTree.cpp
 *
 *  Created on: Jun 24, 2010
 *      Author: pablolisio
 */

#include "PpmcTree.h"

PpmcTree::PpmcTree(GeneralStructure* generalStructure): Ppmc(generalStructure){


}

PpmcTree::~PpmcTree() {

}




//-- Para el Arbol NO se usan las primitivas como estaban - Hay que cambiarlas

bool PpmcTree::insertInStructure(std::string clave, std::string valor) throw (ManagerException){
	//TODO mati
	return this->generalStructure->insert(clave,valor);
}

bool PpmcTree::existsElementInStructure(std::string key){
	//TODO mati
	return this->generalStructure->existsElement(key) ;
}

bool PpmcTree::findInStructure(std::string key, InputData & data) throw (ManagerException){
	//TODO mati
	return this->generalStructure->find(key,data);
}

bool PpmcTree::modifyInStructure(std::string key, std::string newValue) throw (ManagerException){
	//TODO mati
	return this->generalStructure->modify(key,newValue);
}

bool PpmcTree::removeInStructure(std::string key) throw (ManagerException){
	//TODO mati
	return this->generalStructure->remove(key);
}

void PpmcTree::printStructure(){
	//TODO mati
	return this->generalStructure->print();
}

bool PpmcTree::deleteGeneratedFilesInStructure(){
	//TODO mati
	return this->generalStructure->deleteGeneratedFiles();
}
