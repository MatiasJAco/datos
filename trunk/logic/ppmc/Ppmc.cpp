/*
 * Ppmc.cpp
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */
#include "Ppmc.h"
#include "../../physical/file/SequentialFile.h"
#include "../../application/compresion/common/FrequencyTable.h"

Ppmc::Ppmc(GeneralStructure* generalStructure){
	this->generalStructure = generalStructure;
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
		//TODO emitir la probabilidad del caracter aca
		StringInputData stringInputData;
		this->generalStructure->find(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());
		frequencyTable->increaseFrequency(character,1);
		std::string stringFrequencyTable = frequencyTable->toString();
		this->generalStructure->modify(stringContext,stringFrequencyTable);
		delete frequencyTable;
	} else {
		frequencyTable = new FrequencyTable();
		frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto cero, con una ocurrencia.
		std::string stringFrequencyTable = frequencyTable->toString();
		this->generalStructure->insert(stringContext,stringFrequencyTable);
		delete frequencyTable;
		stringContext = stringContext.substr(1,stringContext.length());
		actualContextNumber--;
		if (actualContextNumber > 0) {
			this->ppmcEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo de contexto progresivamente.
		} else if (actualContextNumber == 0) {
			stringContext = "0";
			this->ppmcEmitter(stringContext, character, actualContextNumber, maxContext); // Bajo al contexto 0 que es el último.
		} else { // Llegamos al contexto -1.
			// emitir la probabilidad del caracter en el contexto -1.
		}
	}
}
