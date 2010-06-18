/*
 * Ppmc.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */
#include "Ppmc.h"

//Ppmc::Ppmc(){
//
//}

Ppmc::Ppmc(GeneralStructure* generalStructure){
	this->generalStructure = generalStructure;
}

Ppmc::~Ppmc() {

}

void Ppmc::stoupper(std::string& s) {
	std::string::iterator i = s.begin();
	std::string::iterator end = s.end();

	while (i != end) {
		*i = std::toupper((unsigned char)*i);
		++i;
	}
}

int Ppmc::createContext(std::string context) {
	string valor = "*/,1/-"; // * es el caracter de escape.
	try{
		this->generalStructure->insert(context, valor);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		return -1;
	}

	return 0;
}

bool Ppmc::existsCharacterInContext(std::string context, std::string character) {
	StringInputData stringInputData;
	try{
		this->generalStructure->find(context,stringInputData);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		return false;
	}
	// Si existe el contexto, lo obtengo y busco el caracter en su tabla.
	std::string contextTable = stringInputData.getValue();
	if (contextTable.find(character,0) != string::npos) { // Si encuentra el caracter en la tabla del contexto, devuelve true.
		return true;
	}
	return false;
}

int Ppmc::addCharacterToContext(std::string context, std::string character) {
	if (this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData stringInputData;
	try{
		this->generalStructure->find(context,stringInputData);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		return -1;
	}
	std::string contextTable = stringInputData.getValue();
	contextTable.append(character); // Agrega el caracter al contexto.
	contextTable.append("/,1/-"); // Inicialmente, el caracter se agrega con una ocurrencia.
	try{
		this->generalStructure->modify(context, contextTable);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		return -1;
	}
	return 0;
}

int Ppmc::increaseFrequency(std::string context, std::string character) {
	if (!this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData stringInputData;
		try{
			this->generalStructure->find(context,stringInputData);
		}
		catch(ManagerException &e)
		{
			cout << e.what()<<endl;
			return -1;
		}
	std::string contextTable = stringInputData.getValue();
	std::string newContextTable = "";

	size_t characterIndex = contextTable.find(character,0); // Busca el indice del caracter.
	size_t dashIndex = contextTable.find("/-",characterIndex); // Busca el primer guión luego del caracter.

	newContextTable.append(contextTable,0,characterIndex+1); // Copia la cadena vieja a la nueva, hasta encontrar la letra inclusive.
	newContextTable.append("/,");

	std::string stringOccurrences = contextTable.substr(characterIndex+3,dashIndex-characterIndex-3);
	int occurrences = atoi(stringOccurrences.c_str());
	occurrences++;

	std::string newStringOccurrences;
	std::stringstream aux;
	aux << occurrences;
	newStringOccurrences = aux.str();

	newContextTable.append(newStringOccurrences); // Agrega la cantidad de ocurrencias anterior, mas 1.
	newContextTable.append("/-");
	newContextTable.append(contextTable, contextTable.find("-",characterIndex)+1, contextTable.length());
	try{
		this->generalStructure->modify(context, newContextTable);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		return -1;
	}
	return 0;
}


int Ppmc::getCharacterOccurrences(std::string context, std::string character) {
	if (!this->existsCharacterInContext(context, character)) {
		//todo: esta bien que retorne 1 aca?
		return 1;
	}

	StringInputData stringInputData;
	try{
		this->generalStructure->find(context,stringInputData);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		return -1;
	}

	std::string contextTable = stringInputData.getValue();

	size_t characterIndex = contextTable.find(character,0); // Busca el indice del caracter.
	size_t dashIndex = contextTable.find("/-",characterIndex); // Busca el primer guión luego del caracter.

	std::string stringOccurrences = contextTable.substr(characterIndex+3,dashIndex-characterIndex-3);
	int occurrences = atoi(stringOccurrences.c_str());
	return occurrences;
}


int Ppmc::getTotalOccurencesFromContext(std::string context) {
	int occurrences = 0;
	StringInputData stringInputData;
	try{
		this->generalStructure->find(context,stringInputData);
	}
	catch(ManagerException &e)
	{
		cout << e.what()<<endl;
		//todo Esta bien que retorne -1 aca? yo haria que estos metodos retornen un bool
		return -1;
	}

	std::string contextTable = stringInputData.getValue();

	while (contextTable.find("/,",0) != string::npos) {
		size_t commaIndex = contextTable.find("/,",0);
		size_t dashIndex = contextTable.find("/-",0);
		std::string stringOccurrences = contextTable.substr(commaIndex+2,dashIndex-3);
		occurrences += atoi(stringOccurrences.c_str());
		contextTable.replace(0,dashIndex+2,"");
	}

	return occurrences;
}









