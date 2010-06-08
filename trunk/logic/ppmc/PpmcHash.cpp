/*
 * PpmcHash.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#include "PpmcHash.h"

PpmcHash::PpmcHash() {
	// TODO Auto-generated constructor stub

}

PpmcHash::~PpmcHash() {
	// TODO Auto-generated destructor stub
}

bool PpmcHash::saveContext(const char* context, std::string value){
	//TODO hay que llamar al insert de hash aca
	return true;
}

bool PpmcHash::findContext(const char* context, char character, std::string & value){
	//TODO hay que llamar al get de hash
	return true;
}

bool Ppmc::compress(std::string path,int context){
	std::cout<<path;
	return true;
}

bool Ppmc::deCompress(const std::string & path){
	return false;
}


