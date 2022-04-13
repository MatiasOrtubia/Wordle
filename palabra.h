#ifndef PALABRA_H
#define PALABRA_H

#include <stdlib.h>


typedef struct palabra palabra_t;

palabra_t *palabra_crear(char *p, size_t n);
void palabra_destruir(palabra_t *p);

void palabra_mostrar(palabra_t *p);

char *palabra_obtener_palabra(palabra_t *p);

/* Obtiene un caracter de la palabra ubicado en la posicion n */
char palabra_obtener_letra(palabra_t *p, size_t n);

size_t palabra_obtener_longitud(palabra_t *p);

#endif
