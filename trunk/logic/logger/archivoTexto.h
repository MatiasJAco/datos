#ifndef __ARCHIVOTEXTO_H__
#define __ARCHIVOTEXTO_H__

#ifndef MAX_LENGTH
#define MAX_LENGTH 256
#endif

//Inclusiones necesarias
#include <fstream>

/**
 * Es el archivo referente al Logger
 */
class ArchivoTexto {

private:
  std::fstream  archivo;  // referencia al archivo

public:
  /**
   * Abre el archivo ubicado en el path pasado (debe incluir nombre completo) en modo lectura/escritura.
   * Deja el cursor al comienzo del mismo.
   * En caso de no existir el archivo, lo crea.
   * Si no puede realizar la operación, arroja una excepción
   * @param path Es el path del archivo
   */
  ArchivoTexto(const std::string& path);

  /**
   * Cierra el archivo (no lo destruye físicamente)
   */
  ~ArchivoTexto();

  /**
   * Escribe un caracter al archivo en la posición del cursor.
   * Luego de escribirlo, el cursor queda en la posición siguiente
   * Si no puede escribir, arroja una excepción
   * @param c Es el caracter a escribir
   */
  void escribir(char c);

  /**
   * Escribe una cadena de caracteres al archivo en la posición del cursor.
   * Luego de escribirlo, el cursor queda en la posición siguiente al último caracter de la cadena
   *  Si no puede escribir, arroja una excepción
   *  @param cadena Es la cadena de caracteres a escribir
   */
  void escribir(const std::string& cadena);

  /**
   * Posiciona el cursor en una nueva linea debajo de la actual
   * Si no puede hacerlo, arroja una excepción
   */
  void terminarLinea();

  /**
   * Escribe una tabulación horizontal en el archivo, quedando el cursor en la posición siguiente
   * Si no puede hacerlo, arroja una excepción
   */
  void tabular();

  /**
   * Lee del archivo una cadena de caracteres a partir de la posición actual del cursor y hasta:
   *  - Que se encuentre un fin de linea
   *  - Se lean MAX_LENGTH caracteres
   * El contenido leido se almacena en el parámetro "cadena"
   * Retorna true si pudo leer una linea, o false en caso contrario
   * @param cadena Es la cadena de caracteres a leer
   * @return bool Retorna true si pudo leer correctamente, false en caso contrario
   */
  bool leerLinea(std::string &cadena );

  /**
   * Posiciona el cursor al comienzo del archivo
   */
  void irAlPrincipio();

  /**
   * Posiciona el cursor al final del archivo
   */
  void irAlFinal();

  /**
   * Lee un caracter del archivo de texto y lo guarda en el parametro caracter
   * El caracter queda almacenado en el parametro caracter
  */
  void leerCaracter(char&);

  /**
   * indica si el archivo llego a su fin
   * @return bool Devuelve true si es el fin del archivo y false en caso contrario
   */
  bool finDeArchivo();

  /*
  Descripcion: Indica posicion del cursor en el archivo
  pre:-
  post:Devuelve un entero que representa la posicion del cursor en el archivo
  */
  int getPosicionCursor();

  /**
   * Cambia posicion del cursor en el archivo
   * Recibe entero positivo
   */
  void setPosicionCursor(int);

  /**
   * Permite obtener el tamanio del archivo
   * @return long Devuelve el tamanio del archivo en bytes
   */
   long getTamanio();
};

#endif
