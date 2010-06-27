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

bool Ppmc::deCompress(const std::string & path) {
	std::string outPath = "";
	int maxContext = 0;
	size_t position = path.find(".ppmc");
	if (position != string::npos) {
		outPath = path.substr(0, position);
		maxContext = atoi(path.substr(position+5, path.length()-position-5).c_str());
	} else {
		return false; // El archivo no posee la extension ".ppmc".
	}

	std::cout << "Descomprimiendo archivo... (" << path << ")" << std::endl;
	SequentialFile* sequentialFile = new SequentialFile(WRITE_FILE);
	sequentialFile->open(outPath);

	//instancio el compresor aritmetico como Decompresor.
	ArithmeticCompressor* arithmeticCompressor = new ArithmeticCompressor(ArithmeticCompressor::DECOMPRESSOR, path, 256);

	std::string stringContext;
	std::string previousStringContext="";
	std::string maxStringContext = "";
	std::string maxStringContextDesfasadoEn1 = "";
	int actualContextNumber = -1; // Representa el número de contexto -1 (de donde arranca la descompresion)
	char character;
	char characterAnterior;
	short shortCharacter;
	FrequencyTable * frequencyTable;
	bool primeraVez = true;
	bool continuarCiclo = true;

	//primer llamado para inicializar al ctxt 0
	createFrequencyTable(ZERO_CONTEXT,0);

	int borrarContador = 0; //todo hacerle caso al nombre de la variable :D
	while(continuarCiclo){
				borrarContador++;
				if (actualContextNumber ==-1){
					frequencyTable = this->minusOneCtxtFreqTable;
					stringContext = MINUS_ONE_CONTEXT;
				}
				else if (actualContextNumber == 0)
					stringContext = ZERO_CONTEXT;
		cout<<"mando a aritmetico : stringContext : '"<<stringContext<<"', actualContextNum: "<<actualContextNumber<<endl;
		//shortCharacter = arithmeticCompressor->decompress(frequencyTable);
		shortCharacter = borrarEsteMetodo(borrarContador);      //TODO esta hardcodeado esto para probar hasta que ande el decompress de aritmetico
		cout<<"aritmetico emitio : "<< (char) shortCharacter<<endl;
		if (borrarContador == 13){		cout<< "cagamos: 13"<<endl; return false;}
								if (primeraVez && (shortCharacter == EOF_CHAR)){
									cout<<"El compresor aritmetico devolvio EOF al ppio de todo en el decompresor";
									return false; //TODO false o true?
								}
								else if (shortCharacter == EOF_CHAR){
									continuarCiclo = false;
								}
								if (actualContextNumber != -1)	//libero memoria
									delete frequencyTable;

		if (continuarCiclo){
			//si el caracter no es ESC ni EOF, lo emito,armo el maxStringContext y actualizo las tablas de frec q necesito, y creo las nuevas
			if (shortCharacter != ESC_CHAR){   // Aritmetico no emitio ESC -> me muevo a un contexto superior
//					actualContextNumber++;
//					if (actualContextNumber == 0)
//						stringContext = ZERO_CONTEXT;
//					else{
//						//todo IMPLEMENTAR - caso en que salgo antes de llegar al ctxt -1
//					}
				actualContextNumber=0;
				stringContext = ZERO_CONTEXT;


					//escribo en el archivo de salida el caracter.
					character = (char) shortCharacter;
					//sequentialFile->writeChar(character);
					cout<<"EMITO : '" << character << "'" << endl;	//TODO aca hay que mandar al archivo de descompresion

					getMaxStringContext(maxStringContext,characterAnterior,maxContext,primeraVez);
					cout << "maxStringContext: " << maxStringContext<<", ";
					getMaxStringContextDesfasado(maxStringContextDesfasadoEn1,character,maxContext,primeraVez);
					cout << "maxStringContextDesfasadoEn1: " << maxStringContextDesfasadoEn1<<", ";
					cout << "previousStringContext: " << previousStringContext<<endl;


					//-----------actualizo todas las tablas de frecuencias que necesite--------------
					//actualizo la del contexto 0
						updateFrequencyTables(stringContext,shortCharacter,actualContextNumber,maxContext);
						cout << "UPDATE: ctx " << stringContext<<","<<actualContextNumber<<","<<(char) shortCharacter<<endl;

						std::string maxStringContextAux;

						if(!primeraVez){
							if (previousStringContext.length()!=maxContext){
								for (unsigned int i = 1; i<=maxStringContext.length();i++){
									maxStringContextAux = maxStringContext;
									actualContextNumber++;
									stringContext = maxStringContextAux.substr(maxStringContext.length()-i,i);
									updateFrequencyTables(stringContext,shortCharacter,actualContextNumber,maxContext);
									cout << "UPDATE: ctx " << stringContext<<","<<actualContextNumber<<","<<(char) shortCharacter<<endl;
								}
							}
							else {   //previousContext tiene mismo tam que maxContext
								for (unsigned int i = 1; i<=previousStringContext.length();i++){
									maxStringContextAux = previousStringContext;
									actualContextNumber++;
									stringContext = maxStringContextAux.substr(previousStringContext.length()-i,i);
									updateFrequencyTables(stringContext,shortCharacter,actualContextNumber,maxContext);
									cout << "UPDATE: ctx " << stringContext<<","<<actualContextNumber<<","<<(char) shortCharacter<<endl;
								}
							}
						}


						// -------creo todas las tablas de frecuencias nuevas--
						std::string stringContextAux;
						if (primeraVez){	//actualizo contexto 1
							stringContextAux = character;
							createFrequencyTable(stringContextAux,1); //borrar createFrecTable
							cout << "CREATE: " << stringContextAux<<","<<1<<endl;
						}
						else{
							actualContextNumber=1;
							for (unsigned int i = 1; i<=maxStringContextDesfasadoEn1.length();i++){
								maxStringContextAux = maxStringContextDesfasadoEn1;
								stringContext = maxStringContextAux.substr(maxStringContextDesfasadoEn1.length()-i,i);
								updateFrequencyTables(stringContext,ESC_CHAR,actualContextNumber,maxContext); //todo borrar createFrecTable y en realidad no hay que llamar a esta funcion
								cout << "CREATE: " << stringContext<<","<<actualContextNumber<<endl;//todo creo que es crear si no esta creado, nada mas.
								if (i!=maxStringContextDesfasadoEn1.length())
									actualContextNumber++;
							}
						}

					//actualizo stringContext para entrar al ciclo de nuevo
					if (!primeraVez){
						if (previousStringContext == ZERO_CONTEXT){
							actualContextNumber = 1;
							stringContext =  character;
						}
						else{//aca me llega con actualContextNumber==maxContext
							if(maxStringContextDesfasadoEn1.length()!=maxContext){
								maxStringContextAux = maxStringContextDesfasadoEn1;
								stringContext =  maxStringContextAux.substr(0,maxStringContextDesfasadoEn1.length());
							}else{
								maxStringContextAux = maxStringContextDesfasadoEn1;
								stringContext =  maxStringContextAux.substr(maxStringContextDesfasadoEn1.length()-maxStringContext.length(),maxStringContextDesfasadoEn1.length());
								actualContextNumber = stringContext.length();
							}
						}
					}
					previousStringContext = stringContext;
			}
			else {	// Aritmetico emitio ESC -> me muevo a un contexto inferior e incremento el contador cantidadContextosAActualizar
				actualContextNumber--;
							if (actualContextNumber == -1)
								stringContext = MINUS_ONE_CONTEXT;
							else if (actualContextNumber == 0)
								stringContext = ZERO_CONTEXT;
							else {
								stringContext = stringContext.substr(1,stringContext.length()-1);
							}

							if (actualContextNumber<-1) //TODO solo para debug
								cout<< "hubo un error de actualContextNumber. quedo menor a -1 en ppmc descompresor";

				}

			primeraVez = false;
			characterAnterior = character;

			//ya actualice las tablas necesarias si hacian falta. Ahora obtengo tabla de frecs para volver al ciclo
			if (this->existsElementInStructure(stringContext)) { // si Existe el contexto obtengo la tabla
				frequencyTable = this->getFrequencyTable(stringContext, true);
			}
			else {	//no existe el ctxt
				if (actualContextNumber > -1){
					cout<<"paso por aca! sino se pasa por aca, hay qe borrar este else"<<endl;//todo ver si pasa por aca, me pa que hay que sacar este else
					frequencyTable = new FrequencyTable();
					frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
					frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
					this->insertInStructure(stringContext,frequencyTable->toString());
							string borrar = frequencyTable->toString();
							cout << borrar << endl;
					//delete frequencyTable;
				}
			}

		}//fin if(continuarCiclo)
	}//fin While(continuarCiclo)


//-------falta ver este pedazo que estaba en el compress de ppmc----------------
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




	//sequentialFile->close();
	std::cout << "Fin de descompresion" << std::endl;
	return true;
}


void Ppmc::createFrequencyTable(std::string stringContext,int actualContextNumber){
	FrequencyTable * frequencyTable = new FrequencyTable();
	frequencyTable->setFrequency(ESC_CHAR,1); // Agrega el escape en el contexto a crearse.
	this->insertInStructure(stringContext,frequencyTable->toString());
	delete frequencyTable;
}

void Ppmc::updateFrequencyTables(std::string stringContext, short character, int actualContextNumber, int maxContext) {

	FrequencyTable* frequencyTable;

	if (this->existsElementInStructure(stringContext)) { // Existe el contexto pasado por parametro.
		StringInputData stringInputData;
		this->findInStructure(stringContext,stringInputData);
		frequencyTable = new FrequencyTable();
		frequencyTable->deserialize(stringInputData.getValue());

		if (frequencyTable->getFrequency(character) == 0) { // Si no existe el caracter en el contexto dado,
			//std::cout << "Emito el caracter " << "Escape" << " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(ESC_CHAR) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del escape en el contexto ACÁ.
			frequencyTable->increaseFrequency(ESC_CHAR,1);//incremento frecuencia al escape
			frequencyTable->setFrequency(character,1); // Agrega el caracter al contexto a crearse, con una ocurrencia.
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			string borrar = frequencyTable->toString();
			//cout << borrar << endl;
		} else { // Si ya existe el caracter en el contexto dado, se lo emite, y se incrementa su frecuencia.
			//std::cout << "Emito el caracter " << character <<  " en el contexto " << stringContext << " con " << frequencyTable->getFrequency(character) << " ocurrencias" << std::endl; // TODO Adrián: emitir la probabilidad del caracter en el contexto ACÁ.
			//this->countHit(stringContext);		//TODO MAti - countHit!
			frequencyTable->increaseFrequency(character,1);
			std::string stringFrequencyTable = frequencyTable->toString();
			this->modifyInStructure(stringContext,stringFrequencyTable);
			string borrar = frequencyTable->toString();
			//cout << borrar << endl;
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
		//cout << borrar << endl;
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
