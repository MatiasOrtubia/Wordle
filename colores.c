#include <stdio.h>
#include "colores.h"
/*
void set_black(void) {
    printf("\033[0;30m");
}

void set_red(void) {
    printf("\033[0;31m"); 
}
*/
void set_green(void) {
    printf("\033[1;32m");
}

void set_yellow(void) {
    printf("\033[1;33m");
}
/*
void set_blue(void) {
    printf("\033[0;34m");
}

void set_purple(void) {
    printf("\033[0;35m");
}

void set_cyan(void) {
    printf("\033[0;36m");
}
*/
void set_white(void) {
    printf("\033[0;37m");
}

void color_reset(void) {
    printf("\033[0m");
}
