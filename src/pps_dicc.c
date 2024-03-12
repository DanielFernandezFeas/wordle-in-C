#include "wordle_dicc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAYMIN 65
#define MAYMAX 90
#define MINMIN 97
#define MINMAX 122

#define OK 0
#define KO -1

char *mi_strdup(const char *s);

void cifrado_cesar (int op, char *pword) {
    char *aux = pword;
    int cbase;
    int ascii;
    int idx = 0;

	fprintf(fich_log, "DBG[cifrado_cesar]: op = %d; pword = %s\n", op, pword);

    while(idx < LONG_PALABRA_WORDLE) {
        if(((int) aux[idx] >= MAYMIN) && ((int) aux[idx] <= MAYMAX))
        	/*
        	 * Letra mayúscula => base es 'A'
        	 */
        	cbase = MAYMIN;
        else {
            if(((int) aux[idx] >= MINMIN) && ((int) aux[idx] <= MINMAX)) {
            	/*
            	 * Letra minúscula => base es 'a'
            	 */
            	cbase = MINMIN;
            }
            else
            	/*
            	 * No es letra => no hace nada
            	 */
            	cbase = -1;
        }
        if(cbase > 0) {
        	if (op)
            	ascii = aux[idx] - (cbase - 26 + ((int) clave_cesar));
        	else
            	ascii = aux[idx] - (cbase - ((int) clave_cesar));
        	ascii = ascii % 26;
        	ascii += cbase;
        	aux[idx] = (char) ascii;
        }
        idx++;
    }
}

int en_diccionario(char *word) {
	char aux[LONG_PALABRA_WORDLE+1];
	unsigned int i = 0;
	int found = 1;

	memset(aux, 0, LONG_PALABRA_WORDLE+1);
	memcpy(aux, word, LONG_PALABRA_WORDLE);
	cifrado_cesar (0, aux);        /* Codificar palabra */
	while(i < n_palabras && found != 0)
		found = memcmp(aux, diccionario[i++], LONG_PALABRA_WORDLE);

	fprintf(fich_log, "DBG[en_diccionario]: Palabra (%s:%s); Resultado: ", word, aux);
	fprintf(fich_log, found == 0 ? "OK\n" : "KO\n");

	if (found == 0)
		return 1;
	else
		return 0;
}

void elegir_palabra(char *ppal, int pos) {
	memcpy(ppal, diccionario[pos], LONG_PALABRA_WORDLE);
}

int cargar_diccionario(FILE *fich_dicc) {
	struct dic_wordle {
		unsigned int clave;     /* clave cifrado/descifrado */
		unsigned int npals;     /* palabras en el diccionario */
	} dic_pps = {0, 0};

	char buff[LONG_PALABRA_WORDLE+1];
	char *aux = NULL;
	int rcode = 0;

	/*
	 * Leer struct mediante fread
	 */
	rcode = (int) fread (&dic_pps, sizeof(struct dic_wordle), 1, fich_dicc);
	if(rcode != 1) {
		fprintf(fich_log, "ERR[cargar_diccionario]: Imposible cargar el diccionario\n");
		return NOLEE;
	}
	/*
	 * Reservar memoria para el array de punteros que indexa el diccionario
	 */
	diccionario = (char **) calloc(dic_pps.npals, sizeof(char *));
	if(diccionario == NULL) {
		fprintf(fich_log, "ERR[cargar_diccionario]: Fallo de asignación de memoria. \n");
		return NOMEM;
	}
	/*
	 * Recoger la clave de cifrado/descifrado
	 */
	clave_cesar = dic_pps.clave;
	if(clave_cesar < 1 || clave_cesar > 25) {
		fprintf(fich_log, "ERR[cargar_diccionario]: Clave de cifrado NO válida. El valor debe estar en [1-25]\n");
		return NOCLA;
	}
	/*
	 * Leer el diccionario (una palabra en cada línea)
	 */
	while(fgets(buff, LONG_PALABRA_WORDLE+2, fich_dicc) != NULL) {
		buff[5] = '\0';                                  /* Elimina CR */
		aux = (char *) mi_strdup((char *) buff);        /* Duplica string (asigna memoria nueva) */
		if(aux == NULL) {
			fprintf(fich_log, "ERR[cargar_diccionario]: Fallo de asignación de memoria. \n");
			rcode = NOMEM;
			break;
		}
		diccionario[n_palabras++] = aux;        /* Almacenar palabra */
	}

	if(rcode == NOMEM)
		return NOMEM;
	else {
		fprintf(fich_log, "DBG[cargar_diccionario]: Cargadas %d palabras en el diccionario\n", n_palabras);
		if(n_palabras != dic_pps.npals) {
			fprintf(fich_log, "DBG[cargar_diccionario]: El número de palabras no es correcto\n");
			fprintf(fich_log, "DBG[cargar_diccionario]: Cargadas %d de %d palabras\n", n_palabras, dic_pps.npals);
			return NOPAL;
		}
		return (int) n_palabras;
	}
}

void vaciar_diccionario(void) {
	/*
	 * Liberar la memoria antes de terminar
	 */
	while(n_palabras > 0)
		free((char *) diccionario[--n_palabras]);
   free((char **) diccionario);

	fprintf(fich_log, "DBG[vaciar_diccionario]: Diccionario vaciado correctamente\n");
}

char *mi_strdup(const char *s) {
	char *ptr = NULL;

	ptr = (char *) calloc(LONG_PALABRA_WORDLE+1, sizeof(char));
	if(ptr != NULL)
		memcpy(ptr, s, LONG_PALABRA_WORDLE);
	return ptr;
}


