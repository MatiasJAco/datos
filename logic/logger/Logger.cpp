/*
 * Logger.cpp
 *
 *  Created on: 02/04/2010
 *      Author: matias
 */


#include "Logger.h"
using namespace std;

Logger* Logger::pinstance = 0;// Inicializo el puntero

Logger* Logger::Instance (){
  if (pinstance == 0)  // ¿Es la primera llamada?
  {
    pinstance = new Logger; // Creo la instancia
  }
  return pinstance; // Retornamos la dirección de la instancia
}

Logger::Logger(){};

Logger::~Logger(){};


string Logger::itos(int i){                                                 //   int to string en c++
       string num;
       int temp;
       while(i / 10!=0){
         temp=i%10;
         i= i/10;
         temp =temp + 48;
         num = (char)temp + num;

       }
       i=i+48;
       num = (char)i + num ;
       return num;
}

std::string Logger::processLine(char *line) {

	//Puntero que se utilizará para barrer toda la línea.
	char *line_index = line;


	std::string cadena="";

	int contador=0;


	for (;;) {
		//Si llegué al final de la línea termino.
		if ((*line_index == '\n') || (*line_index == '\0')) {
			break;
		}

		contador++;
			switch (*line_index) {


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

bool Logger::findFile(char *ptrArchivo, std::string cadena)
{
    archivo = new ArchivoTexto(ptrArchivo);
    char caracterABuscar;
    char caracterLeido;
    std::string lineaDeCadenaBuscada;
    bool cadenaEncontrada=false;
    unsigned int posicionComienzoDeLinea = 0;
    bool cambioDeLinea = true;
    unsigned int contadorDeLetras = 0;
    while(!archivo->finDeArchivo()){
        caracterABuscar = cadena.at(contadorDeLetras);
        archivo->leerCaracter(caracterLeido);
        if(cambioDeLinea){
            cambioDeLinea = false;
            posicionComienzoDeLinea = archivo->getPosicionCursor() - 1;
        }
        ;
        if(caracterLeido == '\n'){
            cambioDeLinea = true;
        }
        if(caracterABuscar == caracterLeido){
            contadorDeLetras++;
            if(contadorDeLetras == cadena.capacity()){
                contadorDeLetras = 0;
                archivo->setPosicionCursor(posicionComienzoDeLinea);
                archivo->leerLinea(lineaDeCadenaBuscada);
                //std::cout << lineaDeCadenaBuscada << std::endl; // Se comenta para no mostrar las lineas sobre las que busca
                cambioDeLinea = true;
                cadenaEncontrada=true;
            }
        }
        else
            contadorDeLetras = 0;

    }
    delete archivo;
    return cadenaEncontrada;
}

bool Logger::find(std::string cadena){
	int buffer[1];
	buffer[0]=0;
	FILE *archdisco;
	archdisco = fopen("contador.dat","rb");
	fread(buffer,4,1,archdisco);
	fclose(archdisco);
	string nombre="logger";
	for(int i=1;i<buffer[0];i++){
		string numeroLog=itos(i);
		string nuevoNombre=nombre+numeroLog+".txt";

		char* ptrArchivo=&nuevoNombre[0];
		findFile(ptrArchivo, cadena);
	};
	string nuevoNombre=nombre+".txt";
	char* ptrArchivo=&nuevoNombre[0];
	if(!findFile(ptrArchivo,cadena))
		return false;
	return true;
};

void Logger::writeFile(std::string cadena){
	archivo=new ArchivoTexto("logger.txt");
	long tamanio=0;
	FILE *archdisco;
	archdisco = fopen("contador.dat","a");
	fseek(archdisco, 0, SEEK_END);
	size_t size = ftell(archdisco);
	fclose(archdisco);
	if(archivo->getTamanio()==0 && size==0){

		archdisco = fopen("contador.dat","wb");
		int buffer[1];
		buffer[0]=1;

		fwrite(buffer,4,1,archdisco);
		fclose(archdisco);
	}

	archivo->irAlFinal();

	archivo->escribir(cadena);
	archivo->terminarLinea();
	tamanio= archivo->getTamanio();
	if (tamanio> TAMANIO_LIMITE){
		int buffer[1];
		buffer[0]=0;

		FILE *archdisco;
		archdisco = fopen("contador.dat","rb");
		fread(buffer,4,1,archdisco);
		fclose(archdisco);
		buffer[0]++;
		archdisco = fopen("contador.dat","wb");
		fwrite(buffer,4,1,archdisco);
		fclose(archdisco);
		buffer[0]--;
		string numeroLog=itos(buffer[0]);
		string nombre="logger";
		string nuevoNombre=nombre+numeroLog+".txt";
		char* ptrNewName=&nuevoNombre[0];
		rename("logger.txt",ptrNewName);
		delete archivo;
		archivo=new ArchivoTexto("logger.txt");
	}
	delete archivo;
};

//Busca la cadena de caracteres en el log.
bool Logger::findString(char * e_arg){
	std::string cadena = "";
	cadena = cadena + this->processLine(e_arg);
    return this->find(cadena);
}

void Logger::print(){
	std::string cadenaLeida="";
	archivo=new ArchivoTexto("logger.txt");
	while (archivo->leerLinea(cadenaLeida)){
		std::cout<<cadenaLeida<<std::endl;
	}
	delete archivo;
};

void Logger::insert(char *e_arg)
{
    std::string cadena = "";
    cadena = cadena + this->processLine(e_arg);
    this->writeFile(cadena);
}

void Logger::printHelp(void) {
	printf("\t-B, --buscar \t\tBuscar cadena de caracteres.\n");
	printf("\t-h, --ayuda \t\tAyuda para la operacion de la aplicacion.\n");
	printf("\t-I, --ingresar \tIngresar datos a la estructura.\n");
	printf("\t-S, --secuenciar \t\tVolcar todos los datos en un archivo de texto plano.\n");

	return;
}
