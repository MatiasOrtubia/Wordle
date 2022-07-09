#include <stdio.h>
#include <string.h>
#include "wordle.h"
#include "colores.h"

#define MAX_PALABRAS 100
#define MAX_LETRAS 100


/* para bsearch
static int cmp(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
} */


/*Para Verificar que la palabra este en la lista */ 
/*palabra_t *wordle_buscar_palabra(palabra_t *palabra, lista_palabras_t *lista) {
    return bsearch(palabra_obtener_palabra(palabra), lista->l, lista->n, sizeof(char *), cmp);
}
*/

/* Para ver si la letra esta en la palabra, y en que posicion */
/* Devuelve un string con 6 caracteres incluido el \0, con banderas G si es correcta la posicion y la letra, Y si solo es correcta la letra, - si la letra no esta incluida. */
char *letras_verificar(char *p_a_adivinar, char *p_ingresada) {
    size_t l = strlen(p_ingresada);
    char *res = calloc(l + 1,  sizeof(char));
    if(res == NULL) return NULL;

    char *flags_a = calloc(l + 1, sizeof(char));
    if(flags_a == NULL) {
        free(res);
        return NULL;
    }

    char *flags_b = calloc(l + 1, sizeof(char));
    if(flags_b == NULL) {
        free(res);
        free(flags_a);
        return NULL;
    }

    /* Primera recorrida para marcar las 'G' */
    for(size_t i = 0; p_ingresada[i] != '\0'; i++) {
        if(p_ingresada[i] == p_a_adivinar[i]) 
            res[i] = 'G';
    }

    /* Segunda recorrida para marcar las 'Y' y los '-' */
    size_t ia = 0;
    size_t ib = 0;

    while(p_ingresada[ib] != '\0') {
        if(res[ib] == 'G') {
            ib++;
            continue;
        }
        ia = 0;
        while(p_a_adivinar[ia] != '\0') {
            if(flags_a[ia] == 'Y' || res[ib] == 'Y' || res[ia] == 'G') {
                ia++;
                continue;
            }
            if(p_a_adivinar[ia] == p_ingresada[ib]) { /* La letra esta en la palabra */
                flags_a[ia] = 'Y';
                res[ib] = 'Y';
                break;
            }
            ia++;
        }
        if(res[ib] != 'Y') {
            res[ib] = '-'; /* Si termina de recorrer y no la encontro, pone el '-' */
        }
        ib++;
    }
    res[ib] = '\0';

    free(flags_a);
    free(flags_b);

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
