#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "calc_helper.h"
#include "pila.h"

#define MAX_STR 100

bool calculadora(char* linea);

int main(void) {
    char aux[MAX_STR];
    while (fgets(aux, MAX_STR, stdin)) {
        if (!calculadora(aux)) {
            fprintf(stderr, "ERROR\n");
        }
    }
    return 0;
}

void operar(pilanum_t* p, enum oper_type oper)

bool calculadora(char* linea) {
    char** strv = dc_split(linea);
    if (!strv) return false;
    struct calc_token t;
    pilanum_t* pila = pilanum_crear();
    if (!pila) {
        free(strv);
        return false;
    }
    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], &t)) {
            free(strv);
            return false;
        }
        else if (t.type == TOK_NUM) {
            apilar_num(pila, t.value);
        }
        else if ()
    }
}