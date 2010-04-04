/*
 * Logger.cpp
 *
 *  Created on: 02/04/2010
 *      Author: matias
 */

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include "../logger/archivoTexto.h"
#include <iostream>

//Valores algo arbitrarios para los arrays estáticos.
#define STACK_SIZE 150
#define INPUT_STRING_BUFFER_SIZE 200


namespace 
{
    const int TAMANIO_LIMITE = 200;
}
typedef enum {FILE_INPUT, STRING_INPUT, NONE} input_t;


  //puntero que contendra la direccion del archivo a procesar
  ArchivoTexto* archivo;
//Estructura estática que representa al stack.
typedef struct {
	double stack_buf[STACK_SIZE];
	size_t stack_index;
} stack_t;

//Headers.

void print_help(void);
std::string procesar_linea(char *line);
void buscar_cadena(std::string cadena);
void recorrer_log(void);
void escribir_archivo(std::string cadena);



int main(int argc, char **argv)
{
	//Variables especiales para la función 'getopt_long'.
	static struct option long_options[] =
	{
		{"buscar", required_argument, 0, 'B'},
		{"ayuda", no_argument, 0, 'h'},
		{"ingresar", required_argument, 0, 'I'},
		{"secuenciar", no_argument, 0, 'S'},
		{0, 0, 0, 0}
	};
	int option_index = 0;

	//Variables de estado de los argumentos del programa.
	bool h_flag, b_flag,i_flag, s_flag;
	char *e_arg;
	input_t input = NONE;

	//Buffer donde se almacenara cada linea (string) leída.


	int c;


	//Utilizo la función 'getopt_long' para analizar los argumentos.
	h_flag = b_flag = i_flag = s_flag = false;
	while ((c = getopt_long (argc, argv, "hSI:B:", long_options, &option_index)) != -1) {
		switch (c) {
		case 'h':
			h_flag = true;
			break;
		case 'B':
			b_flag = true;
			e_arg = optarg;
			break;
		case 'I':
			i_flag = true;
			e_arg = optarg;
			break;
		case 'S':
			s_flag = true;

			break;
		case '?': // Hubo un error en los argumentos, termino el programa.
			return 1;
			break;
		}
	}



	//Tomo acción en base a los argumentos pasados.
	if (b_flag == true) {
		input = STRING_INPUT;
		std::string cadena="";
		cadena=cadena+procesar_linea(e_arg);
		buscar_cadena(cadena);
		return 0;
	}
	if (h_flag == true) {
		print_help();
		return 0;
	}


	if (s_flag == true) {
		recorrer_log();
		return 0;

	}

	if (i_flag == true) {
		input = STRING_INPUT;
		std::string cadena="";
		cadena=cadena+procesar_linea(e_arg);
		escribir_archivo(cadena);
		return 0;
	}
};



//Procesa una linea particular buscando números y operaciones.
std::string procesar_linea(char *line) {

	//Puntero que se utilizará para barrer toda la línea.
	char *line_index = line;

	//Variable de la función strtod, utilizada para saber si encontró o no un
	//número.

	std::string cadena="";

	int contador=0;
	bool hayClave=false;

	for (;;) {
		//Si llegué al final de la línea termino.
		if ((*line_index == '\n') || (*line_index == '\0')) {
			break;
		}

		contador++;
			switch (*line_index) {
			case '(':

				break;
			case ')':

				break;
			case ';':
				if (contador<3){
					time_t rawtime;
					struct tm * timeinfo;
					time ( &rawtime );
					timeinfo = localtime ( &rawtime );
					hayClave=true;
					cadena=cadena+(asctime(timeinfo));
					cadena.erase(cadena.length()-1);
				}
				cadena=cadena+*line_index;
				break;


			case '\t':
				break;

			default:
				cadena=cadena+*line_index;
			}

			//Avanzo el puntero porque ya se procesó este caracter.
			line_index++;


	} //END - for (;;)
	return cadena;
}



//Busca una cadena de caracteres en el archivo de texto.
void buscar_cadena(std::string cadena){
	archivo=new ArchivoTexto("logger.txt");
	char caracterABuscar;
	char caracterLeido;
	std::string lineaDeCadenaBuscada;
	unsigned int posicionComienzoDeLinea;
	bool cambioDeLinea=true;
	unsigned int contadorDeLetras=0;
	while (not archivo->finDeArchivo()){

		caracterABuscar=cadena.at(contadorDeLetras);
		archivo->leerCaracter(caracterLeido);
		if(cambioDeLinea){
			cambioDeLinea=false;
			posicionComienzoDeLinea=archivo->getPosicionCursor()-1;
		};
		if(caracterLeido=='\n'){
			cambioDeLinea=true;
		}
		if(caracterABuscar==caracterLeido){
			contadorDeLetras++;
			if(contadorDeLetras==cadena.capacity()){
				contadorDeLetras=0;
				archivo->setPosicionCursor(posicionComienzoDeLinea);
				archivo->leerLinea(lineaDeCadenaBuscada);
				std::cout<<lineaDeCadenaBuscada<<std::endl;
				cambioDeLinea=true;

			}
		}else contadorDeLetras=0;
	};

	archivo->~ArchivoTexto();
};

//Recorre el log actual y lo imprime por pantalla.
	void recorrer_log(){
		std::string cadenaLeida="";

		archivo=new ArchivoTexto("logger.txt");
		while (archivo->leerLinea(cadenaLeida)){

			std::cout<<cadenaLeida<<std::endl;
			std::cout<<archivo->getTamanio()<<std::endl;
		}
		archivo->~ArchivoTexto();

	};

//Ingresa datos al archivo de texto.



void escribir_archivo(std::string cadena){

	archivo=new ArchivoTexto("logger.txt");
	long tamanio=0;
	archivo->irAlFinal();
	archivo->escribir(cadena);
	archivo->terminarLinea();
	tamanio= archivo->getTamanio();
	if (tamanio> TAMANIO_LIMITE)
	rename("logger.txt","logger1.txt");
	archivo->~ArchivoTexto();
};





//Imprime la ayuda.
void print_help(void) {
	printf("\t-B, --buscar \t\tBuscar cadena de caracteres.\n");
	printf("\t-h, --ayuda \t\tAyuda para la operacion de la aplicacion.\n");
	printf("\t-I, --ingresar \tIngresar datos a la estructura.\n");
	printf("\t-S, --secuenciar \t\tVolcar todos los datos en un archivo de texto plano.\n");

	return;
}

