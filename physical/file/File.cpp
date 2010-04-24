/*
 * File.cpp
 *
 *  Created on: 22/04/2010
 *      Author: alex
 */

#include "File.h"

using namespace std;
File::File()
{


}

File::~File()
{
}

bool File::resize(unsigned int size)
{
	bool retVal=false;

	if (truncate(m_FileName.c_str(), size)==0)
		retVal=true;

	return retVal;
}


