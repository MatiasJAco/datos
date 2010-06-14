/*
 * PpmcHash.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#include "PpmcHash.h"

PpmcHash::PpmcHash() {
	this->hash = new Hash();
}

PpmcHash::~PpmcHash() {
	delete this->hash;
}

void PpmcHash::stoupper(std::string& s) {
	std::string::iterator i = s.begin();
	std::string::iterator end = s.end();

	while (i != end) {
		*i = std::toupper((unsigned char)*i);
		++i;
	}
}

int PpmcHash::createContext(std::string context) {
	string valor = "27,1-"; // 27 es el caracter de escape.
	this->hash->add(context, valor);
	return 0;
}

bool PpmcHash::existsCharacterInContext(std::string context, std::string character) {
	bool exists = this->hash->existsElement(context);
	if (exists) { // Si existe el contexto, lo obtengo y busco el caracter en su tabla.
		StringInputData* stringInputData = this->hash->get(context);
		std::string contextTable = stringInputData->getValue();
		if (contextTable.find(character,0) != string::npos) { // Si encuentra el caracter en la tabla del contexto, devuelve true.
			return true;
		}
	}
	return false;
}

int PpmcHash::addCharacterToContext(std::string context, std::string character) {
	if (this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData* stringInputData = this->hash->get(context);
	std::string contextTable = stringInputData->getValue();
	contextTable.append(character); // Agrega el caracter al contexto.
	contextTable.append(",1-"); // Inicialmente, el caracter se agrega con una ocurrencia.
	this->hash->modify(context, contextTable);
	return 0;
}

int PpmcHash::increaseFrequency(std::string context, std::string character) {
	if (!this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData* stringInputData = this->hash->get(context);
	std::string contextTable = stringInputData->getValue();
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
	return 0;
}

int PpmcHash::getCharacterOccurrences(std::string context, std::string character) {
	if (!this->existsCharacterInContext(context, character)) {
		return 1;
	}
	StringInputData* stringInputData = this->hash->get(context);
	std::string contextTable = stringInputData->getValue();

	size_t characterIndex = contextTable.find(character,0); // Busca el indice del caracter.
	size_t dashIndex = contextTable.find("-",characterIndex); // Busca el primer guión luego del caracter.

	std::string stringOccurrences = contextTable.substr(characterIndex+2,dashIndex);
	int occurrences = atoi(stringOccurrences.c_str());
	return occurrences;
}

int PpmcHash::getTotalOccurencesFromContext(std::string context) {
	return 0;
}

bool PpmcHash::compress(std::string path,int context) {
	std::cout<<path;
	return true;
}

bool PpmcHash::deCompress(const std::string & path) {
	return false;
}

void PpmcHash::getStatistics() {
}
