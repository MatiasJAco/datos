/*
 * Logger.h
 *
 *  Created on: 06/04/2010
 *      Author: matias
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include "archivoTexto.h"
#include <iostream>

class Logger{

private:
	/**
	 *puntero que contendra la direccion del archivo a procesar
	 */
	ArchivoTexto* archivo;

	static const int TAMANIO_LIMITE = 200;

	/**
	 * Busca una cadena de caracteres en el archivo de texto.
	 */

	void buscar(std::string cadena);


	/**
	 * Procesa una linea particular, quedandose solo con caracteres validos y detectand si
	 * se ingreso una clave o no.
	 */
	std::string procesar_linea(char *line);

	/**
	 * Ingresa datos al archivo de texto.
	 */
	void escribir_archivo(std::string cadena);


public:

	Logger();

	virtual ~Logger();


	/**
	 * Imprime la ayuda.
	 */
	void imprimir_ayuda(void);

	/**
	 * Busca la cadena de caracteres en el log.
	 */
	void buscar_cadena(char*);

	/**
	 * Recorre el log actual y lo imprime por pantalla.
	 */
	void recorrer_log(void);

	/**
	 * Permite ingresar datos al log.
	 */
	void ingresar(char *);








};















#endif /* LOGGER_H_ */
