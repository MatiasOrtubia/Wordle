#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "palabra.h"
#include "wordle.h"
#include "colores.h"

#define MAX_PALABRAS 100
#define MAX_LETRAS 20
#define MAX_TURNOS 6
#define CANT_LETRAS 5

struct lista_palabras {
    palabra_t **p;
    size_t n;
};

typedef struct lista_palabras lista_palabras_t;

/* Obtiene una cadena de caracteres desde stdin, de tamaño máximo len, y la guarda en str. */
/* Devuelve true si no hay errores, y false si falla */
bool input(char *str, size_t len);

bool input(char *str, size_t len) {
    if(fgets(str, len, stdin) != NULL) {
        if(!strchr(str, '\n')) {
            int c;
            while(((c = getchar()) != EOF) && (c != '\n'));

            if(c == EOF) return false;
        }
    
        else {
            str[strlen(str) - 1] = '\0';
        }
    }
    return true;
}
    

int main(void) {
    /* Apertura de archivos */
    FILE *fi = fopen("palabras.txt", "rt");
    if(fi == NULL) {
        perror("No se pudo abrir el archivo.");
        return 1;
    }
    
    /* Creacion de la lista */
    lista_palabras_t *lista = malloc(sizeof(lista_palabras_t *));
    if(lista == NULL) {
        perror("Memoria insuficiente.\n");
        fclose(fi);
        return 1;
    }

    lista->p = calloc(MAX_PALABRAS, sizeof(palabra_t **));
    if(lista->p == NULL) {
        perror("Memoria insuficiente.\n");
        fclose(fi);
    return 1;
    }

    /* Lectura del archivo y carga de los datos*/
    char palabra_temp[MAX_LETRAS];
    size_t i = 0;
    lista->n = 0;
    while(fscanf(fi, "%s", palabra_temp) != EOF && i < MAX_PALABRAS) {
        lista->p[i] = palabra_crear(palabra_temp, strlen(palabra_temp));
        if(lista->p[i] == NULL) {
            perror("Memoria insuficiente.\n");
            fclose(fi);
            return 1;
        }
        (lista->n)++;
        i++;
    }

    fclose(fi);


    /* Se elije una palabra aleatoria */
    srand(time(NULL));
    int n_rand = rand() % lista->n;

#ifdef DEBUG
    printf("La palabra es: %s\n", palabra_obtener_palabra(lista->p[n_rand]));
#endif

    /* El juego */
    /* Se le pide al usuario que ingrese una palabra con la cantidad de letras */
    size_t turno = 1;
    bool victoria = false;
    char *resultado;

    while(turno <= MAX_TURNOS && victoria == false) {
        printf("Turno %zd - ", turno);
        printf("Ingrese una palabra de 5 letras.\n");
        char str[MAX_LETRAS];
        if(input(str, MAX_LETRAS) == false) {
            perror("Error.\n");
            /* Se libera la memoria */
            for(size_t j = 0; j < lista->n; j++)
                palabra_destruir(lista->p[i]);

            free(lista->p);
            free(lista);
            /*
            if(resultado != NULL)
                free(resultado);
            */
            return 1;
        }

        /* Verificacion de longitud */
        if(strlen(str) != CANT_LETRAS)
            continue;
        

        /* Verificar que la palabra este en la lista */

        /* Se compara esa palabra con la palabra a encontrar. */
        resultado = letras_verificar(palabra_obtener_palabra(lista->p[n_rand]), str);
        if(resultado == NULL) {
            perror("Error.\n");
            /* Se libera la memoria */
            for(size_t j = 0; j < lista->n; j++)
                palabra_destruir(lista->p[i]);

            free(lista->p);
            free(lista);

            return 1;
        }

        imprimir_resultado(str, resultado);
        putchar('\n');
        putchar('\n');

        if(victoria_verificar(resultado) == true) 
            victoria = true;

        /* Aca deberia liberar la memoria de resultado creo */

        /* Se pasa al siguiente turno si no se adivino la palabra */
        turno++;
    }

    if(victoria == true)
        printf("Ganaste!\n");
    else {
        printf("Perdiste :(\nLa palabra era \"");
        palabra_mostrar(lista->p[n_rand]);
        printf("\"\n");
    }

    /* Liberacion de memoria */
    for(size_t j = 0; j < lista->n; j++)
        palabra_destruir(lista->p[i]);

    free(lista->p);
    free(lista);
/*
    if(resultado != NULL)
        free(resultado);
*/
    return 0;
}
