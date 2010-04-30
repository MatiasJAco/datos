/*
 * Table.h
 *
 *  Created on: 04/04/2010
 *      Author: pablo
 */

#ifndef TABLE_H_
#define TABLE_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

class Table {
public:
	Table();
	virtual ~Table();

	/**
	 * Crea el archivo de la tabla (tabla.txt) y lo inicializa con tamTabla = 0
	 * y primer registro = 0 (apuntando al bloque 0 del archivo de Hash)
	 * NOTA: tabla.txt va a tener como primer registro el tamaño de si misma
	 */
	FILE * createFile();

	/**
	 * Se encarga de abrir la tabla, devolver un listado de los elementos de la tabla
	 * mediante el puntero listaElementosTabla y luego cerrar el archivo Tabla.
	 * La funcion devuelve el tamaño de la tabla.
	 * Nota: recordar que el primer elemento de la tabla es su propio tamaño (tamTabla)
	 */
	int parse(int * listElementsTable);

	/**
	 * Retorna la cant de elementos que tiene la tabla segun el primer renglon
	 * el cual contiene el tamaño de la misma
	 */
	unsigned int getSize();

	/**
	 * Retorna el bloque a apuntar en el archivo de Hash segun la posicion en la tabla
	 * pasada como parametro(registroAApuntarEnTabla)
	 * Retorna -1 si hubo algun error al intentar leer el registro
	 */
	int getNumberOfBucketInHash(int NumOfRegToPointInTable);

	/**
	 * Modifica el registro "numReg" en la tabla con el valorNuevo a cambiar
	 */
	void modifyRegister(int numReg,unsigned int newValue);

	/**
	 * para imprimir la tabla por consola
	 */
	void print();

	/**
	 * Duplica la tabla con los mismos contenidos que posee
	 */
	void duplicate();

	/**
	* Divide la tabla si es que puede hacerlo, es decir si la tabla esta repetida
	* Retorna -1 si no pudo
	*/
	int verifyAndDivide();

	/**
	 * recorre la tabla, se posiciona en la primer posicion en donde aparece el valor de value
	 * y lo reemplaza por newValue
	 * Retorna false, si no pudo realizar la operacion
	 */
	bool changeFirstTimeInTable(unsigned int value,unsigned int newValue);

	/**
	 * Recorro la tabla circularmente (me muevo para atras "jump" lugares y para adelante "jump" lugares
	 * y verifico si los elementos son iguales,
	 * si los elementos son iguales retorno el elemento
	 * si los elementos son distintos retorno -1
	 */
	int verifyJumps(int position, int jump);

	/**
	 * Recorro la tabla circularmente (me muevo para atras "jump" lugares y para adelante "jump" lugares
	 * y reemplazo los lugares en donde caigo con el elemento que paso como parametro: element
	 */
	void jumpAndReplace(int position, int jump, int element);

private:
	/**
	 * Se encarga de abrir el archivo de la Tabla segun el formato (lectura,escritura) que se
	 * le pase como parametro.
	 * informar si hubo error al intentar hacerlo
	 */
	FILE * openFile(char format[2]);

	/**
	 * Se encarga de abrir el archivo de la Tabla para lectura
	 */
	FILE * openFileForRead();

	/**
	 * Se encarga de abrir el archivo de la Tabla para escritura
	 */
	FILE * openFileForWrite();

	/**
	 * Se encarga de cerrar el archivo de la Tabla e informar si hubo error al intentar hacerlo
	 */
	void closeFile(FILE * tableFile);

	/**
	 * Crea archivo temporario para uso de modificacion de datos
	 */
	FILE* createTemporalFile();

	/**
	 * retorna la primera posicion de la tabla donde aparece el valor del value
	 */
	int getFirstTimeInTable(unsigned int value);


};

#endif /* TABLE_H_ */
