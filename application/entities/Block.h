/*
 * Block.h
 *
 *  Created on: xx/03/2010
 *      Author: Adrián / Pablo
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "KeyInt.h"
#include "StringRegister.h"
#include "../../common/register/Register.h"
#include "../../common/utils/ByteConverter.h"

#include <iostream>
#include <sstream>
#include <list>
using namespace std;

/**
 * Class Block
 * Esta clase contiene un conjunto de registros.
 *
 * @see Register
 */
class Block {

//Atributos
private:

	list<StringRegister> registers;

public:
	//-------------Constructor/Destructor------//
	Block(){};

	~Block();

	unsigned int getSize() const;

	Block& operator=(const Block& bloque);

	/**
	 * Devuelve una instancia nueva de la clase.
	 * Se crea una nueva instancia del tipo especifico con new()
	 * Importante: Una vez que se termine de usar la instancia
	 * es necesario liberar la memoria mediante un delete.
	 * @throws bad_alloc en caso de error al asignar memoria
	 * @return Register * puntero a la instancia nueva
	 */
	Block * newInstance() const;

	char* serialize(char* bytes) const;

	/**
	 * Transforma la cadena de bytes a un bloque
	 * \param bytes Cadena de bytes de la cual lee para asignar los registros del bloque.
	 */
	void deserialize(const char* bytes);

	std::string toString() const;

	list<StringRegister> getRegisters() const
    {
        return this->registers;
    }

    void setRegistersSet(list<StringRegister> registers)
    {
        this->registers = registers;
    }
};

#endif /* BLOCK_H_ */
