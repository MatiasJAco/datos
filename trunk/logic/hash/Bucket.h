/*
 * Bucket.h
 *
 *  Created on: Apr 24, 2010
 *      Author: Pablo Lisio / Adrián Bernardi
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include "../../physical/file/Block.h"
#include "../../physical/file/BlockFile.h"
#include "../input/StringInputData.h"
#include "stdlib.h"

/**
 * Clase que modela un cubo de un hash.
 * Este cubo posee una cantidad indeterminada de registros.
 * La cantidad de registros es proporcional al espacio del cubo.
 */
class Bucket {

private:
	unsigned int number; // Numero de cubo.
	unsigned int depth; // Dispersion del cubo.
	Block* block;

	/**
	 * Se encarga de modificar el tamaño de dispersion del bucket al pasado por parametro.
	 * @param depth es el nuevo valor del tamaño de dispersion.
	 * @return bool retorna true si se pudo realizar, false en caso contrario.
	 */
	bool modifyDepth(int depth);

	/**
	 * Se encarga de posicionarse en un lugar dado.
	 * @param position Es la posicion en la cual me quiero parar.
	 */
	void positionateAt(int position);

public:
	/**
	 * Inicializa los atributos
	 */
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
	int insertRegister(StringInputData* sid);

	/**
	 * Este metodo indica si existe un registro fisico, con la clave dada.
	 * @param key Es la clave a buscar.
	 * @return Devuelve true si encuentra un registro con la clave pasada por parametro. En caso contrario devuelve false.
	 */
	bool existsRegister(unsigned long int key);

	/**
	 * Este metodo indica si existe un registro fisico, con la clave dada.
	 * @param key Es la clave a buscar.
	 * @param position devuelve la posicion en donde se encontro la key (-1 si no se encontro).
	 * @return Devuelve true si encuentra un registro con la clave pasada por parametro. En caso contrario devuelve false.
	 */
	bool existsRegister(unsigned long int key, int & position);

	/**
	 * Este metodo devuelve un registro variable, en base a una clave pasada por parametro.
	 * @param key Es la clave que sirve para encontrar el registro deseado.
	 * @return Devuelve el registro cuya clave es la pasada por parametro.
	 */
	VarRegister getRegister(unsigned long int key);

	/**
	 * Este metodo borra un registro del bloque que contiene el bucket, dada su clave.
	 * @param key Es la clave del registro que se desea eliminar.
	 * @return Devuelve true si consigue borrar el registro, false en caso contrario.
	 */
	bool deleteRegister(unsigned long int key);

	/**
	 * Imprime el bucket entero.
	 */
	void print();

	/**
	 * Se encarga de duplicar el tamaño de dispersion del bucket.
	 * @return bool retorna true si se pudo realizar, false en caso contrario.
	 */
	bool duplicateDepth();

	/**
	 * Se encarga de dividir en 2 el tamaño de dispersion del bucket.
	 * @return bool retorna true si se pudo realizar, false en caso contrario.
	 */
	bool divideDepth();


	/**
	 * Lee el primer registro del bucket, y devuelve su tamaño de dispersión.
	 * @return Devuelve un entero positivo, que representa la dispersión del cubo.
	 */
	unsigned int getDepthFromHashFile();

	/**
	 * Obtiene la lista entera de Sids que contiene el bucket
	 * @param listaDatos de Sids a ser devuelta
	 */
	void getListOfSids(list<StringInputData> &listaDatos);

	/**
	 * Vacia el bucket (dejando el campo de control td)
	 * @return Retorna true si pudo vaciarlo, false en caso contrario
	 */
	bool empty();

};

#endif /* BUCKET_H_ */
