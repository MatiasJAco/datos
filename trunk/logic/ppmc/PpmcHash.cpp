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

int PpmcHash::saveContext(const char* context, std::string value){
	//TODO pablo - comente el add para q ande
	//return this->hash->add(atoi(context), value);
	return 0;
}

bool PpmcHash::findContext(const char* context, char character, std::string & value){
	//TODO hay que llamar al get de hash
	return true;
}

void PpmcHash::stoupper(std::string& s)
{
	std::string::iterator i = s.begin();
	std::string::iterator end = s.end();

	while (i != end) {
		*i = std::toupper((unsigned char)*i);
		++i;
	}
}

int PpmcHash::getNumberForLetter(std::string letter)
{
	this->stoupper(letter);
	const char* character = letter.c_str();
	int i = static_cast<int>(*character);
	return i-65;
}

int PpmcHash::generateContext(std::string context, std::string letter) {
	int letterNumber = this->getNumberForLetter(letter);
	std::string contextTable = "";

	for (int i = 0; i < letterNumber; i++) {
		contextTable.append("0");
	}

	contextTable.append("1");

	for (int i = letterNumber; i < 25; i++) {
		contextTable.append("0");
	}

	this->saveContext(contextTable.c_str(), contextTable);
	return 0;
}

bool PpmcHash::compress(std::string path,int context){
	std::cout<<path;
	return true;
}

bool PpmcHash::deCompress(const std::string & path){
	return false;
}

void PpmcHash::getStatistics(){
}
