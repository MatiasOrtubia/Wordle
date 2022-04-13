#include <stdio.h>
#include <string.h>
#include "wordle.h"
#include "colores.h"

#define MAX_PALABRAS 100
#define MAX_LETRAS 100

/*
struct lista_palabras {
    palabra_t l[MAX_PALABRAS];
    size_t n;
};

Tengo que ver como crear la lista de palabras. Puede estar harcodeada o puedo ver como importarla.
Siento que lo mejor es usar un archivo externo para poder modificarlo, agregar palabras etc.
*/

/* Busqueda con bsearch
static int cmp(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
} */


/*PARA Verificar que la palabra este en la lista */ 
/*palabra_t *wordle_buscar_palabra(palabra_t *palabra, lista_palabras_t *lista) {
    return bsearch(palabra_obtener_palabra(palabra), lista->l, lista->n, sizeof(char *), cmp);
}
*/

/* Para ver si la letra esta en la palabra, y en que posicion */
/* Devuelve un string con 6 caracteres incluido el \0, con banderas G si es correcta la posicion y la letra, Y si solo es correcta la letra, - si la letra no esta incluida. */
/* a: palabra a adivinar b: palabra ingresada por el usuario*/

/* 
 * TODO:
 * HAY UN ERROR, SI LA PALABRA A ADIVINAR ES "TUNEL", Y PONGO "TENER", EL RESULTADO ES GYGG-, CUANDO DEBERIA SER G-GG- */

/* 
 * Tal vez la solucion es recorrer la palabra dos veces. Una para ver las G y otra para ver las Y */

char *letras_verificar(char *a, char *b) {
    char *res = malloc((strlen(a) + 1)* sizeof(char));
    if(res == NULL) return NULL;

    size_t ia = 0;
    size_t ib = 0;

    char *flags_a = calloc(strlen(a) + 1, sizeof(char));
    if(flags_a == NULL) return NULL;

    char *flags_b = calloc(strlen(b) + 1, sizeof(char));
    if(flags_b == NULL) return NULL;

    while(b[ib] != '\0') {
        if(b[ib] == a[ib]) { /* Las letras coinciden */
            flags_b[ib] = 'G';
            flags_a[ib] = 'G'; // Tal vez no sea necesario
            res[ib] = 'G';
        }
        else {
            ia = 0;
            while(a[ia] != '\0') {
                if(flags_a[ia] == 'Y' || flags_b[ia] == 'G') {
                    ia++;
                    continue;
                }
                if(a[ia] == b[ib]) { /* La letra esta en la palabra */
                    flags_a[ia] = 'Y';
                    res[ib] = 'Y';
                    break;
                }
                else { /* La letra no esta en la palabra */
                    res[ib] = '-';
                    ia++;
                    continue;
                }
            }
        }
        ib++;
    }
    res[ib] = '\0'; // Probar

    return res;
}

void imprimir_resultado(char *str, char *res) {
    size_t l = strlen(str);
    for(size_t i = 0; i < l; i++) {
        switch(res[i]) {
            case 'G': 
                set_green();
                putchar(str[i]);
                break;

            case 'Y':
                set_yellow();
                putchar(str[i]);
                break;
            
            default:
                color_reset();
                putchar(str[i]);
                break;
        }
    }
    color_reset();
}

bool victoria_verificar(char *flags) {
    size_t l = strlen(flags);
    for(size_t i = 0; i < l; i++)
        if(flags[i] != 'G')
            return false;

    return true;
}
