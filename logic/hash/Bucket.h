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
#include "stdlib.h"

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
	 * @param sid Es el dato ingresado por el usuario.
	 * @return Devuelve 1 si hubo overflow, 2 si hubo otro tipo de error de I/O, y 0 si pudo insertar el registro en el bloque.
	 */
	int insert(StringInputData* sid);

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

	/**
	 * Imprime el bucket entero
	 */
	void print();

	/**
	 * se encarga de duplicar el td
	 */
	void duplicateDepth();

	/**
	 * se encarga de dividir por 2 el td
	 */
	void divideDepth();

	/**
	 * Para posicionarse al final del bucket
	 */
	void positionateAtEnd();


private:

	/**
	 * lee el primer registro del bucket, el cual tiene la informacion del td de si mismo
	 */
	unsigned int getDepthFromHashFile();
};

#endif /* BUCKET_H_ */
