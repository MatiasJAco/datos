/*
 * Logger.h
 *
 *  Created on: 06/04/2010
 *      Author: matias
 */

#ifndef LOGGER_H_
#define LOGGER_H_


#include <string>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include "archivoTexto.h"
#include <iostream>


/**
 *Esta clase se encarga de almacenar informacion que puede ser necesaria para el usuario.
 */
class Logger{

private:
	/**
	 *puntero que contendra la direccion del archivo a procesar
	 */
	ArchivoTexto* archivo;

	static const int TAMANIO_LIMITE = 10000;

	/**
	 * Busca una cadena de caracteres en el archivo de texto.
	 * @param cadena Es la cadena a buscar
	 * @return bool Retorna true si se pudo realizar, false en caso contrario.
	 */
	bool find(std::string cadena);

	/**
	 * Procesa una linea particular, quedandose solo con caracteres validos y detectando si
	 * se ingreso una clave o no.
	 * @param line Es la linea a procesar
	 * @return string Retorna la cadena de caracteres validos
	 */
	std::string processLine(char *line);

	/**
	 * Ingresa datos al archivo de texto.
	 * @param cadena Es la cadena a ingresar
	 */
	void writeFile(std::string cadena);

	/**
	 * Convierte un entero a string
	 * @param i Es el entero a convertir
	 * @return string Retorna el string
	 */
	std::string itos(int i);

	/**
	 * Busca en el Archivo Logger una cadena
	 * @ptrArchivo i Es el puntero al archivo a buscar
	 * @param cadena Es la cadena de caracteres a ser buscada
	 * @return bool Retorna true si se encontro la cadena, false en caso contrario
	 */
	bool findFile(char *ptrArchivo, std::string cadena);

private:
	Logger();
	Logger(const Logger&);
	Logger &operator= (const Logger &);
	static Logger* pinstance;

public:
	/// Para uso del patron singleton
	static Logger* Instance();

	virtual ~Logger();

	/**
	 * Imprime la ayuda
	 */
	void printHelp(void);

	/**
	 * Busca la cadena de caracteres en el log
	 * @return bool Retorna true si se encontro la cadena, false en caso contrario
	 */
	bool findString(char*);

	/**
	 * Recorre el log actual y lo imprime por pantalla
	 */
	void print(void);

	/**
	 * Permite ingresar datos al log.
	 */
	void insert(char *);

};

#endif /* LOGGER_H_ */
