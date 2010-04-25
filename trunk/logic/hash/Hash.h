/*
 * Hash.h
 *
 *  Created on: Apr 16, 2010
 *      Author: Adrián Bernardi
 */

#ifndef HASH_H_
#define HASH_H_

#include "../input/StringInputData.h"
#include "../../physical/file/BlockFile.h"
#include "Table.h"
#include "Bucket.h"
#include <list>

class Hash {

private:
	Table* hashTable;
	BlockFile* hashFile;


	/**
	 * Retorna el resultado de la funcion Hash. En este caso estamos usando el metodo de "bits sufijos"
	 */
	int calculateHashFunction(StringInputData* sid);

	/**
	 * Retorna el numero de Bucket del HashFile
	 */
	int getNumberOfBucket(StringInputData* sid);

	/**
	 * Crea un bucket (bucket numero 0). Este bucket solo tiene como campo de control el
	 * tamaño de dispersion inicial (1).
	 * Es decir que va a insertarle un primer registro variable que indica el tam de disp del bucket
	 */
	void inicializeHashFile();

	/**
	 * Retorna true si ya existe en el HashFile el elemento (sid) pasado por parametro
	 */
	bool existsElement(StringInputData* sid);

public:

	Hash();

	virtual ~Hash();

	/**
	 * Agrega un elemento nuevo al archivo Hash.
	 * Si el StringInputData ya existe en el HashFile retorna 1;
	 * Si el StringInputData fue guardado exitosamente retorna 0;
	 * Si hubo algun problema al ejecutar este metodo retorna -1;
	 */
	int add(StringInputData* sid);

	/**
	 * This method gets a Data object, giving it's key.
	 */
	StringInputData* get(int key);

	/**
	 * para imprimir el Hash por consola
	 */
	void print();
};

#endif /* HASH_H_ */
