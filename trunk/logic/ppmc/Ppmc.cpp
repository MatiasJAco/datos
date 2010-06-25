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

	for (int i = 1; i <= 257; i++) {
		this->minusOneCtxtFreqTable->setFrequency(i,1); // Llena con 1 ocurrencia los 256 caracteres ASCII y el EOF.
	}
}

Ppmc::~Ppmc() {
}



//-----------------------------------------------------------------------------------------------
//-----------------------------------COMPRESION -------------------------------------------------
//-----------------------------------------------------------------------------------------------
bool Ppmc::compress(std::string path,int maxContext) {
	std::cout << "Comprimiendo archivo... (" << path << ")" << std::endl;
	SequentialFile* sequentialFile = new SequentialFile(READ_FILE);
	sequentialFile->open(path);
	//TODO que pasa si el archivo esta vacio?? hay que validarlo
	char character = sequentialFile->readChar();
	//TODO no seria strinContext = "_" o  " " (vacio) ?? (para indicar el ctx cero)
	std::string stringContext = ZERO_CONTEXT;
	int actualContextNumber = 0; // Representa el número de contexto más alto que se alcanzó hasta ahora.

	this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext);
	actualContextNumber++;
	stringContext = character;
	bool isNotEof = false;

	character = sequentialFile->readChar(isNotEof);

	while (isNotEof) {
		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext);
		if (actualContextNumber < maxContext) {
			actualContextNumber++;
			stringContext.append(1,character);
		} else {
			stringContext.append(1,character);
			stringContext.substr(1,stringContext.length());
		}
		character = sequentialFile->readChar(isNotEof);
	}
	sequentialFile->close();
	std::cout << "Fin de compresion" << std::endl;
	return true;
}

void Ppmc::ppmcCompressionEmitter(std::string stringContext, char character, int actualContextNumber, int maxContext) {
	FrequencyTable* frequencyTable;
	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		StringInputData stringInputData;
		this->findInStructure(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado, se emite un escape y se agrega el caracter faltante.
			std::cout << "Emito el caracter " << "Escape" << " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
			frequencyTable->increaseFrequency(ESC_CHAR,1);//incremento frecuencia al escape
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
		} else { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto ACÁ.
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
		int difference = stringContext.size()-maxContext;
		if (difference > 0)
			stringContext = stringContext.substr(stringContext.size()-maxContext,maxContext);
		std::cout << "Emito el caracter " << "Escape" <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->insertInStructure(stringContext,frequencyTable->toString());
		delete frequencyTable;
	}
	stringContext = stringContext.substr(1,stringContext.length());
	actualContextNumber--;
	if (actualContextNumber > 0) {
		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo de contexto progresivamente.
	} else if (actualContextNumber == 0) {
		stringContext = ZERO_CONTEXT;
		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo al contexto 0 que es el último.
	} else { // Llegamos al contexto -1.
		std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << this->minusOneCtxtFreqTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto -1 ACÁ.
		//TODO adrian esto habia que sacarlo no?
		this->minusOneCtxtFreqTable->increaseFrequency(character,1);
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
	//TODO esta hardcodeado esto para probar hasta que ande el decompress de aritmetico
	short shortCharacter = 68; // 68 = "D"
	char character;
	if (shortCharacter != EOF_CHAR)
		character = (char) shortCharacter;
	else {
		cout<<"El compresor aritmetico devolvio EOF al ppio de todo en el decompresor";
		return false; //TODO false o true?
	}

	std::string stringContext = MINUS_ONE_CONTEXT;
	int actualContextNumber = -1; // Representa el número de contexto -1 (de donde arranca la descompresion)

	//TODO IMPORTANTE! ver como obtener este valor!
	int maxContext = 3;


	//escribo en el archivo de salida el caracter.
	//sequentialFile->writeChar(character);

	this->updateFrequencyTables(stringContext, character, actualContextNumber, maxContext);





//-------falta ver este pedazo----------------
	actualContextNumber--;
	stringContext = character;
	bool isNotEof = false;
	character = sequentialFile->readChar(isNotEof);

	while (isNotEof) {
		this->updateFrequencyTables(stringContext, character, actualContextNumber, maxContext);
		if (actualContextNumber < maxContext) {
			actualContextNumber++;
			stringContext.append(1,character);
		} else {
			stringContext.append(1,character);
			stringContext.substr(1,stringContext.length());
		}
		character = sequentialFile->readChar();
	}
//--------------------------------------------------




	sequentialFile->close();
	std::cout << "Fin de descompresion" << std::endl;
	return true;
}
void Ppmc::updateFrequencyTables(std::string stringContext, char character, int actualContextNumber, int maxContext) {











	FrequencyTable* frequencyTable;

	if (strcmp(stringContext.c_str(),MINUS_ONE_CONTEXT.c_str()) == 0){ //Estoy en contexto -1
			//ver si este if  sirve realmente

	}


	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		StringInputData stringInputData;
		this->findInStructure(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado, se emite un escape y se agrega el caracter faltante.
			std::cout << "Emito el caracter " << "Escape" << " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
			frequencyTable->increaseFrequency(ESC_CHAR,1);//incremento frecuencia al escape
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
		} else { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto ACÁ.
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
		int difference = stringContext.size()-maxContext;
		if (difference > 0)
			stringContext = stringContext.substr(stringContext.size()-maxContext,maxContext);
		std::cout << "Emito el caracter " << "Escape" <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->insertInStructure(stringContext,frequencyTable->toString());
		delete frequencyTable;
	}
	stringContext = stringContext.substr(1,stringContext.length());
	actualContextNumber--;
	if (actualContextNumber > 0) {
		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo de contexto progresivamente.
	} else if (actualContextNumber == 0) {
		stringContext = ZERO_CONTEXT;
		this->ppmcCompressionEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo al contexto 0 que es el último.
	} else { // Llegamos al contexto -1.
		std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << this->minusOneCtxtFreqTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto -1 ACÁ.
		//TODO adrian esto habia que sacarlo no?
		this->minusOneCtxtFreqTable->increaseFrequency(character,1);
	}
}
























void Ppmc::getStatistics() {
}

