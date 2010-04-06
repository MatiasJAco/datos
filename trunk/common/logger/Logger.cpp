/*
 * Logger.cpp
 *
 *  Created on: 02/04/2010
 *      Author: matias
 */


#include "Logger.h"

 Logger::Logger(){

};

 Logger::~Logger(){};


std::string Logger::procesar_linea(char *line) {

	//Puntero que se utilizará para barrer toda la línea.
	char *line_index = line;


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


	}
	return cadena;
}



void Logger::buscar(std::string cadena){
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




void Logger::escribir_archivo(std::string cadena){

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

//Busca la cadena de caracteres en el log.
void Logger::buscar_cadena(char * e_arg){
	std::string cadena = "";
	cadena = cadena + this->procesar_linea(e_arg);
    this->buscar(cadena);
}


	void Logger::recorrer_log(){
		std::string cadenaLeida="";

		archivo=new ArchivoTexto("logger.txt");
		while (archivo->leerLinea(cadenaLeida)){

			std::cout<<cadenaLeida<<std::endl;

		}
		archivo->~ArchivoTexto();

	};


void Logger::ingresar(char *e_arg)
{
    std::string cadena = "";
    cadena = cadena + this->procesar_linea(e_arg);
    this->escribir_archivo(cadena);
}


void Logger::imprimir_ayuda(void) {
	printf("\t-B, --buscar \t\tBuscar cadena de caracteres.\n");
	printf("\t-h, --ayuda \t\tAyuda para la operacion de la aplicacion.\n");
	printf("\t-I, --ingresar \tIngresar datos a la estructura.\n");
	printf("\t-S, --secuenciar \t\tVolcar todos los datos en un archivo de texto plano.\n");

	return;
}

