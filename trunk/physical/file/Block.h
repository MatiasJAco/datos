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

typedef enum {UNDERFLOW_LOAD=0, NORMAL_LOAD ,OVERFLOW_LOAD} loadResultEnum;


/**
 * Bloque, compuesto por registros variables. Maneja los temas de tama�o de los nodos.
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
	static const float DEFAULT_FIXED_REGISTER_COUNT=0;

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
	 * overflow, no inserta y devuelve en load estado OVERFLOW_LOAD
	 * @param reg registro a insertar
	 * @param load devuelve un factor de balance que indica cual seria el resultado
	 * 		   de la operacion
	 * @return bool true en caso de exito, false en caso contrario
	 * @see VarRegister, loadResultEnum
	 */
	bool addRegister(const VarRegister &reg, loadResultEnum &load);

	/**
	 * Elimina el registro que se encuentra en la posicion
	 * actual del iterador.Y devuelve un parametro que indica el estado del bloque despues
	 * de realizar la operacion
	 * @param load devuelve un factor de balance que indica cual seria el resultado
	 * 		   de la operacion
	 * @return bool true en caso de exito
	 * @see loadResultEnum
	 */
	bool deleteRegister(loadResultEnum &load);


	/**
	 * Modifica el registro que se encuentra en la posicion actual del iterador
	 * En caso de producirse OVERFLOW_LOAD o UNDERFLOW_LOAD, no realiza la modificacion.
	 * @param reg valor de registro que se va a colocar.
	 * @return bool true en caso de ok, false en caso contrario
	 */
	bool modifyRegister(const VarRegister & reg);

	/**
	 * Modifica el registro que se encuentra en la posicion actual del iterador
	 * En caso de producirse OVERFLOW_LOAD o UNDERFLOW_LOAD, no realiza la modificacion.
	 * @param load devuelve un factor de balance que indica cual seria el resultado
	 * 		   de la operacion
	 * @param reg valor de registro que se va a colocar.
	 * @return bool true en caso de ok, false en caso contrario
	 * @see loadResultEnum
	 */
	bool modifyRegister(const VarRegister & reg, loadResultEnum & load);

	/**
	 * Muestra por pantalla el contenido del bloque. Se usa para debug
	 */
	void printRegisters();

	/**
	 * Elimina todos los registros de un bloque.
	 */
	void clear();

	//------------------------RECORRIDO---------------------------------------//
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
	 * Obtiene el registro actual y retrocede
	 * @param foward indica si se retrocede el iterador despues de obtener un registro
	 * @return VarRegister el registro actual
	 */
	VarRegister getPreviousRegister(bool foward=true);

	/**
	 * Posiciona el iterador en la posicion n, y devuelve el registro
	 * que se encuentra en esa posicion
	 * @param number posicion a la que se salta
	 * @return VarRegister el registro actual
	 */
	VarRegister getRegisterN(unsigned int number);

	/**
	 * Obtiene el VarRegister actual
	 * @return VarRegister el registro
	 */
	VarRegister peekRegister();

	/**
	 * Obtiene el VarRegister siguiente
	 * @return VarRegister el registro
	 */
	VarRegister peekNextRegister();

	/**
	 * Se fija si es el primer registro...
	 * @return bool true si es el primero, false en caso contrario
	 */
	bool isFirstRegister();

	/**
	 * Se fija si se paso el ultimo registro
	 * @return bool true  si nos pasamos del ultimo elemento, false en caso contrario
	 */
	bool isLastRegister();

	/**
	 * Indica si puede continuar iterando, dado que quedan registros en el bloque.
	 * @return bool true si existe un registro proximo, false en caso contrario
	 */
	bool hasNextRegister();

	/**
	 * Posiciona el iterador al principio del bloque, y setea el count
	 *  si no hay registros no hace nada
	 *
	 */
	void restartCounter();

	/**
	 * Posiciona el iterador despues del ultimo elemento
	*/
	void jumpEndCounter();

	/**
	* Posiciona el iterador despues del ultimo elemento
	*/
	void jumpEndBlock();


	/**
	 * Posiciona el iterador en el ultimo elemento
	 */
	void jumpLastRegister();



	//-----------------------------GET/SET--------------------------------------//
	/**
	 * Setea el factor de carga a utilizar
	 * @param factor factor de carga a colocar
	 */
	void setLoadFactor(float factor);

	/**
	 * Obtiene el contador de la pos actual
	 * Si no esta sobre una posicion valida devuelve -1
	 * Posiciones no validas: lista de reg vacios, o hecho un delete
	 * del ultimo registro
	 * @return int numero de reg actual -1 en caso de pos no valida
	 */
	int getPosActual();

	/**
	 * Obtiene la cantidad de registros.
	 * @return unsigned int cantidad de registros
	 */
	unsigned int getRegisterAmount();

	/**
	 * Obtiene la minima carga que puede tener el bloque sin estar en underflow
	 * Solo devuelve un valor si esta seteado LOAD_FACTOR. En caso de no estar
	 * seteado devuelve 0
	 * @return unsigned int cantidad de bytes minima
	 */
	unsigned int getMinimalLoad();

	/**
	 * Obtiene el numero del bloque actual
	 * @return numero de bloque
	 */
	unsigned int getBlockNumber();

	/**
	 * Obtiene el porcentaje del bloque ocupado actualmente
	 * @return float porcentaje de carga actual
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

	unsigned int getFixedRegisterCount();

	void setFixedRegisterCount(unsigned int count);

	unsigned int getBlockControlDataSize();

	unsigned int getBlockSize();

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

	/**
	 * Elimina el registro que se encuentra en la posicion
	 * actual del iterador. Si al eliminar el registro se fuera a producir underflow,
	 * no realiza la operacion.
	 * @return bool true en caso de exito
	 */
	bool deleteRegister();


private:

	float calculateFraction(unsigned int);

	loadResultEnum evaluateLoad(unsigned int bytes);

	bool LoadBlockAtributes(char *streamChar);

	bool SaveBlockAtributes(char *streamChar);

private:

	/**
	 * Numero del bloque actual
	 */
	unsigned int m_blockNumber;

	/**
	 * Tama�o en bytes del bloque
	 */
	unsigned int m_blockSize;

	/**
	 * Offset en bytes del primer registro, depende de la
	 * cantidad de informacion de control que se guarde
	 */
	unsigned int m_FirstRegisterOffset;

	/**
	 * Porcentaje minimo de carga del bloque para que este se
	 * encuentre en underflow. Por default es -1 con lo cual
	 * no se evalua underflow.
	 */
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

	/**
	 * Posicion del iterador actual
	 * Si no esta en ningun registro es -1
	 */
	int m_posActual;

	/**
	 * Cantidad de registros del bloque que son datos de control.
	 * Esto es para el uso de otras clases derivadas.
	 */
	unsigned int m_fixedRegisterCount;

};

#endif /* BLOCK_H_ */
