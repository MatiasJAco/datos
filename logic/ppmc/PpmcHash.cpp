/*
 * PpmcHash.cpp
 *
 *  Created on: Jun 24, 2010
 *      Author: pablolisio
 */

#include "PpmcHash.h"

PpmcHash::PpmcHash(GeneralStructure* generalStructure): Ppmc(generalStructure){

}

PpmcHash::~PpmcHash() {

}



//-- Para el Hash se usan las primitivas como estaban

bool PpmcHash::insertInStructure(std::string clave, std::string valor) throw (ManagerException){
	return this->generalStructure->insert(clave,valor);
}

bool PpmcHash::existsElementInStructure(std::string key){
	return this->generalStructure->existsElement(key) ;
}

bool PpmcHash::findInStructure(std::string key, InputData & data) throw (ManagerException){
	return this->generalStructure->find(key,data);
}

bool PpmcHash::modifyInStructure(std::string key, std::string newValue) throw (ManagerException){
	return this->generalStructure->modify(key,newValue);
}

bool PpmcHash::removeInStructure(std::string key) throw (ManagerException){
	return this->generalStructure->remove(key);
}

bool PpmcHash::getNextContext(std::string key, InputData & data) throw (ManagerException){
	return this->generalStructure->find(key,data);
}
