#include <iostream>
using namespace std;
#include "../common/hash/Table.h"

int main(){
	Table miTabla;
	miTabla.crearArch();
	int tamTabla = miTabla.obtenerTamanio();
	int listaElementosTabla[tamTabla];

	miTabla.parsear(listaElementosTabla);
	miTabla.imprimir(listaElementosTabla,tamTabla);

	miTabla.modificarRegistro(2,50);
	tamTabla = miTabla.obtenerTamanio();
	int listaElementosTabla2[tamTabla];
	miTabla.parsear(listaElementosTabla2);
	miTabla.imprimir(listaElementosTabla2,tamTabla);

	miTabla.duplicar();
	tamTabla = miTabla.obtenerTamanio();
	int listaElementosTabla3[tamTabla];
	miTabla.parsear(listaElementosTabla3);
	miTabla.imprimir(listaElementosTabla3,tamTabla);

	miTabla.duplicar();
	tamTabla = miTabla.obtenerTamanio();
	int listaElementosTabla4[tamTabla];
	miTabla.parsear(listaElementosTabla4);
	miTabla.imprimir(listaElementosTabla4,tamTabla);

	miTabla.duplicar();
	tamTabla = miTabla.obtenerTamanio();
	int listaElementosTabla5[tamTabla];
	miTabla.parsear(listaElementosTabla5);
	miTabla.imprimir(listaElementosTabla5,tamTabla);

	miTabla.modificarRegistro(70,23);
	tamTabla = miTabla.obtenerTamanio();
	int listaElementosTabla6[tamTabla];
	miTabla.parsear(listaElementosTabla6);
	miTabla.imprimir(listaElementosTabla6,tamTabla);

	return 0;
}
