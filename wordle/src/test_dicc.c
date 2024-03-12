#include "test_dicc.h"
#include <time.h>
#include "wordle_dicc.h"

void testear_dicc(char *fdic, char *flog) {
	time_t tidx;
	int didx = 0;
	struct tm *tinf;
	char aux[LONG_PALABRA_WORDLE+1];

	didx = (int) (time(NULL) % n_palabras);  /* índice aleatorio en el diccionario */

	/*
	 * Test #1: Recuperar palabra del diccionario
	 * Se selecciona una palabra aleatoriamente a partir
	 * del nº de segundos transcurridos desde 01/01/1970
	 */
	elegir_palabra(aux, didx);

	/*
	 * Test #2: Decodificar palabra del diccionario
	 */
	cifrado_cesar (1, aux);

	fprintf(stdout, "\tPPS C Wordle (2023)\n");
	fprintf(stdout, "\t===================\n");
	fprintf(stdout, "\t\tRuta fich dic:\t%s\n", fdic);
	fprintf(stdout, "\t\tRuta fich log:\t%s\n", flog);
	time(&tidx);
	tinf = localtime(&tidx);
	fprintf(stdout, "\t\tHora ejecución:\t%s", asctime(tinf));
	fprintf(stdout, "\t-------------------\n");
	fprintf(stdout, "\t\tPalabras en dicc:\t\t%d\n", n_palabras);
	fprintf(stdout, "\t\tPosición aleatoria en dicc:\t%d\n", didx+1);
	fprintf(stdout, "\t\tPalabra en posición aleatoria:\t%s\n", aux);

	/*
	 * Test #3: Buscar palabra en el diccionario
	 */
	if(!en_diccionario (aux))
		fprintf(stdout, "\t\tTest en_diccionario():\t\tKO\n");
	else
		fprintf(stdout, "\t\tTest en_diccionario():\t\tOK\n");

	fprintf(stdout, "\t-------------------\n");
}


