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
	 * Cambia el valor de un key pasado por parámetro.
	 * @param key Es el key al cual se le cambiará el valor.
	 * @param value Es el valor nuevo que tomara la clave pasada por parametro.
	 */
	int modify(int key, string value);

	/**
	 * para imprimir el Hash por consola
	 */
	void print();
};

#endif /* HASH_H_ */
