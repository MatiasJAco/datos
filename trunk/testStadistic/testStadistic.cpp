/*
 * testStadistic.cpp
 *
 *  Created on: 26/06/2010
 *      Author: matias
 */

using namespace std;
#include "../logic/ppmc/stadistic/stadistic.h"

int main(int argc, char *argv[]){
	char  path [20];

	Stadistic* miEstadista=new Stadistic();
	strcpy(path,"archivo");
	int tamanio=miEstadista->getFileSize(path);

	printf("El archivo es de %d",tamanio);
	delete miEstadista;

};
