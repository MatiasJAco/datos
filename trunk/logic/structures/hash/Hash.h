/*
 * Hash.h
 *
 *  Created on: Apr 16, 2010
 *      Author: Pablo Lisio / Adrián Bernardi
 */

#ifndef HASH_H_
#define HASH_H_


#include "Table.h"
#include "Bucket.h"
#include "../GeneralStructure.h"
#include "../../input/StringInputData.h"
#include "../../ppmc/bigint/BigIntegerLibrary.hh"
#include "../../ppmc/md5/MD5.h"
#include "../../exceptions/ManagerException.h"
#include "../../exceptions/HashException.h"
#include "../../../physical/file/BlockFile.h"
/**
 * Clase que permite modelar un Hash.
 * Maneja una tabla que contiene buckets.
 * Cada bucket a su vez posee registros, y en cada registro hay un dato.
 * El usuario puede ingresar, modificar, eliminar o consultar datos.
 */


class Hash : public GeneralStructure {

private:
	Table* hashTable;
	BlockFile* hashFile;
	unsigned int bucketsUsedAmount;

	/**
	 * Retorna el resultado de la funcion Hash. En este caso estamos usando el metodo de "bits sufijos".
	 * @param key Es la clave sobre la cual se aplicará la función de hash.
	 * @return Devuelve un entero que surge de aplicar la función de hash a la clave pasada por parámetro.
	 */
	int calculateHashFunction(std::string key);

	/**
	 * Retorna el numero de Bucket del archivo de hash.
	 * @param key Es la clave que se usa para calcular el número de bucket.
	 * @return Devuelve el número de bucket que contiene al dato que posee la clave pasada por parámetro.
	 */
	int getNumberOfBucket(std::string key);

	/**
	 * Crea un bucket (bucket numero 0). Este bucket solo tiene como campo de control el tamaño de dispersion inicial (1).
	 * Es decir que va a insertarle un primer registro variable que indica el tam de disp del bucket.
	 */
	void inicializeHashFile();

	/**
	 * Agrega un elemento nuevo al archivo Hash. Este metodo debe ser llamado desde
	 * el metodo add(clave,valor)
	 * @param sid Es el StringInputData.
	 * @return true si la operación fue exitosa
	 */
	bool insert(StringInputData* sid) throw (ManagerException);

	/**
	 * Verifica si existe un dato en un bloque, e indica en qué posición.
	 * @param key Es la clave del dato que se desea hallar.
	 * @param position Devuelve la posicion en donde se encontro la clave, o -1 si no se encontró.
	 * @return Retorna true si ya existe en el HashFile el elemento (sid) pasado por parametro.
	 */
	bool existsElement(std::string key, int & position);

	/**
	 * Crea un bucket nuevo.
	 * @param depth Es el tamaño de dispersión que tendrá el bloque a crearse.
	 * @return Devuelve un puntero al bucket creado.
	 */
	Bucket* createNewBucket(int depth);

	/**
	 * Intenta insertar un sid nuevo en su correspondiente bucket segun la funcion de hash y la vez retorna por parametro el resultado de la operacion.
	 * @param sid Es el dato ingresado por el usuario.
	 * @param result Devuelve 1 si hubo overflow, 2 si hubo otro tipo de error de I/O, y 0 si pudo insertar el registro en el bloque.
	 * @return Devuelve un puntero al bucket donde se  intento insertar
	 */
	Bucket* tryToInsertNewSid(StringInputData* sid, int & result);

	/**
	 * Borra los registros del bucket pasado por parametro (de disco), y luego redispersa dichos registros en el hash.
	 * @param bucketDesbordado Es el bucket desbordado cuyos registros deben redispersarse.
	 * @return Devuelve 0 si realizo la operacion correctamente.
	 */
	int reHash(Bucket* bucketDesbordado);

	/**
	 * Guarda el bucket en el archivo Hash
	 */
	void saveBucket(Bucket * bucket);

public:

	/**
	 * Crea el archivo Hash (si es que no esta creado) y lo inicializa
	 */
	Hash();

	/**
	 * Cierra el archivo (no lo destruye físicamente)
	 */
	virtual ~Hash();



    /*----------------------------------------------------------*/
	/*-----------------------PRIMITIVAS-------------------------*/
	/*----------------------------------------------------------*/

	/**
	 * Agrega un elemento nuevo al archivo Hash.
	 * @param clave Es la clave del dato a ingresar.
	 * @param valor Es el valor del dato a ingrear.
	 * @return true si la operación fue exitosa
	 */
	bool insert(std::string clave, std::string valor) throw (ManagerException);

	/**
	 * Verifica si existe un dato en un bloque. El dato está identificado por la clave que se pasa por parámetro.
	 * @param key Es la clave del dato que se desea hallar.
	 * @return true si ya existe en el HashFile la clave pasada por parametro
	 */
	bool existsElement(std::string key);

	/**
	 * Busca y retorna un elemento dado su clave.
	 * @param key Es la clave del dato a buscar
	 * @param data Es el StringInputData que representa al dato que contiene la clave a buscar
	 * @return true si la operación fue exitosa
	 */
	bool find(std::string key, InputData & data) throw (ManagerException);

	/**
	 * Cambia el valor de un key pasado por parámetro.
	 * @param key Es el key al cual se le cambiará el valor.
	 * @param newValue Es el valor nuevo que tomara la clave pasada por parametro.
	 * @return true si la operación fue exitosa
	 */
	bool modify(std::string key, std::string newValue) throw (ManagerException);

	/**
	 * Elimina el dato, cuya clave es la pasada por parametro.
	 * @param key Es la clave del dato que se desea borrar.
	 * @return true si la operacion fue exitosa
	 */
	bool remove(std::string key) throw (ManagerException);

	/**
	 * Imprime el hash por pantalla.
	 */
	void print();

	/**
	 * Borra los archivos generados por el Hash. Es útil para las pruebas unitarias.
	 */
	bool deleteGeneratedFiles();

	/**
	 * Este metodo devuelve todas las claves del hash en una lista.
	 * @return Devuelve todas las claves del hash en una lista.
	 */
	keyList getKeys();
};

#endif /* HASH_H_ */
