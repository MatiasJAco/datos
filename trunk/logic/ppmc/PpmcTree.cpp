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
	return this->generalStructure->modify(claveInvertida,newValue);
}

bool PpmcTree::removeInStructure(std::string key) throw (ManagerException){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	return this->generalStructure->remove(claveInvertida);
}

bool PpmcTree::getNextContext(std::string key, InputData & data) throw (ManagerException){
	//Invierto la clave.
	string claveInvertida = string(key.rbegin(), key.rend());
	StringInputData comparado;
	bool encontrado=false;
	//Para saltear al ultimo buscado.
	this->generalStructure->getPrevious(comparado);
	this->generalStructure->getPrevious(comparado);
	//Comienza busqueda.
	while ((!encontrado)&&(comparado.getKey()>=claveInvertida)){
		if(comparado.getKey()==claveInvertida){
			data.setKey(comparado.getKey());
			data.setValue(comparado.getValue());
			encontrado=true;
		}
		if(!encontrado)
			this->generalStructure->getPrevious(comparado);
	};
	return encontrado;

}

void PpmcTree::printAllContexts()
{
	StringInputData stringInputData;

	bool hasLeaf = true;

	//TODO ver si valido arbol vacio
	((BPlusTree *) generalStructure)->getFirstElement(stringInputData);

	while(hasLeaf)
	{
		FrequencyTable ft;

		ft.deserialize(stringInputData.getValue());
		cout <<"Contexto: " <<stringInputData.getKey()<< " "<< ft.toPrintableString()<<endl;
		hasLeaf = ((BPlusTree *) generalStructure)->getNext(stringInputData);
	}
}
