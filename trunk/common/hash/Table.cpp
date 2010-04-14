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

FILE * Table::openFile(char format[2]){
	FILE * arch_tabla;
	char * nombreArchTabla = "tabla.txt";
	arch_tabla = fopen(nombreArchTabla,format);
	if( !arch_tabla )
	  printf( "\nError: No se pudo abrir la tabla correctamente\n" );
	return arch_tabla;
}

FILE * Table::openFileForRead(){
	return openFile("r");
}

FILE * Table::openFileForWrite(){
	return openFile("w");
}

void Table::closeFile(FILE * tableFile){
	if( fclose(tableFile) )
		      printf( "\nError: No se pudo cerrar la tabla correctamente\n" );
}

FILE* Table::createTemporalFile(){
	FILE * arch_tabla_temporal;
	char * nombreArchTabla = "tablaTemporal.txt";
	arch_tabla_temporal = fopen(nombreArchTabla,"w");
	if( !arch_tabla_temporal )
	  printf( "\nError: No se pudo abrir la tabla correctamente\n" );
	return arch_tabla_temporal;
}

FILE * Table::createFile(){
	FILE* archTabla = openFileForWrite();
	//TODO: cambiar el renglon de aca abajo por este: "fprintf( archTabla, "0\n0" );"
	fprintf( archTabla, "9\n0\n1\n2\n3\n4\n5\n6\n7\n8" );

	closeFile(archTabla);
	return archTabla;
}

int Table::parse(int * listElementsTable){
	int tamTabla;
	char linea[180];
	char * ptr = NULL;
	int cont = 0;
	FILE * arch_tabla;

	arch_tabla = openFileForRead();

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
			listElementsTable[cont] = atoi(ptr);
			cont++;
		}
	}

	closeFile(arch_tabla);

	return tamTabla;
}

int Table::getSize(){
	int tamTabla;
	char linea[180];
	char * ptr = NULL;
	FILE * arch_tabla;
	arch_tabla = openFileForRead();
	//Tomo el primer renglon (tamTabla)
	fgets(linea,180,arch_tabla);
	ptr = strtok(linea," \n\t");
	tamTabla = atoi(ptr);
	closeFile(arch_tabla);
	return tamTabla;
}

int Table::getNumberOfBucketInHash(int NumOfRegToPointInTable){
	FILE * arch_tabla;
	char * ptr = NULL;
	char linea[180];

	arch_tabla = openFileForRead();

	for (int i = 0;i<NumOfRegToPointInTable+2;i++){
		if (!feof(arch_tabla))
			fgets(linea,180,arch_tabla);
		else{
			printf("\nError: hubo un error al intentar acceder a un registro de la tabla en obtenerBloqueAApuntarEnArchivoHash.");
			return -1;
		}
	}

	ptr = strtok(linea," \n\t");
	int resultado = atoi(ptr);

	closeFile(arch_tabla);

	return resultado;
}

void Table::modifyRegister(int numReg,int newValue){
	int numeroRenglon = numReg+1;
	int tam_tabla_a_borrar = getSize();
	if ((numReg<tam_tabla_a_borrar)&&(numReg>=0)){
		FILE * arch_tabla_a_borrar;
		arch_tabla_a_borrar = openFileForRead();
		FILE * archTemporal = createTemporalFile();
		char linea[180];
		char * ptr = NULL;
		char valorObtenido[10];
		char valorNuevoString[10];
		sprintf(valorNuevoString,"%i",newValue);

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
		closeFile(arch_tabla_a_borrar);
		closeFile(archTemporal);
		remove("tabla.txt");
		rename("tablaTemporal.txt","tabla.txt");
	}
	else{
		printf("\nError: hubo un error al intentar acceder a un registro de la tabla. Registro %i no existe en la tabla.",numReg);
	}
}

void Table::print(int * listElementsTable,int sizeOfTable){
	printf("\nTabla (de tamaño = %i):\n ",sizeOfTable);
	for (int i = 0; i<sizeOfTable;i++){
		printf("%i",listElementsTable[i]);
		if (i<sizeOfTable-1)
			printf(" | ");
	}
	if (sizeOfTable == 0)
		printf("Sin elementos ..");
}

void Table::duplicate(){
	int tamTabla = getSize();
	int listaElementosTabla[tamTabla];
	parse(listaElementosTabla);

	FILE * archTemporal = createTemporalFile();
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

	closeFile(archTemporal);
	remove("tabla.txt");
	rename("tablaTemporal.txt","tabla.txt");
}



