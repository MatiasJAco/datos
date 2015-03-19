# Mini tutorial doxygen.

# Instalacion #

  1. En una terminal:  `sudo apt-get install doxygen`
  1. Instalar el plugin Eclox.
    * En Eclipse Galileo: Help->Install new software y en add, agregar la url: http://download.gna.org/eclox/update
  1. Instalar graphviz (_Opcional_) : `sudo apt-get install graphviz`

# Detalles #

Una vez que instalen el plugin y reinicien eclipse, aparece un boton con el simbolo @ en la barra de herramientas para generar el archivo de configuracion del doxygen, que es lo unico que se necesita para generar la documentacion.

Es bastante intuitivo de usar: hay que indicarle el proyecto sobre el cual queremos generar la doc, y setearle otros parametros segun si se quiere que la salida sea html, rtf, tex, etc. Tambien aparecen otras opciones avanzadas.

Tiene la opcion de generar graficos de clases,etc.. para lo cual es necesario el graphviz. Aunque sobre esto no investigue mucho.

# Ejemplo #

Yo anduve probando con el de esta pagina: http://www.upl.cs.wisc.edu/tutorials/doxygen/.
Despues lo subo al repositorio en una carpeta de pruebas.