#include <stdio.h>
#include <string.h>
#include "palabra.h"

struct palabra {
    char *letras; // Cadena de n caracteres, incluido el '\0'
    size_t n; // longitud de la palabra, sin contar el '\0' (Por ejemplo, l de "hola" es 4. Como funciona en strlen)
};

palabra_t *palabra_crear(char *p, size_t n) {
    palabra_t *palabra = malloc(sizeof(palabra_t));
    if(palabra == NULL)
        return NULL;

    palabra->letras = malloc((n + 1) * sizeof(char));
    if(palabra->letras == NULL)
        return NULL;

    strcpy(palabra->letras, p);

    palabra->n = n;

    return palabra;
}


void palabra_destruir(palabra_t *p) {
    free(p);
}

void palabra_mostrar(palabra_t *p) {
    printf("%s", p->letras);
}

char *palabra_obtener_palabra(palabra_t *p) {
    return p->letras;
}

char palabra_obtener_letra(palabra_t *p, size_t n) {
    return p->letras[n];
}

size_t palabra_obtener_longitud(palabra_t *p) {
    return strlen(p->letras);
}
