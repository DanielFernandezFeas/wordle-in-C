#ifndef PPS_INICIAR_H
#define PPS_INICIAR_H

#include "wordle_dicc.h"

/* Macros para constantes usadas como resultados */
#define NOLOG -10 /* Error relacionado con el fichero de logs */
#define NODIC -11 /* Error relacionado con el fichero de diccionario */
#define NOMOD -12 /* Error relacionado con el modo */

/*
 * - Comprueba la corrección de los argumentos:
 *   - nomfich_dicc: path del archivo del diccionario
 *   - nomfich_log: path del archivo de log
 *   - modo: 'j' si es modo juego, 't' si es modo tester
 * - Carga el diccionario y ejecuta en el modo que corresponda (si el
 *   modo es 'j' ejecuta jugar_wordle, si el modo es 't' ejecutar
 *   testear_dicc).
 * - Cierra ficheros y libera memoria antes de terminar
 *
 * PRECONDICIÓN: nomfich_dicc y nomfich_log no son NULL
 *
 * DEVUELVE:
 *   NOMOD si modo no es 'j' o 't'
 *   NODIC si no encuentra el archivo del diccionario
 *   NOLOG si no crea el archivo de log
 *   NOLEE si falla la lectura del archivo del diccionario
 *   NOMEM si falla la asignación de memoria dinámica
 *   NOCLA si la clave de cifrado no es válida
 *   NOPAL si el número de palabras en el dicc no coincide
 *         con el indicado en la estructura de control
 *   0 si todo es correcto
 */
int iniciar(char *nomfich_dicc, char *nomfich_log, char modo);

#endif /* PPS_INICIAR_H */
