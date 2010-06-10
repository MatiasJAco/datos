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

/**
 * Esta clase sirve para modelar una tabla de un hash.
 * Contiene los números de buckets del hash, y los mantiene persistidos en disco.
 */
class Table {
public:
	Table();
	virtual ~Table();

	/**
	 * Crea el archivo de la tabla (tabla.txt) y lo inicializa con tamTabla = 0 y primer registro = 0 (apuntando al bloque 0 del archivo de Hash).
	 * NOTA: tabla.txt va a tener como primer registro el tamaño de si misma.
	 * @return Devuelve el archivo de la tabla.
	 */
	FILE * createFile();

	/**
	 * Se encarga de abrir la tabla, devolver un listado de los elementos de la tabla mediante el puntero listaElementosTabla y luego cerrar el archivo Tabla.
	 * La funcion devuelve el tamaño de la tabla.
	 * Nota: recordar que el primer elemento de la tabla es su propio tamaño (tamTabla)
	 * @param listElementsTable Es la lista de elementos que posee la tabla.
	 * @return Devuelve un entero que indica el tamaño de la tabla.
	 */
	int parse(unsigned int * listElementsTable);

	/**
	 * Retorna la cant de elementos que tiene la tabla segun el primer renglon, el cual contiene el tamaño de la misma.
	 * @return Devuelve la cantidad de elementos que tiene la tabla, es decir, su tamaño.
	 */
	unsigned int getSize();

	/**
	 * Retorna el bloque a apuntar en el archivo de Hash segun la posicion en la tabla pasada como parametro(registroAApuntarEnTabla).
	 * @param NumOfRegToPointInTable Es la posición de la tabla, para buscar el bucket que hay en la misma.
	 * @return Devuelve -1 si hubo algun error al intentar leer el registro
	 */
	int getNumberOfBucketInHash(unsigned long int NumOfRegToPointInTable);

	/**
	 * Modifica el registro "numReg" en la tabla con el valorNuevo a cambiar.
	 * @param numReg Es el número de registro a modificar.
	 * @param newValue Es el nuevo valor que tendrá el registro que se desea modificar.
	 */
	void modifyRegister(int numReg,unsigned int newValue);

	/**
	 * Sirve para imprimir la tabla por consola.
	 */
	void print();

	/**
	 * Duplica la tabla con los mismos contenidos que posee.
	 */
	void duplicate();

	/**
	* Divide la tabla si es que puede hacerlo, es decir si la tabla esta repetida.
	* @return Devuelve -1 si no puede dividir la tabla.
	*/
	int verifyAndDivide();

	/**
	 * Recorre la tabla, se posiciona en la primer posicion en donde aparece el valor de value y lo reemplaza por newValue.
	 * @param value Es el valor que se desea cambiar, si es que existe.
	 * @param newValue Es el nuevo valor que se desea guardar.
	 * @return Devuelve true si pudo realizar la operación. False en caso contrario.
	 */
	bool changeFirstTimeInTable(unsigned int value,unsigned int newValue);

	/**
	 * Este método recorre la tabla circularmente hacia atras y hacia adelante ("jump" lugares), y se verifica si los elementos son iguales.
	 * @param position Es la posicion sobre la cual desplazarse hacia atrás y hacia adelante en la tabla.
	 * @param jump Es el tamaño del salto.
	 * @return Si los elementos son iguales, se devuelve el valor del elemento. En caso contrario, devuelve -1.
	 */
	int verifyJumps(int position, int jump);

	/**
	 * Este método recorre la tabla circularmente hacia atras y hacia adelante ("jump" lugares), y
	 * reemplaza el valor actual con el elemento que se pasó como parametro (element).
	 * @param position Es la posicion desde donde arrancar a recorrer circularmente.
	 * @param jump Es el tamaño del salto.
	 * @param element Es el nuevo valor a guardar.
	 */
	void jumpAndReplace(int position, int jump, int element);

private:
	/**
	 * Indica si existe el archivo pasado por parametro.
	 * @param nombreArchTabla Es el archivo que se desea saber si existe.
	 * @return True si existe el archivo, false en caso contrario.
	 */
	bool exists(char nombreArchTabla[10]);

	/**
	 * Se encarga de abrir el archivo de la Tabla segun el formato (lectura,escritura) que se le pase como parametro.
	 * @param format Puede ser por ejemplo para escritura "w", o bien para lectura "r".
	 * @return Devuelve un puntero al archivo de la tabla.
	 */
	FILE * openFile(char format[2]);

	/**
	 * Se encarga de abrir el archivo de la Tabla para lectura.
	 * @return Devuelve un puntero al archivo de la tabla.
	 */
	FILE * openFileForRead();

	/**
	 * Se encarga de abrir el archivo de la Tabla para escritura.
	 * @return Devuelve un puntero al archivo de la tabla.
	 */
	FILE * openFileForWrite();

	/**
	 * Se encarga de abrir el archivo de la Tabla para agregar datos al final.
	 * @return Devuelve un puntero al archivo de la tabla.
	 */
	FILE * openFileForAppend();

	/**
	 * Se encarga de cerrar el archivo de la Tabla e informa si hubo error al intentar hacerlo.
	 * @param tableFile Es el archivo que representa la tabla en disco.
	 */
	void closeFile(FILE * tableFile);

	/**
	 * Crea archivo temporal para uso de modificacion de datos.
	 * @return Devuelve un puntero al archivo temporal.
	 */
	FILE* createTemporalFile();

	/**
	 * Retorna la primera posicion de la tabla donde aparece el valor del value.
	 * @param value Es el valor que se desea encontrar en la tabla.
	 * @return Devuelve la primer posición de la tabla en donde aparece el valor pasado por parámetro.
	 */
	int getFirstTimeInTable(unsigned int value);

};

#endif /* TABLE_H_ */
