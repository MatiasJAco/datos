/*
 * Ppmc.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */
#include "Ppmc.h"

const string Ppmc::ZERO_CONTEXT = "0";
const string Ppmc::MINUS_ONE_CONTEXT = "-1";

Ppmc::Ppmc(GeneralStructure* generalStructure){
	this->generalStructure = generalStructure;
	this->minusOneCtxtFreqTable = new FrequencyTable();
	for (int i = 0; i <= 256; i++) {
		this->minusOneCtxtFreqTable->setFrequency(i,1); // Llena con 1 ocurrencia los 256 caracteres ASCII y el EOF.
	}
	this->contextStats=NULL;
	this->logger = Logger::Instance();
}

Ppmc::~Ppmc() {
}

//-----------------------------------------------------------------------------------------------
//-----------------------------------COMPRESION -------------------------------------------------
//-----------------------------------------------------------------------------------------------

FrequencyTable* Ppmc::getFrequencyTable(std::string stringContext,bool newRead) {
	FrequencyTable* frequencyTable = new FrequencyTable();
	StringInputData stringInputData;
	if (newRead){
		this->findInStructure(stringContext,stringInputData);
	} else{
		this->getNextContext(stringContext,stringInputData);
	};
	frequencyTable->deserialize(stringInputData.getValue());
	return frequencyTable;
}

std::string Ppmc::getCompressionOutFile(std::string path, int maxContext) {
	std::string outFile = path;
	outFile.append(".ppmc");
	stringstream ss;
	ss << maxContext;
	outFile.append(ss.str());
	return outFile;
}

bool Ppmc::compress(std::string path,int maxContext) {
	std::string log = ";Comprimiendo archivo: ";
	log.append(path);
	this->logger->insert(&log[0]);

	ArithmeticCompressor* compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR, this->getCompressionOutFile(path, maxContext), 24);
	this->setContextStats(maxContext);
	bool newRead=true;
	std::cout << "Comprimiendo archivo... (" << path << ")" << std::endl;
	SequentialFile* sequentialFile = new SequentialFile(READ_FILE);
	sequentialFile->open(path);
	//TODO que pasa si el archivo esta vacio?? hay que validarlo
	char character = sequentialFile->readChar();
	//TODO no seria strinContext = "_" o  " " (vacio) ?? (para indicar el ctx cero)
	std::string stringContext = ZERO_CONTEXT;
	int actualContextNumber = 0; // Representa el número de contexto más alto que se alcanzó hasta ahora.
	FrequencyTable* previousFrequencyTable = new FrequencyTable();

	this->ppmcCompressionEmitter(compressor, stringContext, character, actualContextNumber, maxContext, newRead, previousFrequencyTable);

	if (actualContextNumber < maxContext) { // Si el contexto maximo es mayor a cero, se incrementa el contexto actual a 1.
		actualContextNumber++;
		stringContext = character;
	}

	bool isNotEof = false;

	character = sequentialFile->readChar(isNotEof);

	while (isNotEof) {
		this->ppmcCompressionEmitter(compressor, stringContext, character, actualContextNumber, maxContext, newRead, previousFrequencyTable);
		if (actualContextNumber < maxContext) {
			actualContextNumber++;
			stringContext.append(1,character);
		} else {
			stringContext.append(1,character);
			stringContext = stringContext.substr(1, stringContext.length());
		}
		character = sequentialFile->readChar(isNotEof);
	}
	sequentialFile->close();
	delete compressor;
	std::cout << "Fin de compresion" << std::endl;

	log = ";Se termino de comprimir el archivo: ";
	log.append(path);
	this->logger->insert(&log[0]);

	return true;
}

void Ppmc::ppmcCompressionEmitter(ArithmeticCompressor* compressor, std::string stringContext, char character, int actualContextNumber, int maxContext, bool newRead, FrequencyTable* previousFrequencyTable) {
	FrequencyTable* frequencyTable;
	FrequencyTable* excludedFrequencyTable;
	FrequencyTable* nextExclusionTable = previousFrequencyTable;

	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		frequencyTable = this->getFrequencyTable(stringContext, newRead);

		nextExclusionTable = new FrequencyTable(*frequencyTable);
		excludedFrequencyTable = new FrequencyTable(frequencyTable->excludeFromTable(*previousFrequencyTable)); // Se excluyen los caracteres que estaban en el contexto anterior.

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado, se emite un escape y se agrega el caracter faltante.
			if ((excludedFrequencyTable->getFrequency(ESC_CHAR) == 1) && (excludedFrequencyTable->getFrequencyTotal() == 1)) {
				std::cout << "Emitiria el caracter Escape en el contexto " << stringContext << " con " << excludedFrequencyTable->getFrequency(ESC_CHAR) << "/" << excludedFrequencyTable->getFrequencyTotal() << std::endl;
			} else {
				compressor->compress(ESC_CHAR, (*excludedFrequencyTable));
				std::cout << "Emito el caracter Escape en el contexto " << stringContext << " con " << excludedFrequencyTable->getFrequency(ESC_CHAR) << "/" << excludedFrequencyTable->getFrequencyTotal() << std::endl;
				//std::cout << std::endl << "Tabla excluida   : " << excludedFrequencyTable->toString() << std::endl << std::endl;
			}
			frequencyTable->increaseFrequency(ESC_CHAR,1);//incremento frecuencia al escape
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
		} else { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			compressor->compress(character, (*excludedFrequencyTable));
			std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << excludedFrequencyTable->getFrequency(character) << "/" << excludedFrequencyTable->getFrequencyTotal() << std::endl;
			//std::cout << std::endl << "Tabla excluida   : " << excludedFrequencyTable->toString() << std::endl << std::endl;
			this->countHit(stringContext);
			frequencyTable->increaseFrequency(character,1);
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			return;
		}
	} else { // No existe el contexto pasado por parametro. Por lo tanto se lo crea.
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
		std::cout << "Emitiria el caracter Escape en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << "/" << frequencyTable->getFrequencyTotal() << std::endl;
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->insertInStructure(stringContext,frequencyTable->toString());
	}
	stringContext = stringContext.substr(1,stringContext.length());
	actualContextNumber--;
	if (actualContextNumber > 0) {
		newRead=false;
		this->ppmcCompressionEmitter(compressor, stringContext, character, actualContextNumber, maxContext, newRead, nextExclusionTable); // Bajo de contexto progresivamente.
	} else if (actualContextNumber == 0) {
		stringContext = ZERO_CONTEXT;
		newRead=true;
		this->ppmcCompressionEmitter(compressor, stringContext, character, actualContextNumber, maxContext, newRead, nextExclusionTable); // Bajo al contexto 0 que es el anteúltimo.
	} else { // Llegamos al contexto -1.
		(*minusOneCtxtFreqTable) = this->minusOneCtxtFreqTable->excludeFromTable(*nextExclusionTable); // Se excluyen los caracteres que estaban en el contexto anterior.
		compressor->compress(character, (*minusOneCtxtFreqTable));
		std::cout << "Emito el caracter " << character <<  " en el contexto -1 con " << this->minusOneCtxtFreqTable->getFrequency(character) << "/" << minusOneCtxtFreqTable->getFrequencyTotal() << std::endl;
		//std::cout << std::endl << "Tabla excluida   : " << minusOneCtxtFreqTable->toString() << std::endl << std::endl;
	}
}



//-----------------------------------------------------------------------------------------------
//-----------------------------------DESCOMPRESION ----------------------------------------------
//-----------------------------------------------------------------------------------------------


short Ppmc::borrarEsteMetodo(int contador){
	short result;
	switch (contador){
		case 1: result =  68; break;		//D
		case 2: result = 257; break;		//ESC
		case 3: result = 73;  break;		//I
		case 4: result = 257; break;		//ESC
		case 5: result = 257; break;		//ESC
		case 6: result = 86;  break;		//V
		case 7: result = 257; break;		//ESC
		case 8: result = 257; break;		//ESC
		case 9: result = 73;  break;		//I
		case 10: result = 257; break;		//ESC
		case 11: result = 257; break;		//ESC
		case 12: result = 68; break;		//D
	}
	return result;
}

bool Ppmc::getMetadata(std::string path, std::string & outPath, int & maxContext){
	size_t position = path.find(".ppmc");
	if (position != string::npos) {
		outPath = path.substr(0, position);
		maxContext = atoi(path.substr(position+5, path.length()-position-5).c_str());
	} else {
		return false; // El archivo no posee la extension ".ppmc".
	}

	position = outPath.find(".txt");
	outPath = outPath.substr(0, position);
	outPath.append("Descomprimido.txt");
	return true;
}

// -1 si el primero es menor al segundo, 0 si son iguales, 1 si el primero es mayor al segundo
int Ppmc::compareStringContexts(std::string previousStringContext,std::string stringContext){
	if (previousStringContext == ZERO_CONTEXT && stringContext==MINUS_ONE_CONTEXT )
		return 1;
	else if (previousStringContext.length()==1 && previousStringContext!=ZERO_CONTEXT)
		return 1;
	else if (previousStringContext==MINUS_ONE_CONTEXT && stringContext != MINUS_ONE_CONTEXT)
		return -1;
	else if (previousStringContext == stringContext)
		return 0;
	return -1;
}

bool Ppmc::deCompress(const std::string & path) {
	std::string log = ";Descomprimiendo archivo: ";
	log.append(path);
	this->logger->insert(&log[0]);
	std::string outPath = "";
	int maxContext;
	if (!getMetadata( path, outPath, maxContext))
		return false; // El archivo no posee la extension ".ppmc".

	std::cout << "Descomprimiendo archivo... (" << path << ") con contexto "<<maxContext << std::endl;
	SequentialFile* sequentialFile = new SequentialFile(WRITE_FILE);
	sequentialFile->open(outPath);

	//instancio el compresor aritmetico como Decompresor.
	ArithmeticCompressor* arithmeticCompressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR, path, 24);

	std::string stringContext = MINUS_ONE_CONTEXT;
	std::string previousStringContext="";
	std::string maxStringContext = "";
	std::string maxStringContextDesfasadoEn1 = "";
	//int actualContextNumber = -1; // Representa el número de contexto -1 (de donde arranca la descompresion)
	char character;
	char characterAnterior;
	short shortCharacter;
	FrequencyTable * frequencyTable = minusOneCtxtFreqTable;
//	FrequencyTable* previousFrequencyTable;
//	FrequencyTable * excludedFrequencyTable;
	bool isNotEOF = true;
	int borrarContador = 1; //todo hacerle caso al nombre de la variable :D


	//primer llamado para inicializar al ctxt 0
	updateFrequencyTables(ZERO_CONTEXT, ESC_CHAR);


//-----------------------------PRIMER PASADA-----------------------------
	string borrar = frequencyTable->toString();
	cout << "Tabla p el aritmetico (ctx '"<<stringContext<<"' / CantElemSinESC "<<frequencyTable->getCharCount()<<") : "<<borrar << endl;
//	shortCharacter = arithmeticCompressor->decompress(*frequencyTable);
	shortCharacter = borrarEsteMetodo(borrarContador);
	character = (char) shortCharacter;
	if (shortCharacter != ESC_CHAR) cout<<"aritmetico emitio : "<< character<<endl;
	if (shortCharacter == EOF_CHAR){
		cout<<"El compresor aritmetico devolvio EOF al ppio de todo en el decompresor";
		return false; //TODO false o true?
	}
	//escribo en el archivo de salida el caracter.
	sequentialFile->writeChar(character);
	cout<<"MANDO AL ARCHIVO ( "<<outPath<<" ) : '" << character << "'" << endl;
	characterAnterior = character;
	getMaxStringContext(maxStringContext,characterAnterior,maxContext,true);
	//cout << "maxStringContext: " << maxStringContext<<", ";
	getMaxStringContextDesfasado(maxStringContextDesfasadoEn1,character,maxContext,true);
	//cout << "maxStringContextDesfasadoEn1: " << maxStringContextDesfasadoEn1<<", ";
	//cout << "previousStringContext: " << previousStringContext<<endl;

	//actualizo contexto cero
	stringContext = ZERO_CONTEXT;
	updateFrequencyTables(stringContext,shortCharacter);
	cout << "UPDATE: ctx " << stringContext<<","<<(char) shortCharacter<<endl;
	//actualizo contexto 1
	stringContext = character;
	updateFrequencyTables(stringContext, ESC_CHAR);//creo la tabla del contexto con esc(1)
	cout << "CREATE (o update): " << stringContext<<endl;
	previousStringContext = MINUS_ONE_CONTEXT;
	borrarContador++;

	//-----------------------------COMIENZO DE 2da PASADA-----------------------------
	stringContext=ZERO_CONTEXT;
	frequencyTable = this->getFrequencyTable(stringContext, true);
	borrar = frequencyTable->toString();
	cout << "Tabla p el aritmetico (ctx '"<<stringContext<<"' / CantElemSinESC "<<frequencyTable->getCharCount()<<") : "<<borrar << endl;
//	shortCharacter = arithmeticCompressor->decompress(*frequencyTable);
	shortCharacter = borrarEsteMetodo(borrarContador);
	if (shortCharacter != ESC_CHAR) cout<<"aritmetico emitio : "<< character<<endl;
	else cout<<"aritmetico emitio : ESC "<<endl;

	while(isNotEOF){
				borrarContador++;
				if (borrarContador == 14){
					cout<< "cagamos: 13"<<endl;
					sequentialFile->close();
					return false;}

		//si el caracter no es ESC ni EOF, lo emito,armo el maxStringContext y actualizo las tablas de frec q necesito, y creo las nuevas
		if (shortCharacter != ESC_CHAR){   // Aritmetico no emitio ESC -> me muevo a un contexto superior
				//escribo en el archivo de salida el caracter.
				sequentialFile->writeChar(character);
				cout<<"MANDO AL ARCHIVO ( "<<outPath<<" ) : '" << character << "'" << endl;

				getMaxStringContext(maxStringContext,characterAnterior,maxContext,false);
				//cout << "maxStringContext: " << maxStringContext<<", ";
				getMaxStringContextDesfasado(maxStringContextDesfasadoEn1,character,maxContext,false);
				//cout << "maxStringContextDesfasadoEn1: " << maxStringContextDesfasadoEn1<<", ";
				//cout << "previousStringContext: " << previousStringContext<<endl;


				//-----------actualizo todas las tablas de frecuencias que necesite--------------
				std::string maxStringContextAux;
				if (previousStringContext.length()!=maxContext){
					for (unsigned int i = maxStringContext.length(); i>=1;i--){
						maxStringContextAux = maxStringContext;
						stringContext = maxStringContextAux.substr(maxStringContext.length()-i,i);
						updateFrequencyTables(stringContext,shortCharacter);
						cout << "UPDATE: ctx " << stringContext<<","<<(char) shortCharacter<<endl;
					}
				}
				else {   //previousContext tiene mismo tam que maxContext
					for (unsigned int i = previousStringContext.length(); i>=1;i--){
						maxStringContextAux = previousStringContext;
						stringContext = maxStringContextAux.substr(previousStringContext.length()-i,i);
						updateFrequencyTables(stringContext,shortCharacter);
						cout << "UPDATE: ctx " << stringContext<<","<<(char) shortCharacter<<endl;
					}
				}

				//-------actualizo la del cero
				stringContext = ZERO_CONTEXT;
				updateFrequencyTables(stringContext,shortCharacter);
				cout << "UPDATE: ctx " << stringContext<<","<<(char) shortCharacter<<endl;


				// -------creo todas las tablas de frecuencias nuevas--
				std::string stringContextAux;
				for (unsigned int i = maxStringContextDesfasadoEn1.length(); i>=1;i--){
					maxStringContextAux = maxStringContextDesfasadoEn1;
					stringContext = maxStringContextAux.substr(maxStringContextDesfasadoEn1.length()-i,i);
					updateFrequencyTables(stringContext, ESC_CHAR);//creo la tabla del contexto con esc(1)
					cout << "CREATE (o update): " << stringContext<<endl;
				}

				//-------actualizo stringContext para entrar al ciclo de nuevo
				if (previousStringContext == ZERO_CONTEXT){
					stringContext =  character;
				}
				else{//aca me llega con actualContextNumber==maxContext
					if(maxStringContextDesfasadoEn1.length()!=maxContext){
						maxStringContextAux = maxStringContextDesfasadoEn1; //todo actualContextNumber ??
						stringContext =  maxStringContextAux.substr(0,maxStringContextDesfasadoEn1.length());
						cout << "nunca paso por aca todavia"<<endl;
					}else{
						maxStringContextAux = maxStringContextDesfasadoEn1;
						stringContext =  maxStringContextAux.substr(maxStringContextDesfasadoEn1.length()-maxStringContext.length(),maxStringContextDesfasadoEn1.length());
					}
				}
				previousStringContext = stringContext;
		}
		else {	// Aritmetico emitio ESC -> me muevo a un contexto inferior e incremento el contador cantidadContextosAActualizar
			if (stringContext==ZERO_CONTEXT){
				previousStringContext = stringContext;
				stringContext = MINUS_ONE_CONTEXT;
			}else if (stringContext==MINUS_ONE_CONTEXT){
				cout<< "hubo un error de actualContextNumber. quedo menor a -1 en ppmc descompresor";
			}else if (stringContext.length()==1){
				previousStringContext = stringContext;
				stringContext=ZERO_CONTEXT;
			}else{
				previousStringContext = stringContext;
				stringContext = stringContext.substr(1,stringContext.length()-1);
			}
		}

			//ya actualice las tablas necesarias si hacian falta. Ahora obtengo tabla de frecs para pasarle al descompresor aritmetico
			if (this->existsElementInStructure(stringContext)) { // si Existe el contexto obtengo la tabla
				frequencyTable = this->getFrequencyTable(stringContext, true);
			}
			else if (stringContext == MINUS_ONE_CONTEXT){
				frequencyTable = this->minusOneCtxtFreqTable;
			}

			string borrar = frequencyTable->toString();
			cout << "Tabla p el aritmetico (ctx '"<<stringContext<<"' / CantElemSinESC "<<frequencyTable->getCharCount()<<") : "<<borrar << endl;
		//	shortCharacter = arithmeticCompressor->decompress(*frequencyTable);
			shortCharacter = borrarEsteMetodo(borrarContador);

			if (shortCharacter != ESC_CHAR) {
				characterAnterior = character;
				character = (char) shortCharacter;
				cout<<"aritmetico emitio : "<< character<<endl;
			}
			else cout<<"aritmetico emitio : ESC "<<endl;

			if (shortCharacter == EOF_CHAR){
				isNotEOF = false;
			}
			if (stringContext!= MINUS_ONE_CONTEXT)
				delete frequencyTable;		//libero memoria

	}//fin While(continuarCiclo)

	sequentialFile->close();
	std::cout << "Fin de descompresion" << std::endl;

	log = ";Se termino de descomprimir el archivo: ";
	log.append(path);
	this->logger->insert(&log[0]);

	return true;
}

void Ppmc::updateFrequencyTables(std::string stringContext, short character) {

	FrequencyTable* frequencyTable;

	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		StringInputData stringInputData;
		this->findInStructure(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado,
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			unsigned long cantCaract = frequencyTable->getCharCount();

			string borrar = frequencyTable->toString();
						cout << borrar << endl;

			frequencyTable->setFrequency(ESC_CHAR,cantCaract); //actualizo la frecuencia del ESC si es necesario
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			borrar = frequencyTable->toString();
			cout << "ctx "<< stringContext<<" : " <<borrar << endl;
		} else { // Si ya existe el caracter en el contexto dado, se incrementa su frecuencia.
			//this->countHit(stringContext);		//TODO MAti - countHit!
			if (character!=ESC_CHAR)
				frequencyTable->increaseFrequency(character,1);
			unsigned long cantCaract = frequencyTable->getCharCount();
			frequencyTable->setFrequency(ESC_CHAR,cantCaract);  //actualizo la frecuencia del ESC si es necesario
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			string borrar = frequencyTable->toString();
			cout << "ctx "<< stringContext<<" : " <<borrar << endl;
			delete frequencyTable;
			return;
		}
		delete frequencyTable;
	} else { // No existe el contexto pasado por parametro. Por lo tanto se lo crea con ESC(1)
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
		if (character!= ESC_CHAR)
			cout<<"se esperaba q este metodo se use solo como parametro de entrada a ESC"<<endl;    //todo borrar desp de que ande todo
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->insertInStructure(stringContext,frequencyTable->toString());
		string borrar = frequencyTable->toString();
		cout << "ctx "<< stringContext<<" : " <<borrar << endl;
		delete frequencyTable;
	}
}
void Ppmc::getMaxStringContext(std::string &maxStringContext,char characterAnterior,unsigned int maxContext,bool primeraVez){
	if (primeraVez)	//no hay contexto anterior la primera vez
		maxStringContext = "";
	else{
		maxStringContext  = maxStringContext.append(1,characterAnterior);
		if (maxStringContext.length()>maxContext)
			maxStringContext = maxStringContext.substr(0,maxContext);
	}
}

void Ppmc::getMaxStringContextDesfasado(std::string &maxStringContextDesfasado,char character,unsigned int maxContext,bool primeraVez){
	if (primeraVez)	//tengo al character la primera vez
		maxStringContextDesfasado = character;
	else{
		maxStringContextDesfasado  = maxStringContextDesfasado.append(1,character);
		if (maxStringContextDesfasado.length()>maxContext)
			maxStringContextDesfasado = maxStringContextDesfasado.substr(maxStringContextDesfasado.length()-maxContext,maxContext);
	}
}


void Ppmc::getStatistics(int row) {
	for (int i=0;i<row;i++){
	printf("Cantidad de aciertos en contexto de orden %d : %d \n",i,this->contextStats[i]);

	}

}

int Ppmc::setContextStats(int maxContexts){
	if( (this->contextStats = (int*) malloc(sizeof(int)*(maxContexts+1)) ) == NULL)
	return -1;
	// Construye un vector dinamico de maxContexts enteros y se inicializan a 0.
	for(int i=0;i<(maxContexts+1);i++)
	contextStats[i] = 0;
	//TODO Recordar liberar memoria cuando se dejen de necesitar las estadisticas.
	return 0;
};

void Ppmc::countHit(std::string successfulContext) {
	int contextNumber=successfulContext.size();
	this->contextStats[contextNumber]++;



}

bool Ppmc::printContext(string key)
{
	bool retVal;

	StringInputData stringInputData;

	FrequencyTable ft;

	retVal = generalStructure->find(key, stringInputData);

	if(retVal)
	{
		ft.deserialize(stringInputData.getValue());
		cout <<"Contexto: " <<stringInputData.getKey()<< " "<< ft.toPrintableString()<<endl;
	}

	return retVal;
}


int Ppmc::getFileSize(char* filename){
	FILE* archivo;
	int size;
	archivo = fopen (filename, "rb");
	fseek(archivo, 0, SEEK_END); // Se posiciona al final del archivo
	size = ftell(archivo); // Devuelve la posición actual del archivo (en bytes)
	fclose(archivo);

	return size;


}

void Ppmc::ppmcDeCompressionEmitter(ArithmeticCompressor* decompressor, char& character, std::string stringContext, int actualContextNumber, int maxContext, bool newRead) {
	FrequencyTable* frequencyTable;
	if (this->existsElementInStructure(stringContext)) {
		newRead = false;
		frequencyTable = this->getFrequencyTable(stringContext, newRead);
		character = decompressor->decompress(*(frequencyTable));
		if ((short)character == ESC_CHAR) {
		} else {
			return;
		}
	} else { // No existe el contexto pasado por parametro. Por lo tanto lo crea.
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
		this->insertInStructure(stringContext,frequencyTable->toString());
		newRead = false;
	}

	if ((actualContextNumber-1) > 0) {
		newRead=false;
		this->ppmcDeCompressionEmitter(decompressor, character, stringContext.substr(1,stringContext.length()), actualContextNumber-1, maxContext, newRead); // Bajo de contexto progresivamente.
	} else if ((actualContextNumber-1) == 0) {
		stringContext = ZERO_CONTEXT;
		newRead=true;
		this->ppmcDeCompressionEmitter(decompressor, character, stringContext, actualContextNumber-1, maxContext, newRead); // Bajo al contexto 0 que es el anteúltimo.
	} else { // Llegamos al contexto -1.
		character = decompressor->decompress(*(minusOneCtxtFreqTable));
		std::cout << "Recupero el caracter " << character <<  " en el contexto -1." << std::endl;
	}

	if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado, se lo agrega.
		std::cout << "Agrego caracter " << character << " al contexto " << stringContext << std::endl;
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->modifyInStructure(stringContext, frequencyTable->toString());
	} else { // Si ya existe el caracter en el contexto dado, se incrementa su frecuencia.
		frequencyTable->increaseFrequency(character,1);
		this->modifyInStructure(stringContext, frequencyTable->toString());
	}
}

bool Ppmc::deCompress2(const std::string path) {
	int maxContext = 0;
	std::string outPath = "";

	size_t position = path.find(".ppmc");
	if (position != string::npos) {
		outPath = path.substr(0, position);
		maxContext = atoi(path.substr(position+5, path.length()-position-5).c_str());
	} else {
		return false; // El archivo no posee la extension ".ppmc".
	}

	std::cout << "Descomprimiendo archivo... (" << path << ")" << std::endl;

	outPath = outPath.substr(0, outPath.find(".txt"));
	outPath.append("Descomprimido.txt");

	ArithmeticCompressor* decompressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR, path, 24);
	bool newRead=true;
	char character = NULL;
	SequentialFile* sequentialFile = new SequentialFile(WRITE_FILE);
	sequentialFile->open(outPath);
	int actualContextNumber = 0; // Representa el número de contexto más alto que se alcanzó hasta ahora.
	std::string stringContext = "0";

	this->ppmcDeCompressionEmitter(decompressor, character, stringContext, actualContextNumber, maxContext, newRead);

	actualContextNumber = 1;
	stringContext = character;

	while (character != EOF_CHAR) {
		this->ppmcDeCompressionEmitter(decompressor, character, stringContext, actualContextNumber, maxContext, newRead);
		if (actualContextNumber < maxContext) {
			actualContextNumber++;
			stringContext.append(1,character);
		} else {
			stringContext.append(1,character);
			stringContext = stringContext.substr(1, stringContext.length());
		}
		sequentialFile->writeChar(character);
	}
	sequentialFile->close();
	delete decompressor;
	std::cout << "Fin de compresion" << std::endl;
	return true;
};
