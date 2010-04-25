/*
 * Block.h
 *
 *  Created on: 11/04/2010
 *      Author: alex
 */

#ifndef BLOCK_H_
#define BLOCK_H_
#include "Register.h"
#include "VarRegister.h"
#include "../utils/ByteConverter.h"
#include <sstream>
#include <list>

typedef enum {UNDERFLOW, NORMAL_LOAD ,OVERFLOW} loadResultEnum;


/**
 * Block
 */
class Block {

	friend class BlockManager;

public:
	//------------------------TYPEDEFS----------------------------------//
	/**
	 * Definicion del tipo de datos que almacena los registros
	 */
	typedef std::list <VarRegister> RegisterList;

	/**
	 * Definicion del iterador de la lista
	 */
	typedef RegisterList::iterator RegisterListIt;

private:
	static const float UNDEFINED_LOAD_FACTOR=-1;

public:
	//------------------------CONSTRUCTOR/DESTUCTOR---------------------//
	/**
	 * Constructor
	 * @param blocknumber numero del bloque a crear
	 * @param blockSize tama�o del bloque
	 * @param loadFactor factor de carga del bloque
	 */
	Block(unsigned int blocknumber, unsigned int blockSize,float loadFactor);
	~Block();

	//-------------------------METODOS-----------------------------------//

	/**
	 * Inserta un registro en la posicion actual del iterador, en caso de producirse
	 * overflow, no inserta.
	 * @param reg registro a insertar
	 * @return bool true en caso de exito, false en caso contrario
	 * @see VarRegister
	 */
	bool addRegister(const VarRegister &reg);

	/**
	 * Inserta un registro en la posicion actual, en caso de producirse
	 * overflow, no inserta y devuelve en load estado OVERFLOW
	 * @param reg registro a insertar
	 * @param load devuelve un factor de balance que indica cual seria el resultado
	 * 		   de la operacion
	 * @return bool true en caso de exito, false en caso contrario
	 * @see VarRegister, loadResultEnum
	 */
	bool addRegister(const VarRegister &reg, loadResultEnum &load);

	/**
	 * Elimina el registro que se encuentra en la posicion
	 * actual del iterador. Si al eliminar el registro se fuera a producir underflow,
	 * no realiza la operacion.
	 * @return bool true en caso de exito
	 */
	bool deleteRegister();

	/**
	 * Elimina el registro que se encuentra en la posicion
	 * actual del iterador.Si al eliminar el registro se fuera a producir underflow,
	 * no realiza la operacion, y de
	 * @param load devuelve un factor de balance que indica cual seria el resultado
	 * 		   de la operacion
	 * @return bool true en caso de exito
	 * @see loadResultEnum
	 */
	bool deleteRegister(loadResultEnum &load);


	/**
	 * Modifica el registro que se encuentra en la posicion actual del iterador
	 * En caso de producirse OVERFLOW o UNDERFLOW, no realiza la modificacion.
	 * @param reg valor de registro que se va a colocar.
	 * @return bool true en caso de ok, false en caso contrario
	 */
	bool modifyRegister(const VarRegister & reg);

	/**
	 * Modifica el registro que se encuentra en la posicion actual del iterador
	 * En caso de producirse OVERFLOW o UNDERFLOW, no realiza la modificacion.
	 * @param load devuelve un factor de balance que indica cual seria el resultado
	 * 		   de la operacion
	 * @param reg valor de registro que se va a colocar.
	 * @return bool true en caso de ok, false en caso contrario
	 * @see loadResultEnum
	 */
	bool modifyRegister(const VarRegister & reg, loadResultEnum & load);


	/**
	 * Obtiene el proximo Register,  siendo este de longitud variable.
	 * La informacion de la longitud del Register no es necesario pasarla,
	 * ya que se encuentra persistida en disco.
	 * @param foward indica si avanza el iterador despues de obtener un registro
	 * @return VarRegister el registro
	 *
	 */
	VarRegister getNextRegister(bool foward=true);

	/**
	 * Obtiene el proximo Register,  siendo este de longitud variable.
	 * La informacion de la longitud del Register no es necesario pasarla,
	 * ya que se encuentra persistida en disco.
	 * @param foward indica si avanza el iterador despues de obtener un registro
	 * @return VarRegister el registro
	 *
	 */
	VarRegister peekRegister();


	bool isLastRegister();

	/**
	 * Devuelve el contador al principio del bloque
	 */
	void restartCounter();


	/**
	 * Setea el factor de carga a utilizar
	 * @param factor factor de carga a colocar
	 */
	void setLoadFactor(float factor);


	/**
	 * Obtiene la cantidad de registros.
	 * @return unsigned int cantidad de registros
	 */
	unsigned int getRegisterAmount();

	/**
	 * Obtiene el numero del bloque actual
	 * @return numero de bloque
	 */
	unsigned int getBlockNumber();

	/**
	 * Obtiene el porcentaje del bloque ocupado actualmente
	 * @return float oorcentaje de carga actual
	 */
	float  getActualLoad();

	/**
	 * Sirve para obtener la cantidad de bytes usados en el bloque.
	 * @return Devuelve la cantidad de bytes libres del bloque.
	 */
	unsigned int getUsedSpace();

	/**
	 * Sirve para obtener la cantidad de bytes libres que quedan en el bloque.
	 * @return Devuelve la cantidad de bytes libres del bloque.
	 */
	unsigned int getRemainingSpace();

	/**
	 * Muestra por pantalla el contenido del bloque. Se usa para debug
	 */
	void printRegisters();

	//--------------------SERIALIZE/DESERIALIZE-------------------//
	/**
	 * Convierte a un stream el contenido del registro
	 * @param streamChar stream de caracteres en el cual se coloca el contenido del bloque.
	 * tiene que tener memoria asignada desde el ambito del cual se la llama
	 * @return true en caso de ok, false en caso contrario
	 */
	bool serialize(char *streamChar);

	/**
	 * Carga el bloque desde un stream
	 * @param streamChar stream de caracteres del cual se carga el registro
	 * @return true en caso de ok, false en caso contrario
	 */
	bool deserialize(char *streamChar);

private:

	float calculateFraction(unsigned int);

	loadResultEnum evaluateLoad(unsigned int bytes);

	bool LoadBlockAtributes(char *streamChar);

	bool SaveBlockAtributes(char *streamChar);

private:

	unsigned int m_blockNumber;

	unsigned int m_blockSize;

	unsigned int m_FirstRegisterOffset;

	float m_LoadFactor;
	/**
	 * Espacio usado por el bloque
	 */
	unsigned int m_usedBytes;

	/**
	 * Cantidad de registros en el nodo.
	 */
	unsigned int m_registerCount;

	/**
	 * Posicion actual dentro del nodo. Se usa para ir recorriendo
	 * secuencialmente
	 */
	RegisterListIt m_actualReg;

	/**
	 * Lista que contiene todos los Registers del bloque.
	 */
	RegisterList m_registers;


};

#endif /* BLOCK_H_ */
