/*
 * Table.cpp
 *
 *  Created on: 04/04/2010
 *      Author: pablo
 */

#include "Table.h"

Table::Table() {
	// TODO Auto-generated constructor stub

}

Table::~Table() {
	// TODO Auto-generated destructor stub
}

FILE * Table::abrirArch(char formato[2]){
	FILE * arch_tabla;
	char * nombreArchTabla = "tabla.txt";
	arch_tabla = fopen(nombreArchTabla,formato);
	if( !arch_tabla )
	  printf( "\nError: No se pudo abrir la tabla correctamente\n" );
	return arch_tabla;
}

FILE * Table::abrirArchLectura(){
	return abrirArch("r");
}

FILE * Table::abrirArchEscritura(){
	return abrirArch("w");
}

void Table::cerrarArch(FILE * arch_tabla){
	if( fclose(arch_tabla) )
		      printf( "\nError: No se pudo cerrar la tabla correctamente\n" );
}

FILE* Table::crearArchivoTemporal(){
	FILE * arch_tabla_temporal;
	char * nombreArchTabla = "tablaTemporal.txt";
	arch_tabla_temporal = fopen(nombreArchTabla,"w");
	if( !arch_tabla_temporal )
	  printf( "\nError: No se pudo abrir la tabla correctamente\n" );
	return arch_tabla_temporal;
}

FILE * Table::crearArch(){
	FILE* archTabla = abrirArchEscritura();
	//TODO: cambiar el renglon de aca abajo por este: "fprintf( archTabla, "0\n0" );"
	fprintf( archTabla, "9\n0\n1\n2\n3\n4\n5\n6\n7\n8" );

	cerrarArch(archTabla);
	return archTabla;
}

int Table::parsear(int * listaElementosTabla){
	int tamTabla;
	char linea[180];
	char * ptr = NULL;
	int cont = 0;
	FILE * arch_tabla;

	arch_tabla = abrirArchLectura();

	//Tomo el primer renglon (tamTabla)
	fgets(linea,180,arch_tabla);
	ptr = strtok(linea," \n\t");
	tamTabla = atoi(ptr);

	for(int i = 1;i<=tamTabla;i++){
		fgets(linea,180,arch_tabla);
		ptr = strtok(linea," \n\t");
		if (ptr == NULL)
				printf("\nError: El archivo de la tabla contiene un renglon vacio. El mismo no se puede parsear. No puede contener un renglon vacio.\n\t");
		else{
			listaElementosTabla[cont] = atoi(ptr);
			cont++;
		}
	}

	cerrarArch(arch_tabla);

	return tamTabla;
}

int Table::obtenerTamanio(){
	int tamTabla;
	char linea[180];
	char * ptr = NULL;
	FILE * arch_tabla;
	arch_tabla = abrirArchLectura();
	//Tomo el primer renglon (tamTabla)
	fgets(linea,180,arch_tabla);
	ptr = strtok(linea," \n\t");
	tamTabla = atoi(ptr);
	cerrarArch(arch_tabla);
	return tamTabla;
}

int Table::obtenerBloqueAApuntarEnArchivoHash(int registroAApuntarEnTabla){
	FILE * arch_tabla;
	char * ptr = NULL;
	char linea[180];

	arch_tabla = abrirArchLectura();

	for (int i = 0;i<registroAApuntarEnTabla+2;i++){
		if (!feof(arch_tabla))
			fgets(linea,180,arch_tabla);
		else{
			printf("\nError: hubo un error al intentar acceder a un registro de la tabla en obtenerBloqueAApuntarEnArchivoHash.");
			return -1;
		}
	}

	ptr = strtok(linea," \n\t");
	int resultado = atoi(ptr);

	cerrarArch(arch_tabla);

	return resultado;
}

void Table::modificarRegistro(int numReg,int valorNuevo){
	int numeroRenglon = numReg+1;
	int tam_tabla_a_borrar = obtenerTamanio();
	if ((numReg<tam_tabla_a_borrar)&&(numReg>=0)){
		FILE * arch_tabla_a_borrar;
		arch_tabla_a_borrar = abrirArchLectura();
		FILE * archTemporal = crearArchivoTemporal();
		char linea[180];
		char * ptr = NULL;
		char valorObtenido[10];
		char valorNuevoString[10];
		sprintf(valorNuevoString,"%i",valorNuevo);

		for (int i = 1;i<=numeroRenglon;i++){
			if (!feof(arch_tabla_a_borrar)){
				fgets(linea,180,arch_tabla_a_borrar);
				ptr = strtok(linea," \n\t");
				strcpy(valorObtenido,ptr);
				fprintf( archTemporal, valorObtenido );
				fprintf( archTemporal, "\n" );
			}
			else
				printf("\nError: hubo un error al intentar acceder a un registro de la tabla en modificarRegistroEnTabla1.");
		}

		fprintf( archTemporal, valorNuevoString );
		fprintf( archTemporal, "\n" );
		fgets(linea,180,arch_tabla_a_borrar);

		if (numeroRenglon+1<=tam_tabla_a_borrar){
			for (int i = numeroRenglon+1;i<=tam_tabla_a_borrar;i++){
				if (!feof(arch_tabla_a_borrar)){
					fgets(linea,180,arch_tabla_a_borrar);
					ptr = strtok(linea," \n\t");
					strcpy(valorObtenido,ptr);
					fprintf( archTemporal, valorObtenido );
					fprintf( archTemporal, "\n" );
				}
				else
					printf("\nError: hubo un error al intentar acceder a un registro de la tabla en modificarRegistroEnTabla2.");
			}
		}
		cerrarArch(arch_tabla_a_borrar);
		cerrarArch(archTemporal);
		remove("tabla.txt");
		rename("tablaTemporal.txt","tabla.txt");
	}
	else{
		printf("\nError: hubo un error al intentar acceder a un registro de la tabla. Registro %i no existe en la tabla.",numReg);
	}
}

void Table::imprimir(int * listaElementosTabla,int tamTabla){
	printf("\nTabla (de tamaño = %i):\n ",tamTabla);
	for (int i = 0; i<tamTabla;i++){
		printf("%i",listaElementosTabla[i]);
		if (i<tamTabla-1)
			printf(" | ");
	}
	if (tamTabla == 0)
		printf("Sin elementos ..");
}

void Table::duplicar(){
	int tamTabla = obtenerTamanio();
	int listaElementosTabla[tamTabla];
	parsear(listaElementosTabla);

	FILE * archTemporal = crearArchivoTemporal();
	char nuevoTam[10];
	int aux = tamTabla*2;
	sprintf(nuevoTam,"%i",aux);
	char valorObtenido[10];

	fprintf( archTemporal, nuevoTam );
	fprintf( archTemporal, "\n" );

	for(int i = 0;i<tamTabla;i++){
			sprintf(valorObtenido,"%i",listaElementosTabla[i]);
			fprintf( archTemporal,  valorObtenido);
			fprintf( archTemporal, "\n" );
	}
	for(int i = 0;i<tamTabla;i++){
			sprintf(valorObtenido,"%i",listaElementosTabla[i]);
			fprintf( archTemporal,  valorObtenido);
			fprintf( archTemporal, "\n" );
	}

	cerrarArch(archTemporal);
	remove("tabla.txt");
	rename("tablaTemporal.txt","tabla.txt");
}



