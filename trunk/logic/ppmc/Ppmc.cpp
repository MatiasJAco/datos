/*
 * Ppmc.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */
#include "Ppmc.h"
#include "../../physical/file/SequentialFile.h"

const string Ppmc::ZERO_CONTEXT = "0";
const string Ppmc::MINUS_ONE_CONTEXT = "-1";

Ppmc::Ppmc(GeneralStructure* generalStructure){
	this->generalStructure = generalStructure;
	this->minusOneCtxtFreqTable = new FrequencyTable();
	for (int i = 0; i <= 256; i++) {
		this->minusOneCtxtFreqTable->setFrequency(i,1); // Llena con 1 ocurrencia los 256 caracteres ASCII y el EOF.
	}
	this->contextStats=NULL;
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

bool Ppmc::compress(std::string path,int maxContext) {
	ArithmeticCompressor* compressor = new ArithmeticCompressor(ArithmeticCompressor::COMPRESSOR, "comprimido.gzip", 256);
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
	actualContextNumber++;
	stringContext = character;
	bool isNotEof = false;

	character = sequentialFile->readChar(isNotEof);

	while (isNotEof) {
		this->ppmcCompressionEmitter(compressor, stringContext, character, actualContextNumber, maxContext, newRead, previousFrequencyTable);
		if (actualContextNumber < maxContext) {
			actualContextNumber++;
			stringContext.append(1,character);
		} else {
			stringContext.append(1,character);
			stringContext = stringContext.substr(1,maxContext);
		}
		character = sequentialFile->readChar(isNotEof);
	}
	sequentialFile->close();
	delete compressor;
	std::cout << "Fin de compresion" << std::endl;
	return true;
}

void Ppmc::ppmcCompressionEmitter(ArithmeticCompressor* compressor, std::string stringContext, char character, int actualContextNumber, int maxContext, bool newRead, FrequencyTable* previousFrequencyTable) {
	FrequencyTable* frequencyTable;
	FrequencyTable* excludedFrequencyTable;
	FrequencyTable* nextExclusionTable = previousFrequencyTable;

	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		frequencyTable = this->getFrequencyTable(stringContext, newRead);

		//std::cout << std::endl << "Tabla exclusion  :" << previousFrequencyTable->toString() << std::endl;
		//std::cout << "Tabla sin excluir: " << frequencyTable->toString() << std::endl;
		nextExclusionTable = new FrequencyTable(*frequencyTable);
		excludedFrequencyTable = new FrequencyTable(frequencyTable->excludeFromTable(*previousFrequencyTable)); // Se excluyen los caracteres que estaban en el contexto anterior.
		//std::cout << "Tabla excluida   : " << frequencyTable->toString() << std::endl << std::endl;

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado, se emite un escape y se agrega el caracter faltante.
			if ((excludedFrequencyTable->getFrequency(ESC_CHAR) == 1) && (excludedFrequencyTable->getFrequencyTotal() == 1)) {
				std::cout << "Emitiria el caracter Escape en el contexto " << stringContext << " con " << excludedFrequencyTable->getFrequency(ESC_CHAR) << "/" << excludedFrequencyTable->getFrequencyTotal() << std::endl;
			} else {
				compressor->compress(ESC_CHAR, (*excludedFrequencyTable));
				std::cout << "Emito el caracter Escape en el contexto " << stringContext << " con " << excludedFrequencyTable->getFrequency(ESC_CHAR) << "/" << excludedFrequencyTable->getFrequencyTotal() << std::endl;
			}
			frequencyTable->increaseFrequency(ESC_CHAR,1);//incremento frecuencia al escape
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
		} else { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			compressor->compress(character, (*excludedFrequencyTable));
			std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << excludedFrequencyTable->getFrequency(character) << "/" << excludedFrequencyTable->getFrequencyTotal() << std::endl;
			this->countHit(stringContext);
			frequencyTable->increaseFrequency(character,1);
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			return;
		}
	} else { // No existe el contexto pasado por parametro. Por lo tanto se lo crea.
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
		//compressor->compress(ESC_CHAR, (*frequencyTable));
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
	}
}



//-----------------------------------------------------------------------------------------------
//-----------------------------------DESCOMPRESION ----------------------------------------------
//-----------------------------------------------------------------------------------------------
bool Ppmc::deCompress(const std::string & path) {
	std::cout << "Descomprimiendo archivo... (" << path << ")" << std::endl;
	SequentialFile* sequentialFile = new SequentialFile(WRITE_FILE);
	sequentialFile->open(path);

	//instancio el compresor aritmetico como Decompresor.
	//ArithmeticCompressor* arithmeticCompressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR,path,8);

	//mando la tabla de frecuencias del contexto -1 para que me retorne el primer caracter
	//short shortCharacter = arithmeticCompressor->decompress(*this->minusOneCtxtFreqTable);


	short shortCharacter = 68; // 68 = "D"           //TODO esta hardcodeado esto para probar hasta que ande el decompress de aritmetico

	if (shortCharacter == EOF_CHAR){
		cout<<"El compresor aritmetico devolvio EOF al ppio de todo en el decompresor";
		return false; //TODO false o true?
	}

	std::string stringContext;
	int actualContextNumber = -1; // Representa el número de contexto -1 (de donde arranca la descompresion)
	int maxContext = 3;  //TODO IMPORTANTE! ver como obtener este valor!
	char character;
	FrequencyTable * frequencyTable;
	short cantidadContextosAActualizar;

	while(shortCharacter!= EOF_CHAR){

		cantidadContextosAActualizar = 1;

			if (actualContextNumber == -1)
				stringContext = MINUS_ONE_CONTEXT;
			else if (actualContextNumber == 0)
				stringContext = ZERO_CONTEXT;

		this->ppmcDecompressionEmitter(stringContext, shortCharacter, actualContextNumber, maxContext); //TODO ver si se usan todos los params

		//escribo en el archivo de salida el caracter.
		character = (char) shortCharacter;
		//sequentialFile->writeChar(character);
		cout<<"EMITO : '" << character << "'" << endl;	//TODO aca hay que mandar al archivo de descompresion

		shortCharacter = ESC_CHAR;
		while (shortCharacter == ESC_CHAR){
			StringInputData stringInputData;
			this->findInStructure(stringContext,stringInputData);
			frequencyTable = new FrequencyTable();
			frequencyTable->deserialize(stringInputData.getValue());
			//shortCharacter = arithmeticCompressor->decompress(frequencyTable);
					string borrar = frequencyTable->toString();
					cout << borrar << endl;
			shortCharacter = ESC_CHAR;           //TODO esta hardcodeado esto para probar hasta que ande el decompress de aritmetico
			delete frequencyTable;
			actualContextNumber--;
				if (actualContextNumber == -1)
					stringContext = MINUS_ONE_CONTEXT;
				else if (actualContextNumber == 0)
					stringContext = ZERO_CONTEXT;
			cantidadContextosAActualizar ++;
		}
		//sale del while con el ctxt donde el aritmetico emitio un caracter distinto a ESC. En character esta el caracter distinto a ESC.
		for (short i = cantidadContextosAActualizar; i>0 ; i--){

			if (actualContextNumber == -1){ //voy al contexto siguiente si estoy en el -1
				actualContextNumber++;
				stringContext = ZERO_CONTEXT;
			}

			updateFrequencyTables(stringContext,shortCharacter,actualContextNumber,maxContext);
			actualContextNumber++;
			//TODO ver aca como hago para obtener el listado de contextos q se tienen que actualizar (listado de stringContexts)

		}

	}
//-------falta ver este pedazo----------------
//	actualContextNumber--;
//	stringContext = character;
//	bool isNotEof = false;
//	character = sequentialFile->readChar(isNotEof);
//
//	while (isNotEof) {
//		this->updateFrequencyTables(stringContext, character, actualContextNumber, maxContext);
//		if (actualContextNumber < maxContext) {
//			actualContextNumber++;
//			stringContext.append(1,character);
//		} else {
//			stringContext.append(1,character);
//			stringContext.substr(1,stringContext.length());
//		}
//		character = sequentialFile->readChar();
//	}
//--------------------------------------------------




	sequentialFile->close();
	std::cout << "Fin de descompresion" << std::endl;
	return true;
}
void Ppmc::ppmcDecompressionEmitter(std::string &stringContext, short shortCharacter, int &actualContextNumber, int maxContext) {

	char character;

	if (shortCharacter != ESC_CHAR){   // Aritmetico no emitio ESC -> me muevo a un contexto superior
		character = (char) shortCharacter;
		actualContextNumber++;
		if (actualContextNumber == 0)
			stringContext = ZERO_CONTEXT;

		updateFrequencyTables(stringContext, character, actualContextNumber, maxContext);

	}
	else {	// Aritmetico emitio ESC -> me muevo a un contexto inferior

	}

}


void Ppmc::updateFrequencyTables(std::string stringContext, short character, int actualContextNumber, int maxContext) {

	FrequencyTable* frequencyTable;

	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		StringInputData stringInputData;
		this->findInStructure(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado, se emite un escape y se agrega el caracter faltante.
			//std::cout << "Emito el caracter " << "Escape" << " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
			frequencyTable->increaseFrequency(ESC_CHAR,1);//incremento frecuencia al escape
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
		} else { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			//std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto ACÁ.
			this->countHit(stringContext);
			frequencyTable->increaseFrequency(character,1);
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			delete frequencyTable;
			return;
		}
		delete frequencyTable;
	} else { // No existe el contexto pasado por parametro. Por lo tanto se lo crea.
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
//		int difference = stringContext.size()-maxContext;
//		if (difference > 0)
//			stringContext = stringContext.substr(stringContext.size()-maxContext,maxContext);
//		std::cout << "Emito el caracter " << "Escape" <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->insertInStructure(stringContext,frequencyTable->toString());
		string borrar = frequencyTable->toString();
		cout << borrar << endl;
		delete frequencyTable;
	}
//	stringContext = stringContext.substr(1,stringContext.length());
//	actualContextNumber--;
//	if (actualContextNumber > 0) {
//		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo de contexto progresivamente.
//	} else if (actualContextNumber == 0) {
//		stringContext = ZERO_CONTEXT;
//		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo al contexto 0 que es el último.
//	} else { // Llegamos al contexto -1.
//		std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << this->minusOneCtxtFreqTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto -1 ACÁ.
//		//TODO adrian esto habia que sacarlo no?
//		this->minusOneCtxtFreqTable->increaseFrequency(character,1);
//	}
}



void Ppmc::getStatistics() {

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
