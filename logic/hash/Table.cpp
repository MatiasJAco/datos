/*
 * Table.cpp
 *
 *  Created on: 04/04/2010
 *      Author: pablo
 */

#include "Table.h"

Table::Table() {
}

Table::~Table() {
	//se tuvo en cuenta en la implementacion que la tabla quede siempre guardada en disco despues de cada operacion
}

bool Table::exists(char nombreArchTabla[10]){
	if (fopen(nombreArchTabla,"r"))
		return true;
	else
		return false;
}

FILE * Table::openFile(char format[2]){
	FILE * arch_tabla;
	char nombreArchTabla[10] = "tabla.txt";
	arch_tabla = fopen(nombreArchTabla,format);
	return arch_tabla;
}

FILE * Table::openFileForRead(){
	char format[2]="r";
	return openFile(format);
}

FILE * Table::openFileForWrite(){
	char format[2]="w";
	return openFile(format);
}

FILE * Table::openFileForAppend(){
	char format[2]="a";
	return openFile(format);
}

void Table::closeFile(FILE * tableFile){
	fclose(tableFile);
}

FILE* Table::createTemporalFile(){
	FILE * arch_tabla_temporal;
	char nombreArchTabla[18] = "tablaTemporal.txt";
	arch_tabla_temporal = fopen(nombreArchTabla,"w");
	return arch_tabla_temporal;
}

FILE * Table::createFile(){
	FILE* archTabla;
	char nombreArchTabla[10] = "tabla.txt";
	if (!exists(nombreArchTabla)) {
		archTabla = openFileForWrite();
		fprintf( archTabla, "1\n0" ); // Se crea la tabla, con size 1.
		closeFile(archTabla);
	} else {
		archTabla = openFileForAppend();
		closeFile(archTabla);
	}
	return archTabla;
}

int Table::parse(unsigned int * listElementsTable){
	int sizeOfTable;
	char linea[180];
	char * ptr = NULL;
	int cont = 0;
	FILE * arch_tabla;

	arch_tabla = openFileForRead();

	//Tomo el primer renglon (sizeOfTable)
	fgets(linea,180,arch_tabla);
	ptr = strtok(linea," \n\t");
	sizeOfTable = atoi(ptr);

	for(int i = 1;i<=sizeOfTable;i++){
		fgets(linea,180,arch_tabla);
		ptr = strtok(linea," \n\t");
		if (ptr != NULL){
			listElementsTable[cont] = atoi(ptr);
			cont++;
		}
	}

	closeFile(arch_tabla);

	return sizeOfTable;
}

unsigned int Table::getSize(){
	unsigned int sizeOfTable;
	char linea[180];
	char * ptr = NULL;
	FILE * arch_tabla;
	arch_tabla = openFileForRead();
	//Tomo el primer renglon (sizeOfTable)
	fgets(linea,180,arch_tabla);
	ptr = strtok(linea," \n\t");
	sizeOfTable = atoi(ptr);
	closeFile(arch_tabla);
	return sizeOfTable;
}

int Table::getNumberOfBucketInHash(int NumOfRegToPointInTable){
	FILE * arch_tabla;
	char * ptr = NULL;
	char linea[180];

	arch_tabla = openFileForRead();

	for (int i = 0;i<NumOfRegToPointInTable+2;i++){
		if (!feof(arch_tabla))
			fgets(linea,180,arch_tabla);
		else
			return -1;

	}

	ptr = strtok(linea," \n\t");
	int resultado = atoi(ptr);

	closeFile(arch_tabla);

	return resultado;
}

void Table::modifyRegister(int numReg,unsigned int newValue){
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
				fprintf(archTemporal,"%s\n",valorObtenido);
			}
		}

		fprintf( archTemporal,"%s\n" ,valorNuevoString );
		fgets(linea,180,arch_tabla_a_borrar);

		if (numeroRenglon+1<=tam_tabla_a_borrar){
			for (int i = numeroRenglon+1;i<=tam_tabla_a_borrar;i++){
				if (!feof(arch_tabla_a_borrar)){
					fgets(linea,180,arch_tabla_a_borrar);
					ptr = strtok(linea," \n\t");
					strcpy(valorObtenido,ptr);
					fprintf(archTemporal,"%s\n",valorObtenido);
				}
			}
		}
		closeFile(arch_tabla_a_borrar);
		closeFile(archTemporal);
		remove("tabla.txt");
		rename("tablaTemporal.txt","tabla.txt");
	}
}

void Table::print(){
	int sizeOfTable = this->getSize();
	unsigned int listElementsTable[sizeOfTable];
	this->parse(listElementsTable);

	printf("Tabla (de tamaño = %i): ",sizeOfTable);
	for (int i = 0; i<sizeOfTable;i++){
		printf("%i",listElementsTable[i]);
		if (i<sizeOfTable-1)
			printf(" | ");
	}
	if (sizeOfTable == 0)
		printf("Sin elementos ..");

	printf("\n");
}

void Table::duplicate(){
	int sizeOfTable = getSize();
	unsigned int listElementsTable[sizeOfTable];
	parse(listElementsTable);

	FILE * archTemporal = createTemporalFile();
	char nuevoTam[10];
	int aux = sizeOfTable*2;
	sprintf(nuevoTam,"%i",aux);
	char valorObtenido[10];

	fprintf(archTemporal,"%s\n",nuevoTam);

	for(int i = 0;i<sizeOfTable;i++){
			sprintf(valorObtenido,"%i",listElementsTable[i]);
			fprintf( archTemporal, "%s\n" ,valorObtenido);
	}
	for(int i = 0;i<sizeOfTable;i++){
			sprintf(valorObtenido,"%i",listElementsTable[i]);
			fprintf( archTemporal, "%s\n" ,valorObtenido);
	}

	closeFile(archTemporal);
	remove("tabla.txt");
	rename("tablaTemporal.txt","tabla.txt");
}

int Table::verifyAndDivide(){
	int sizeOfTable = getSize();
	if (sizeOfTable<=1) return -1;
	if (fmod(sizeOfTable,2)!=0) return -1;

	unsigned int listElementsTable[sizeOfTable];
	parse(listElementsTable);
	int pos;
	for (int i = 0; i<sizeOfTable/2;i++){
		pos=i+sizeOfTable/2;
		if (listElementsTable[i]!=listElementsTable[pos])
			return -1;
	}

	//aca ya se verifico y se puede eliminar
	FILE * archTemporal = createTemporalFile();
	char nuevoTam[10];
	int aux = (int) ( sizeOfTable/2);
	sprintf(nuevoTam,"%i",aux);
	char valorObtenido[10];

	fprintf( archTemporal,"%s\n" ,nuevoTam );

	for(int i = 0;i<sizeOfTable/2;i++){
			sprintf(valorObtenido,"%i",listElementsTable[i]);
			fprintf( archTemporal,"%s\n" ,valorObtenido );
	}
	closeFile(archTemporal);
	remove("tabla.txt");
	rename("tablaTemporal.txt","tabla.txt");

	return 0;
}

int Table::getFirstTimeInTable(unsigned int value){
	int sizeOfTable = this->getSize();
	unsigned int listElementsTable[sizeOfTable];
	this->parse(listElementsTable);
	int result = 0;
	bool continuar= true;
	int i = 0;
	while (continuar&&(i<sizeOfTable)){
		if(listElementsTable[i]!=value)
			result++;
		else
			continuar=false;
		i++;
	}
	return result;
}

bool Table::changeFirstTimeInTable(unsigned int value, unsigned int newValue){
	int position = getFirstTimeInTable(value);
	this->modifyRegister(position,newValue);
	return true;
}

int Table::verifyJumps(int position, int jump){
	int element1,element2;
	int sizeOfTable = this->getSize();
	unsigned int listElementsTable[sizeOfTable];
	this->parse(listElementsTable);
	int i;

	/* Me muevo para adelante */
	i =  position+jump;
	if ( i <= (sizeOfTable-1) ){
		element1 = listElementsTable[i];
	}
	else{   //se paso del final y hay que volver al ppio
		i = i -sizeOfTable ;
		element1 = listElementsTable[i];
	}

	/* Me muevo para atras */
	i =  position-jump;
	if ( i >= 0 ){
		element2 = listElementsTable[i];
	}
	else{   //se paso del ppio y hay que volver desde atras
		i = i + sizeOfTable;
		element2 = listElementsTable[i];
	}

	if (element1==element2)	return element1;

	return -1;
}

void Table::jumpAndReplace(int position, int jump, int element){
	int sizeOfTable = this->getSize();
	unsigned int listElementsTable[sizeOfTable];
	this->parse(listElementsTable);
	int i = position;

	//me paro lo mas al ppio posible en la tabla segun los saltos "jumps"
	while ((i-jump)>=0){
		i = i - jump;
	}

	//reemplazo ese elemento
	this->modifyRegister(i,element);

	//mientras que pueda, voy saltando y reemplazando el valor en la tabla
	while ((i+jump)<= (sizeOfTable-1)){
		i = i + jump;
		this->modifyRegister(i,element);
	}
}
