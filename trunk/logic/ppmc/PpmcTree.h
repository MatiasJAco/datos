/*
 * PpmcTree.h
 *
 *  Created on: Jun 7, 2010
 *      Author: Adrián Bernardi - Matias Acosta - Pablo Lisio
 */

#ifndef PPMCTREE_H_
#define PPMCTREE_H_

#include "Ppmc.h"
#include "../logic/input/StringInputData.h"
#include "../logic/structures/tree/BPlusTree.h"


/**
 * Clase que modela el algoritmo de compresión de PPMC con almacenamiento de la tabla en un Arbol
 * usando metodos comunes implementados en la clase padre PPMC
 */
class PpmcTree: public Ppmc {

private:
	/* El arbol que se usa para guardar las tablas de estadisticas del algoritmo de compresion. */
		BPlusTree* tree;

public:

	PpmcTree();
	virtual ~PpmcTree();

	/**
	 * Este metodo se encarga de la compresión.
	 * @param path Es el path donde se encuentra el archivo a comprimir.
	 * @param context Es el número de contexto con el cuál se va a comprimir con ppmc.
	 * @return Devuelve true si comprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool compress(std::string path,int context);

	/**
	 * Este metodo se encarga de la decompresión
	 * @param path Es el path donde se encuentra el archivo a decomprimir.
	 * @return Devuelve true si decomprimio correctamente. En caso contrario devuelve false.
	 */
	virtual bool deCompress(const std::string & path);

	/**
	 * Este metodo muestra las estadisticas de la compresión
	 */
	virtual void getStatistics();





	//Muestra por pantalla la estructura que contiene los contextos.
	//TODO Se usa para debugging, ver si se deja al final.
	void showContexts();



};

#endif /* PPMCTREE_H_ */
