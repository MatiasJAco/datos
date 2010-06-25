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
	//Invierto la clave.
	string claveInvertida = string(clave.rbegin(), clave.rend());
	return this->generalStructure->insert(claveInvertida,valor);
}

bool PpmcTree::existsElementInStructure(std::string key){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	return this->generalStructure->existsElement(claveInvertida) ;
}

bool PpmcTree::findInStructure(std::string key, InputData & data) throw (ManagerException){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	return this->generalStructure->find(claveInvertida,data);
}

bool PpmcTree::modifyInStructure(std::string key, std::string newValue) throw (ManagerException){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	return this->generalStructure->modify(key,newValue);
}

bool PpmcTree::removeInStructure(std::string key) throw (ManagerException){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	return this->generalStructure->remove(key);
}

bool PpmcTree::getNextContext(std::string key, InputData & data) throw (ManagerException){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	StringInputData comparado;
	bool encontrado=false;
	this->generalStructure->getPrevious(comparado);
	while ((!encontrado)&&(comparado.getKey()<=key)){
		if(comparado.getKey()==key){
			data.setKey(comparado.getKey());
			data.setValue(comparado.getValue());
			encontrado=true;
		}
		if(!encontrado)
			this->generalStructure->getPrevious(comparado);
	};
	return encontrado;

}
