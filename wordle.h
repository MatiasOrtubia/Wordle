#ifndef WORDLE_H
#define WORDLE_H

#include <stdbool.h>
#include "palabra.h"

/* Busca una palabra aleatoria desde una lista 
 * Se va a usar para saber si la palabra existe 
 * Devuelve un puntero a la palabra, y NULL si no la encuentra */
palabra_t *wordle_buscar_palabra(palabra_t *palabra, palabra_t **lista_palabras);

/* Para ver si la letra esta en la palabra, y en que posicion */
/* Devuelve un string con 6 caracteres incluido el \0, con banderas G si es correcta la posicion y la letra, Y si solo es correcta la letra, - si la letra no esta incluida. */
/* a: palabra a adivinar b: palabra ingresada por el usuario*/
char *letras_verificar(char *a, char *b);
void imprimir_resultado(char *str, char *res);

bool victoria_verificar(char *flags);

#endif
