/*
 * Bucket.h
 *
 *  Created on: Apr 24, 2010
 *      Author: Adrián Bernardi
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include "../../physical/file/Block.h"
#include "../../physical/file/BlockFile.h"
#include "../input/StringInputData.h"

class Bucket {

private:
	unsigned int number; // Numero de cubo.
	unsigned int depth; // Dispersion del cubo.
	Block* block;

public:
	//Bucket(unsigned int number, unsigned int depth);
	Bucket(Block* block);
	virtual ~Bucket();

	void setNumber(unsigned int number);
	unsigned int getNumber();
	void setDepth(unsigned int depth);
	unsigned int getDepth();
	void setBlock(Block* block);
	Block* getBlock();

	/**
	 * Agrega un elemento nuevo al bucket.
	 * Si el StringInputData fue guardado exitosamente retorna true;
	 * Si hubo desborde en el bucket este metodo retorna false;
	 */
	bool add(StringInputData* sid);

	/**
	 * Este metodo indica si existe un registro fisico, con la clave dada.
	 * @param key Es la clave a buscar.
	 * @return Devuelve true si encuentra un registro con la clave pasada por parametro. En caso contrario devuelve false.
	 */
	bool existsRegister(int key);

	/**
	 * Este metodo devuelve un registro variable, en base a una clave pasada por parametro.
	 * @param key Es la clave que sirve para encontrar el registro deseado.
	 * @return Devuelve el registro cuya clave es la pasada por parametro.
	 */
	VarRegister getRegister(int key);
};

#endif /* BUCKET_H_ */
