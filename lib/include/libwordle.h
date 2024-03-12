#ifndef LIBWORDLE_H
#define LIBWORDLE_H

#include <stdio.h>

/* ------------------------------------------------------------------ */
/*
 * Función pública PROPORCIONADA por la biblioteca wordle para jugar a
 * Wordle en la terminal (usa las variables y "retrollamas", declaradas
 * en el fichero de cabecera wordle_dicc.h).
 *
 * PRECONDICIÓN: el diccionario deberá estar cargado en memoria (ver
 * wordle_dicc.h).
 */
int jugar_wordle();

#endif /* LIBWORDLE_H */
