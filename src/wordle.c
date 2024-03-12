#include <stdio.h>
#include "pps_iniciar.h"

/*
 * INVOCACIÓN
 *
 *   ./wordle DICC LOG MODO
 *
 * - DICC es el nombre del fichero con el diccionario que se va a cargar.
 * - LOG es el nombre del fichero para el log.
 * - MODO puede ser "j" p "t" e indica si se desea arrancar el juego
 *   ("j") o si se desea probar las funciones de gestión del diccionario
 *   ("t").
 */
int main(int argc, char * argv[]) {
  int rcod = -1;

  if(argc == 4)
    rcod = iniciar(argv[1], argv[2], argv[3][0]);
  else
    fprintf(stderr, "ERR[main]: Parámetros incorrectos. No hace nada\n");
  
  return rcod;
}
