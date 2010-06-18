/*
 * PpmcTree.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#include "PpmcTree.h"

PpmcTree::PpmcTree() {
	StringInputData typedata("4","hola");
	this->tree = new BPlusTree("arbol.dat",95,0.5,typedata);
}

PpmcTree::~PpmcTree() {
	delete this->tree;
}

bool PpmcTree::saveContext(const char* context, std::string value){
	//TODO hay que llamar al insert de tree aca
	return true;
}

bool PpmcTree::findContext(const char* context, char character, std::string & value){
	//TODO hay que llamar al get de tree
	return true;
}


int PpmcTree::createContext(std::string context) {

	this->tree->insert(context,"27,1-"); // 27 es el caracter de escape.
	return 0;
}

bool PpmcTree::existsCharacterInContext(std::string context, std::string character) {
	StringInputData datoDevuelto("","");

	bool exists = this->tree->find(context,datoDevuelto);
	if (exists) { // Si existe el contexto, lo obtengo y busco el caracter en su tabla.
		std::string contextTable = datoDevuelto.getValue();
		if (contextTable.find(character,0) != string::npos) { // Si encuentra el caracter en la tabla del contexto, devuelve true.
			return true;
		}
	}
	return false;
}

int PpmcTree::addCharacterToContext(std::string context, std::string character) {
	if (this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData stringInputData("","");
	this->tree->find(context,stringInputData);
	std::string contextTable = stringInputData.getValue();
	contextTable.append(character); // Agrega el caracter al contexto.
	contextTable.append(",1-"); // Inicialmente, el caracter se agrega con una ocurrencia.
	stringInputData.setValue(contextTable);
	this->tree->modify(context,stringInputData.getValue());
	return 0;
}

int PpmcTree::increaseFrequency(std::string context, std::string character) {
	if (!this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData stringInputData("","");
	this->tree->find(context,stringInputData);
	std::string contextTable = stringInputData.getValue();
	std::string newContextTable = "";

	size_t characterIndex = contextTable.find(character,0); // Busca el indice del caracter.
	size_t dashIndex = contextTable.find("-",characterIndex); // Busca el primer guión luego del caracter.

	newContextTable.append(contextTable,0,characterIndex+1); // Copia la cadena vieja a la nueva, hasta encontrar la letra inclusive.
	newContextTable.append(",");

	std::string stringOccurrences = contextTable.substr(characterIndex+2,dashIndex);
	int occurrences = atoi(stringOccurrences.c_str());
	occurrences++;

	std::string newStringOccurrences;
	std::stringstream aux;
	aux << occurrences;
	newStringOccurrences = aux.str();

	newContextTable.append(newStringOccurrences); // Agrega la cantidad de ocurrencias anterior, mas 1.
	newContextTable.append("-");
	newContextTable.append(contextTable, contextTable.find("-",characterIndex)+1, contextTable.length());
	stringInputData.setValue(newContextTable);
	this->tree->modify(context,stringInputData.getValue());
	return 0;
}

int PpmcTree::getCharacterOccurrences(std::string context, std::string character) {
	if (!this->existsCharacterInContext(context, character)) {
		return 1;
	}

	StringInputData stringInputData("","");
	this->tree->find(context,stringInputData);
	std::string contextTable = stringInputData.getValue();

	size_t characterIndex = contextTable.find(character,0); // Busca el indice del caracter.
	size_t dashIndex = contextTable.find("-",characterIndex); // Busca el primer guión luego del caracter.

	std::string stringOccurrences = contextTable.substr(characterIndex+2,dashIndex);
	int occurrences = atoi(stringOccurrences.c_str());
	return occurrences;
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

void PpmcTree::showContexts(){
	StringInputData data;
	this->tree->showTree(data);

};

void PpmcTree::getStatistics(){

};

