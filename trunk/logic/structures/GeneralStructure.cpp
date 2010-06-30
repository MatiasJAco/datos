/*
 * GeneralStructure.cpp
 *
 *  Created on: Jun 18, 2010
 *      Author: pablolisio
 */

#include "GeneralStructure.h"

GeneralStructure::GeneralStructure() {
}

GeneralStructure::~GeneralStructure() {
}

bool GeneralStructure::getPrevious(InputData& data) {
	string key="";
	return this->find(key,data);
}
