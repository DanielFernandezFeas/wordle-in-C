#ifndef WORDLE_DICC_H
#define WORDLE_DICC_H

#include <stdio.h>

/* ------------------------------------------------------------------ */
/* Longitud de las palabras */
#define LONG_PALABRA_WORDLE 5

/* ------------------------------------------------------------------ */
/*
 * Declaración de struct y tipo que define los datos binarios al
 * principio de un fichero diccionario (el resto del diccionario son las
 * palabras cifradas).
 */
struct wordle_cabecera_dicc_s {
  unsigned int clave;
  unsigned int n_palabras;
};
typedef struct wordle_cabecera_dicc_s wordle_cabecera_dicc_t;


/* ------------------------------------------------------------------ */
/*
 * Declaración de variables globales usadas por la biblioteca wordle (es
 * obligación del código cliente definirlas e inicializarlas antes de
 * usar la biblioteca)
 */

/* Fichero de logs en el que la biblioteca va a escribir sus trazas */
extern FILE *fich_log;

/* Clave de cifrado/descifrado del algoritmo de Julio César */
extern unsigned int clave_cesar;

/* Tamaño del diccionario (número de palabras que contiene) */
extern unsigned int n_palabras;

/* Diccionario como array de palabras codificadas */
extern char **diccionario;

/* ------------------------------------------------------------------ */
/*
 * Retrollamadas (callbacks) REQUERIDAS por la bibliotea wordle para
 * gestionar el diccionario (a implementar en el código que usa la
 * biblioteca)
 */

/*
 * - Cifrado/Descifrado según algoritmo Julio César
 * - Las trazas se escriben en fich_log
 * - op = 0 codifica; 1 decodifica
 * - La palabra codificada/decodificada se devuelve en el mismo texto
 */
void cifrado_cesar(int op, char *texto);

/*
 * - Busca la palabra (sin codificar) en el diccionario (deberá
 *   codificarla antes de iniciar la búsqueda)
 * - Las trazas se escriben en fich_log
 *
 * DEVUELVE:
 *   1 si encuentra la palabra, 0 en otro caso
 */
int en_diccionario(char *palabra);

/*
 * - Elige una palabra del diccionario y la devuelve en palabra
 * - Las trazas se escriben en fich_log
 * - pos deberá estar en el intervalo [0,n_palabras)
 */
void elegir_palabra(char *palabra, int pos);

/*
 * - Carga el diccionario (se mantiene codificado) en memoria
 * - Las trazas se escriben en fich_log
 * - Recoge en la variable clave_cesar el valor de la clave de
 *   cifrado/descifrado (en el rango [1, 25])
 * - Recoge en la variable global n_palabras el número de palabras
 *   leídas del archivo del diccionario
 *
 * DEVUELVE:
 *   NOLEE si falla la lectura del archivo del diccionario
 *   NOMEM si falla la asignación de memoria dinámica
 *   NOCLA si la clave de cifrado no es válida
 *   NOPAL si el número de palabras en el dicc no coincide
 *         con el indicado en la estructura de control
 *   El número de palabras cargadas si la carga es exitosa
 */
int cargar_diccionario(FILE *fich_dicc);

/*
 * - "Vacía" el diccionario liberando TODA la memoria asignada
 * - Las trazas se escriben en fich_log
 */
void vaciar_diccionario(void);

/* ------------------------------------------------------------------ */
/*
 * Macros para constantes usadas en los resultados de la carga del
 * diccionario
 */
#define NOLEE -20 /* Error relacionado con la lectura del diccionario */
#define NOMEM -21 /* Error relacionado con la memoria dinámica */
#define NOCLA -22 /* Error relacionado con la clave de cifrado */
#define NOPAL -23 /* Error relacionado con el número de palabras */

#endif /* WORDLE_DICC_H */
