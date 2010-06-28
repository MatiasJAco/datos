/*
 * TestStadistic.cpp
 *
 *  Created on: Jun 27, 2010
 *      Author: adrian
 */

#include "TestStadistic.h"
#include "../application/compresion/ppmc/stadistic/stadistic.h"

TestStadistic::TestStadistic() {
}

TestStadistic::~TestStadistic() {
}

void TestStadistic::testStadistic() {
	char  path [20];

	Stadistic* miEstadista=new Stadistic();
	strcpy(path,"archivo");
	int tamanio=miEstadista->getFileSize(path);

	printf("El archivo es de %d",tamanio);
	delete miEstadista;
}
