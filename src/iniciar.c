#include "pps_iniciar.h"
#include <stdio.h>
#include "libwordle.h"
#include "wordle_dicc.h"
#include "test_dicc.h"

/* Definición de las variables globales "públicas" */
FILE *fich_log = NULL;
unsigned int clave_cesar;
unsigned int n_palabras = 0;
char **diccionario = NULL;

int iniciar(char *fdic, char *flog, char modo) {
	FILE *fddic = NULL;
    int rcod;
        
	if (modo != 'j' && modo != 't')
		return NOMOD;
	/*
	 * Abrir fichero para el log
	 */
	fich_log = fopen(flog, "w");
	if (fich_log != NULL) {
		/*
		 * Abrir fichero diccionario y cargar en memoria
		 */
		if ((fddic = fopen(fdic, "r")) != NULL) {
			rcod = cargar_diccionario(fddic);
			if(rcod > 0) {
				/*
				 * Carga correcta. Cerrar el diccionario!!!
				 */
				fclose(fddic);
				if(modo == 'j')
					/*
					 * A jugar... Entrada al módulo del juego
					 */
					jugar_wordle();
				else
					/*
					 * Ejecutar tester
					 */
					testear_dicc(fdic, flog);
				/*
				 * Vaciar el diccionario
				 */
				vaciar_diccionario();
				/*
				 * Todo correcto. Devolver 0
				 */
				rcod = 0;
			}
		}
		else {
			fprintf(stderr, "ERR[pps_wordle]: Diccionario (%s) no encontrado\n", fdic);
			rcod = NODIC;
		}
		/*
		 * Cerrar el log
		 */
		fclose(fich_log);
	}
	else {
		fprintf(stderr, "ERR[pps_wordle]: Imposible abrir el fichero de log [%s]\n", flog);
		rcod = NOLOG;
	}

	return rcod;
}

