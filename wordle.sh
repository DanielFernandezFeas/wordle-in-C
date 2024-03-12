#!/bin/bash

# Verifica que se pase exactamente un argumento
[ $# -eq 1 ] || exit -1

# Realiza acciones según el argumento proporcionado
if [ $1 = compilar ]; then
    # Compilar
    gcc -I"lib/include" -Wall -Wextra -ansi -pedantic -Werror -c -o  src/pps_iniciar.c || exit -1
    gcc -I"lib/include" -Wall -Wextra -ansi -pedantic -Werror -c -o src/pps_dicc.o src/pps_dicc.c || exit -1
    gcc -I"lib/include" -Wall -Wextra -ansi -pedantic -Werror -c -o src/test_dicc.o src/test_dicc.c || exit -1
    gcc -I"lib/include" -Wall -Wextra -ansi -pedantic -Werror -c -o src/wordle.o src/wordle.c || exit -1

    # Enlazar
    gcc -Llib -o wordle src/pps_iniciar.o src/pps_dicc.o src/test_dicc.o src/wordle.o -lwordle || exit -1

elif [ $1 = jugar ]; then
    # Verifica que el ejecutable "wordle" exista y sea ejecutable
    [ -x wordle ] || exit -1
    # Ejecuta wordle con argumentos adicionales
    ./wordle data/dicES5.dat milog.txt j
    exit $?

elif [ $1 = probar ]; then
    # Verifica que el ejecutable "wordle" exista y sea ejecutable
    [ -x wordle ] || exit -1
    # Ejecuta wordle con argumentos adicionales
    ./wordle data/dicTest.dat milog.txt t
    exit $?

elif [ $1 = limpiar ]; then
    # Elimina archivos generados durante la compilación
    rm src/pps_iniciar.o
    rm src/pps_dicc.o
    rm src/test_dicc.o
    rm src/wordle.o
    rm wordle

else
    # Si no coincide con ninguna operación válida, salir con código de error
    exit -1
fi

# Salida exitosa
exit 0
