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
	FILE * crearArch();

	/**
	 * Se encarga de abrir la tabla, devolver un listado de los elementos de la tabla
	 * mediante el puntero listaElementosTabla y luego cerrar el archivo Tabla.
	 * La funcion devuelve el tamaño de la tabla.
	 * Nota: recordar que el primer elemento de la tabla es su propio tamaño (tamTabla)
	 */
	int parsear(int * listaElementosTabla);

	/**
	 * Retorna la cant de elementos que tiene la tabla segun el primer renglon
	 * el cual contiene el tamaño de la misma
	 */
	int obtenerTamanio();

	/**
	 * Retorna el bloque a apuntar en el archivo de Hash segun la posicion en la tabla
	 * pasada como parametro(registroAApuntarEnTabla)
	 * Retorna -1 si hubo algun error al intentar leer el registro
	 */
	int obtenerBloqueAApuntarEnArchivoHash(int registroAApuntarEnTabla);

	/**
	 * Modifica el registro "numReg" en la tabla con el valorNuevo a cambiar
	 */
	void modificarRegistro(int numReg,int valorNuevo);

	/**
	 * Se le pasa una lista de elementos y el tamaño de la tabla para imprimir la tabla por consola
	 */
	void imprimir(int * listaElementosTabla,int tamTabla);

	/**
	 * Duplica la tabla con los mismos contenidos que posee
	 */
	void duplicar();

private:
	/**
	 * Se encarga de abrir el archivo de la Tabla segun el formato (lectura,escritura) que se
	 * le pase como parametro.
	 * informar si hubo error al intentar hacerlo
	 */
	FILE * abrirArch(char formato[2]);

	/**
	 * Se encarga de abrir el archivo de la Tabla para lectura
	 */
	FILE * abrirArchLectura();

	/**
	 * Se encarga de abrir el archivo de la Tabla para escritura
	 */
	FILE * abrirArchEscritura();

	/**
	 * Se encarga de cerrar el archivo de la Tabla e informar si hubo error al intentar hacerlo
	 */
	void cerrarArch(FILE * arch_tabla);

	/**
	 * Crea archivo temporario para uso de modificacion de datos
	 */
	FILE* crearArchivoTemporal();


};

#endif /* TABLE_H_ */
