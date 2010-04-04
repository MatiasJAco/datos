/*
 * Block.h
 *
 *  Created on: xx/03/2010
 *      Author: Adrián / Pablo
 */

#include "Block.h"

using namespace std;

Block::~Block() {
	// TODO Auto-generated destructor stub
}

unsigned int Block::getSize() const
{
	//TODO iterar por los registros y sumar su tamaño
	return 0;
}

Block & Block::operator =(const Block & bloque)
{
	//TODO iterar revisando si cada registro es igual dentro de cada bloque (este, y
	//el pasado por parámetro. y además iguales en el mismo orden.
	return *this;
}

Block *Block::newInstance() const
{
	return new Block();
}

char *Block::serialize(char *bytes) const
{
	//TODO serializar pasando los bloques como tira de bytes de los registros.
	return bytes;
}

void Block::deserialize(const char *bytes)
{
	//TODO deserializar pasando los bytes a bloques de registros.
}

string Block::toString() const
{
	//TODO pasar el contenido del bloque a string. por ejemplo, mostrando los IDs de cada
	//registro.
	return "";

}
