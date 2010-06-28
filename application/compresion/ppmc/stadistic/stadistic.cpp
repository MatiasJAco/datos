/*
 * stadistic.cpp
 *
 *  Created on: 26/06/2010
 *      Author: matias
 */

#include "stadistic.h"


Stadistic::Stadistic(){
};

int Stadistic::getFileSize(char* filename){
	FILE* archivo;
	int size;
	archivo = fopen (filename, "rb");
	fseek(archivo, 0, SEEK_END); // Se posiciona al final del archivo
	size = ftell(archivo); // Devuelve la posición actual del archivo (en bytes)
	fclose(archivo);

	return size;


};

Stadistic::~Stadistic() {

}
