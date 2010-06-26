/**
 * @file ByteConverter.h
 * @author MCM
 * @date 26-03-2010
 */

#ifndef BYTECONVERTER_H_
#define BYTECONVERTER_H_

#include <cstring>
#include <iostream>
#include <iomanip>

typedef enum {ONE,ZERO} Bit;

/**
 * Clase con métodos estáticos para transformar tipos de datos a cadena de bytes y viceversa.
 * No tiene constructores ni destructor.
 */

class ByteConverter {
public:

	/**
	 * Convierte una cadena de bytes a un entero.
	 * \param bytes La cadena de bytes a convertir
	 * \return Entero despues de la conversión de la cadena de bytes.
	 */
	static int bytesToInt(const char* bytes);


	/**
	 * Convierte una cadena de bytes a un entero.
	 * \param bytes La cadena de bytes a convertir
	 * \return Entero despues de la conversión de la cadena de bytes.
	 */
	static long bytesToLong(const char* bytes);


	/**
	 * Convierte un entero a una cadena de bytes.
	 * \param entero El entero a convertir.
	 * \param bytes La cadena de bytes donde se almacena la conversión.
	 * \return El puntero a la cadena de bytes.
	 */
	static char* intToBytes(const int entero,char* bytes);

	/**
	 * Convierte una cadena de bytes a un entero.
	 * \param bytes La cadena de bytes a convertir
	 * \return Entero despues de la conversión de la cadena de bytes.
	 */
	static unsigned int bytesToUInt(const char* bytes);

	/**
	 * Convierte un entero a una cadena de bytes.
	 * \param entero El entero a convertir.
	 * \param bytes La cadena de bytes donde se almacena la conversión.
	 * \return El puntero a la cadena de bytes.
	 */
	static char* uIntToBytes(const unsigned int entero,char* bytes);

	/**
	 * Convierte un long a una cadena de bytes.
	 * \param long El entero a convertir.
	 * \param bytes La cadena de bytes donde se almacena la conversión.
	 * \return El puntero a la cadena de bytes.
	 */
	static char* uLongToBytes(const unsigned long longInt,char* bytes);

	/**
	 * Convierte un entero a una cadena de bytes.
	 * \param long El entero a convertir.
	 * \param bytes La cadena de bytes donde se almacena la conversión.
	 * \return El puntero a la cadena de bytes.
	 */
	static char* shortToBytes(const short shortInt,char* bytes);


	/**
	 * Convierte una cadena de bytes a un double.
	 * \param bytes La cadena de bytes a convertir
	 * \return double despues de la conversión de la cadena de bytes.
	 */
	static double bytesToDouble(const char* bytes);

	/**
	 * Convierte un double a una cadena de bytes.
	 * \param decimald El double a convertir.
	 * \param bytes La cadena de bytes donde se almacena la conversión.
	 * \return El puntero a la cadena de bytes.
	 */
	static char* doubleToBytes(const double decimald,char* bytes);

	/**
	 * Convierte una cadena de bytes a un float.
	 * \param bytes La cadena de bytes a convertir
	 * \return float despues de la conversión de la cadena de bytes.
	 */
	static float bytesToFloat(const char* bytes);

	/**
	 * Convierte un float a una cadena de bytes.
	 * \param decimalf El float a convertir.
	 * \param bytes La cadena de bytes donde se almacena la conversión.
	 * \return El puntero a la cadena de bytes.
	 */
	static char* floatToBytes(const float decimalf,char* bytes);

	/**
	 * Convierte una cadena de bytes a un dato de tipo string.
	 * \param bytes La cadena de bytes a convertir
	 * \return string despues de la conversión de la cadena de bytes.
	 */
	static std::string bytesToString(const char* bytes);

	/**
	 * Convierte un dato de tipo string a una cadena de bytes, sin
	 * necesidad de manejar el tamaño en caracteres del string.
	 * @param bytes La cadena de bytes donde almacena la conversion.
	 * @param str El string a convertir en bytes.
	 * @return El puntero a la cadena de bytes.
	 */
	static char* stringToBytes(const std::string str,char* bytes);

	/**
	 * Convierte una conjunto de bits a un short.
	 * @param bits Tira de bits a convertir.
	 * @param nbits Cantidad de bits.
	 * @return Numero tipo short que tiene el contenido de la tira de bits.
	 */
	static int bitsToInt(Bit bits[],unsigned int nbits);

	/**
	 * Imprime el contenido del stream en hexadecimal. Su uso es para debug
	 * @param stream el stream a imprimir
	 * @param size cantidad de bytes a imprimir
	 */
	static void printHexa(char *stream,unsigned int size);


};

#endif /* BYTECONVERTER_H_ */
