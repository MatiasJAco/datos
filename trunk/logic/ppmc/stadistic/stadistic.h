/*
 * stadistic.h
 *
 *  Created on: 26/06/2010
 *      Author: matias
 */

#ifndef STADISTIC_H_
#define STADISTIC_H_


#include <string>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include <iostream>
using namespace std;

class Stadistic {

private:
	string contextsHits;


public:
	Stadistic();
	virtual ~Stadistic();
	int getFileSize(char* filename);




};


#endif /* STADISTIC_H_ */
