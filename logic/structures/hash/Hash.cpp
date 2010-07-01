/*
 * Hash.cpp
 *
 *  Created on: Apr 16, 2010
 *      Author: Pablo Lisio / Adrián Bernardi
 */

#include "Hash.h"


Hash::Hash() {
	m_BlockSize = BUCKET_SIZE_DEFAULT;
	this->hashTable->createFile();
	this->hashFile = new BlockFile();
	this->hashFile->open("./hash.bin", m_BlockSize);
	this->inicializeHashFile();
}

Hash::~Hash() {
	this->hashFile->close();
	delete hashFile;
}

void Hash::setBlockSize(unsigned int size)
{
	if(size >0)
		m_BlockSize = size;
}


bool Hash::find(std::string key, InputData & data) throw (ManagerException) {
	bool exists = false;
	if (!this->existsElement(key))
		throw HashException(HashException::INEXISTENT_ELEM);
	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Bucket* bucket = new Bucket(this->hashFile->getBlock(bucketNumber));
	if (bucket->existsRegister(key)) {
		VarRegister varRegister = bucket->getRegister(key);
		StringInputData* stringInputData = new StringInputData();
		stringInputData->toData(varRegister.getValue());
		data.setKey(stringInputData->getKey());
		data.setValue(stringInputData->getValue());
		delete stringInputData;
		exists = true;
	}
	delete bucket;
	return exists;
}

Bucket* Hash::createNewBucket(int depth){
	VarRegister* varRegister = new VarRegister();

	std::string depthString;
	std::stringstream aux;
	aux << depth;
	depthString = aux.str();

	varRegister->setValue(depthString);
	Block* block = this->hashFile->getNewBlock();
	Bucket *bucket = new Bucket(block);
	bucket->setDepth(depth);
	block->addRegister(*varRegister);
	this->saveBucket(bucket);
	delete varRegister;
	bucketsUsedAmount++;	//se agrego un bucket al archivo Hash
	return bucket;
}

void Hash::inicializeHashFile(){
	Block* block = this->hashFile->getBlock(1);
	if (block == NULL)
		createNewBucket(1);
	if (block!=NULL)
		delete block;
}

int Hash::calculateHashFunction(std::string key) {
	int numero = 0;
	try {
	MD5 md5(key);
	std::string md5KeyString(md5.hexdigest());
	int i = 0;
	std::string nueva = "";
	while(i < 32) {
		if (md5KeyString.substr(i,1).compare("0") == 0) {
			nueva.append("00");
		} else if (md5KeyString.substr(i,1).compare("1") == 0) {
			nueva.append("01");
		} else if (md5KeyString.substr(i,1).compare("2") == 0) {
			nueva.append("02");
		} else if (md5KeyString.substr(i,1).compare("3") == 0) {
			nueva.append("03");
		} else if (md5KeyString.substr(i,1).compare("4") == 0) {
			nueva.append("04");
		} else if (md5KeyString.substr(i,1).compare("5") == 0) {
			nueva.append("05");
		} else if (md5KeyString.substr(i,1).compare("6") == 0) {
			nueva.append("06");
		} else if (md5KeyString.substr(i,1).compare("7") == 0) {
			nueva.append("07");
		} else if (md5KeyString.substr(i,1).compare("8") == 0) {
			nueva.append("08");
		} else if (md5KeyString.substr(i,1).compare("9") == 0) {
			nueva.append("09");
		} else if (md5KeyString.substr(i,1).compare("a") == 0) {
			nueva.append("10");
		} else if (md5KeyString.substr(i,1).compare("b") == 0) {
			nueva.append("11");
		} else if (md5KeyString.substr(i,1).compare("c") == 0) {
			nueva.append("12");
		} else if (md5KeyString.substr(i,1).compare("d") == 0) {
			nueva.append("13");
		} else if (md5KeyString.substr(i,1).compare("e") == 0) {
			nueva.append("14");
		} else if (md5KeyString.substr(i,1).compare("f") == 0) {
			nueva.append("15");
		} else {
			nueva.append(md5KeyString.substr(i,1));
		}
		i++;
	}
	BigInteger f = stringToBigInteger(nueva);
	BigInteger g = BigInteger(this->hashTable->getSize());
	numero = (f % g).toInt();
	} catch(...) {
		std::cout << "error desconocido. " << std::endl;
	}
	return numero;
	//return atoi (key.c_str()) % this->hashTable->getSize();
}

void Hash::saveBucket(Bucket * bucket){
	this->hashFile->saveBlock(bucket->getBlock());
}

int Hash::getNumberOfBucket(std::string key) {
	//incremento en uno el valor porque el metodo getBlock() no acepta ceros (0)
	int result = 1;
	result += this->hashTable->getNumberOfBucketInHash(calculateHashFunction(key));
	return result;
}

bool Hash::existsElement(std::string key) {
	int aux = -1;
	return (this->existsElement(key,aux));
}

bool Hash::existsElement(std::string key, int & position) {
	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Block * block = this->hashFile->getBlock(bucketNumber);
	Bucket* bucket = new Bucket(block);
	bool result = bucket->existsRegister(key,position);

	delete bucket;
	return result;
}

int Hash::reHash(Bucket* bucketDesbordado) {
	list<StringInputData> listaDatos;
	bucketDesbordado->getListOfSids(listaDatos);
	bucketDesbordado->empty();
	this->saveBucket(bucketDesbordado);

	//recorro toda la lista de sids y redisperso el bloque
	while (!listaDatos.empty()) {
		StringInputData sid = listaDatos.front();
		this->insert(&sid);
		listaDatos.pop_front(); // Borro el primer sid de la lista.
	}
	delete bucketDesbordado;
	return 0;
}

Bucket* Hash::tryToInsertNewSid(StringInputData* sid, int & result) {
	unsigned int bucketNumber = this->getNumberOfBucket(sid->getKey());

	// Se obtiene el bloque desde el disco
	Block* block = this->hashFile->getBlock(bucketNumber);
	Bucket* bucket = new Bucket(block);
	result = bucket->insertRegister(sid);
	return bucket;
}

bool Hash::insert(std::string clave, string valor) throw (ManagerException){
	StringInputData* sid = new StringInputData();
	sid->setKey(clave);
	sid->setValue(valor);
	bool result = this->insert(sid);
	delete sid;
	return result;
}

bool Hash::insert(StringInputData* sid) throw (ManagerException){
	// Verifico unicidad
	if (existsElement(sid->getKey())){
		throw HashException(HashException::DUPLICATED);
	}

	int insertResult;
	Bucket * bucket = tryToInsertNewSid(sid,insertResult);
	if (insertResult == 0) { //si se pudo agregar en el bucket lo guardo
		this->saveBucket(bucket);
		delete bucket;
	} else if (insertResult == 1) {  //hubo desborde
		int tamTabla = this->hashTable->getSize();
		int td = bucket->getDepth();
		if (td==tamTabla) {
			this->hashTable->duplicate();
			Bucket *bucketNuevo = createNewBucket(tamTabla * 2);
			unsigned int numeroBuquet = bucket->getNumber();
			unsigned int numeroBuquetNuevo = bucketNuevo->getNumber();
			this->hashTable->changeFirstTimeInTable(numeroBuquet,numeroBuquetNuevo);
			delete bucketNuevo;
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->insert(sid);
		} else {
			bucket->duplicateDepth();
			this->saveBucket(bucket);
			Bucket *bucketNuevo = createNewBucket(bucket->getDepth());
			this->hashTable->jumpAndReplace(this->calculateHashFunction(sid->getKey()),bucketNuevo->getDepth(),bucketNuevo->getNumber());
			delete bucketNuevo;
			this->reHash(bucket); // Redispersa los registros del bloque desbordado.
			this->insert(sid);
		}
	} else {
		delete bucket;
		//return insertResult;
		throw HashException(HashException::OPERATION_FAULT);
	}
	return true;
}

bool Hash::modify(std::string key, string newValue) throw (ManagerException){
	StringInputData* sid = new StringInputData();
	sid->setKey(key);

	if (!this->existsElement(sid->getKey())) {
		delete sid;
		throw HashException(HashException::INEXISTENT_ELEM);
	}

	sid->setValue(newValue);
	bool resultErase = this->remove(key);

	if (resultErase) { // Si se pudo borrar correctamente el dato, se trata de reinsertar pero con el nuevo valor.
		bool resultAdd = this->insert(sid);
		if (!resultAdd) {
			throw HashException(HashException::OPERATION_FAULT);
		}
	} else {
		throw HashException(HashException::OPERATION_FAULT);
	}
	delete sid;
	return true;
}

bool Hash::remove(std::string key) throw (ManagerException){
	if (!this->existsElement(key))
		throw HashException(HashException::INEXISTENT_ELEM);

	bool result = false;

	unsigned int bucketNumber = this->getNumberOfBucket(key);
	Block* block = this->hashFile->getBlock(bucketNumber);
	Bucket* bucket = new Bucket(block);
	result = bucket->deleteRegister(key);

	if (result == false) {
		delete bucket;
		throw HashException(HashException::OPERATION_FAULT);
	} else { // Si se pudo borrar exitosamente, reviso cuantos registros le quedan al bloque.

		this->saveBucket(bucket);
		unsigned int registerAmount = block->getRegisterAmount();

		unsigned int depth = bucket->getDepth();
		delete bucket;
		unsigned int tamTable = this->hashTable->getSize();
		int element = -1;
		bool soloLiberarBq = false;
		if ((depth>1)&&(tamTable>1))
			element = this->hashTable->verifyJumps(this->calculateHashFunction(key), depth/2);
		else if (bucketsUsedAmount > 1)
			soloLiberarBq = true;

		if (((registerAmount == 1) && (depth == tamTable) && (element != -1))  ||  ((registerAmount == 1)&& soloLiberarBq)) {
			//intento liberar el bloque
			if (!this->hashFile->deleteBlock(bucketNumber))
				throw HashException(HashException::OPERATION_FAULT);

			if (soloLiberarBq)
				return true;

			// Un bucket fue liberado
			bucketsUsedAmount--;

			//hago las modificaciones necesarias en la tabla
			this->hashTable->modifyRegister(this->calculateHashFunction(key),element);

			Block *blockAux = this->hashFile->getBlock(element+1);
			Bucket * bucketAux = new Bucket(blockAux);
			int tdElement = bucketAux->getDepth();
			this->hashTable->jumpAndReplace(this->calculateHashFunction(key),tdElement,element);

			if (!bucketAux->divideDepth()){
				delete bucketAux;
				throw HashException(HashException::UNDEFINED);
			}
			else
				this->saveBucket(bucketAux);

			delete bucketAux;
			this->hashTable->verifyAndDivide();
		}
	}

	return true;
}

void Hash::print() {
	unsigned int i = 1;
	Bucket* bucket;
	Block* actualBlock = this->hashFile->getBlock(i);
	this->hashTable->print();

	cout << "Bloques libres: ";
	FreeBlockList freeBlockList = this->hashFile->getFreeBlockList();
	for (list<unsigned int>::iterator it = freeBlockList.begin(); it != freeBlockList.end(); it++)
	    cout << *it -1 << " | ";
	cout << endl;

	cout << "HashFile: " << endl;
	while (actualBlock != NULL) {
		int numeroReal = i-1;
		cout << "Bucket " << numeroReal << ": ";
		bucket = new Bucket(actualBlock);
		bucket->print();
		i++;
		delete bucket;
		actualBlock = this->hashFile->getBlock(i);
		cout << endl;
	}
	cout << endl;
}

bool Hash::deleteGeneratedFiles() {
	std::remove("tabla.txt");
	return this->hashFile->deleteFile();
}

keyList Hash::getKeys() {
	keyList keys;

	unsigned int i = 1;
	Block* actualBlock = this->hashFile->getBlock(i);

	while (actualBlock != NULL) {
		VarRegister varReg;
		bool primeraVez = true;
		actualBlock->restartCounter();

		while (actualBlock->hasNextRegister()) {
			varReg=actualBlock->getNextRegister(true);
			StringInputData* sid = new StringInputData();
			char* value = varReg.getValue();
			sid->toData(value);
			if (!primeraVez) {
				keys.push_back(sid->getKey());
			}
			primeraVez=false;

			if (value !=NULL) {
				delete [] value;
			}
			delete sid;
		}

		i++;
		actualBlock = this->hashFile->getBlock(i);
	}
	return keys;
}
