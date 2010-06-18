/*
 * PpmcHash.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#include "PpmcHash.h"

PpmcHash::PpmcHash() : Ppmc(this->hash = new Hash()){}

PpmcHash::~PpmcHash() {
	delete this->hash;
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
