/*
 * Ppmc.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */
#include "Ppmc.h"
#include "../../physical/file/SequentialFile.h"

Ppmc::Ppmc(GeneralStructure* generalStructure){
	this->generalStructure = generalStructure;
	this->minusOneContext = new FrequencyTable();

	for (int i = 1; i <= 257; i++) {
		this->minusOneContext->setFrequency(i,1); // Llena con 1 ocurrencia los 256 caracteres ASCII y el EOF.
	}
}

Ppmc::~Ppmc() {
}

bool Ppmc::compress(std::string path,int maxContext) {
	std::cout << "Comprimiendo archivo... (" << path << ")" << std::endl;
	SequentialFile* sequentialFile = new SequentialFile(READ_FILE);
	sequentialFile->open(path);
	char character = sequentialFile->readChar();
	std::string stringContext = "0";
	int actualContextNumber = 0; // Representa el número de contexto más alto que se alcanzó hasta ahora.

	this->ppmcEmitter(stringContext, character, actualContextNumber, maxContext);
	int contador = 1;    // Seria el limite para no tener EOF.
	actualContextNumber++;
	stringContext = character;
	character = sequentialFile->readChar();

	while (contador < 4) { // TODO Adrián: reemplazar por EOF cuando esté implementado en SequentialFile.
		this->ppmcEmitter(stringContext, character, actualContextNumber, maxContext);
		if (actualContextNumber < maxContext) {
			actualContextNumber++;
			stringContext.append(1,character);
		} else {
			stringContext.append(1,character);
			stringContext.substr(1,stringContext.length());
		}
		contador++;
		character = sequentialFile->readChar();
	}
	sequentialFile->close();
	std::cout << "Fin de compresion" << std::endl;
	return true;
}

bool Ppmc::deCompress(const std::string & path) {
	return false;
}

void Ppmc::getStatistics() {
}

void Ppmc::ppmcEmitter(std::string stringContext, char character, int actualContextNumber, int maxContext) {
	FrequencyTable* frequencyTable;
	if (this->generalStructure->existsElement(stringContext)) { // Existe el contexto pasado por parametro.
		StringInputData stringInputData;
		this->generalStructure->find(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());

		if (frequencyTable->getFrequency(character) == 0) { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			std::cout << "Emito el caracter " << "Escape" << " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		} else { // Si no existe el caracter en el contexto dado, se emite un escape y se agrega el caracter faltante.
			std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto ACÁ.
			frequencyTable->increaseFrequency(character,1);
			return;
		}

		std::string stringFrequencyTable = frequencyTable->toString();
		this->generalStructure->modify(stringContext,stringFrequencyTable);
		delete frequencyTable;
	} else { // No existe el contexto pasado por parametro. Por lo tanto se lo crea.
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
		std::cout << "Emito el caracter " << "Escape" <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
		this->generalStructure->insert(stringContext,frequencyTable->toString());
		delete frequencyTable;
	}
	stringContext = stringContext.substr(1,stringContext.length());
	actualContextNumber--;
	if (actualContextNumber > 0) {
		this->ppmcEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo de contexto progresivamente.
	} else if (actualContextNumber == 0) {
		stringContext = "0";
		this->ppmcEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo al contexto 0 que es el último.
	} else { // Llegamos al contexto -1.
		std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << this->minusOneContext->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto -1 ACÁ.
		this->minusOneContext->increaseFrequency(character,1);
	}
}
