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
	int calculateHashFunction(int key);

	/**
	 * Retorna el numero de Bucket del HashFile
	 */
	int getNumberOfBucket(int key);

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

	/**
	 * crea un bucket nuevo pasandole el tamaño de dispersion y retorna
	 * un puntero al bucket nuevo
	 */
	Bucket* createNewBucket(int depth);

	/**
	 * Intenta insertar un sid nuevo en su correspondiente bucket segun la funcion de hash seteada
	 * Y la vez retorna por parametro el resultado de la operacion:
	 * @param sid Es el dato ingresado por el usuario.
	 * @param  result Devuelve 1 si hubo overflow, 2 si hubo otro tipo de error de I/O, y 0 si pudo insertar el registro en el bloque.
	 * @return Devuelve un puntero al bucket donde se  intento insertar
	 */
	Bucket* tryToInsertNewSid(StringInputData* sid, int & result);

	/**
	 * Basicamente borra el bucket pasado por parametro de disco, luego lo recupera de la lista de bloques libres (esto se
	 * hace para que se borren sus registros) y luego redispersa los registros.
	 * @param bucket Es el bucket desbordado
	 * @return Devuelve 0 si realizo la operacion correctamente.
	 */
	int reHash(Bucket* bucketDesbordado);

public:

	Hash();

	virtual ~Hash();

	/**
	 * Agrega un elemento nuevo al archivo Hash.
	 * @param sid es el StringInputData que se desea agregar
	 * @return int Retorna 1 si el sid ya existe;0 si fue agregado; -1 si hubo algun problema
	 */
	int add(StringInputData* sid);

	/**
	 * This method gets a Data object, giving it's key.
	 */
	StringInputData* get(int key);

	/**
	 * Cambia el valor de un key pasado por parámetro.
	 * @param key Es el key al cual se le cambiará el valor.
	 * @param newValue Es el valor nuevo que tomara la clave pasada por parametro.
	 * @return int Retorna 1 si el sid no existe;0 si fue cambiado; -1 si hubo algun problema
	 */
	int modify(int key, string newValue);


	/**
	 * Elimina la clave pasada por parametro.
	 * @param key Es la clave que se desea borrar.
	 * @return Devuelve 1 si no existe la clave, 0 si pudo borrar la clave.
	 */
	int erase(int key);

	/**
	 * para imprimir el Hash por consola
	 */
	void print();
};

#endif /* HASH_H_ */
