#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "calc_helper.h"
#include "pila.h"
#include "strutil.h"

#define MAX_STR 100

bool calculadora(char* linea);
bool operar(pilanum_t* p, struct calc_oper oper, size_t nums);
bool oper_suma(pilanum_t* p);
bool oper_resta(pilanum_t* p);
bool oper_multi(pilanum_t* p);
bool oper_div(pilanum_t* p);
bool oper_pot(pilanum_t* p);
bool oper_log(pilanum_t* p);
bool oper_raiz(pilanum_t* p);
bool oper_tern(pilanum_t* p);

int main(void) {
    char aux[MAX_STR];
    while (fgets(aux, MAX_STR, stdin)) {
        if (!calculadora(aux)) {
            fprintf(stderr, "ERROR\n");
        }
    }
    return 0;
}

bool calculadora(char* linea) {
    size_t nums = 0;
    char** strv = dc_split(linea);
    if (!strv) return false;
    struct calc_token *t = malloc(sizeof(struct calc_token));
    if (!t) return false;
    pilanum_t* pila = pilanum_crear();
    if (!pila) {
        free(strv);
        return false;
    }
    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], t)) {
            break;
        }
        else if (t->type == TOK_NUM) {
            apilar_num(pila, t->value);
            nums++;
        }
        else if (t->type == TOK_OPER) {
            if (!operar(pila, t->oper, nums)) {
                free_strv(strv);
                free(t);
                pilanum_destruir(pila);
                return false;
            }
        }
        else if (t->type == TOK_LPAREN || t->type == TOK_RPAREN) {
            // como no lo implemente, directamente tiro ERROR en caso de parentesis
            return false;
        }
    }
    calc_num* res = malloc(sizeof(calc_num));
    if (!res) {     // esto creo que me quedo medio "codigo repetido", pero no se me ocurrio otra cosa la verdad. 
        free_strv(strv);
        free(t);
        pilanum_destruir(pila);
        return false;
    }
    if (!desapilar_num(pila, res)) {
        free_strv(strv);
        free(t);
        pilanum_destruir(pila);
        free(res);
        return false;
    }
    if (!pila_esta_vacia(pila)) {
        free_strv(strv);
        free(t);
        free(res);
        pilanum_destruir(pila);
        return false;
    }
    fprintf(stdout, "%ld\n", *res);
    free_strv(strv);
    free(t);
    free(res);
    pilanum_destruir(pila);
    return true;
}

bool operar(pilanum_t* p, struct calc_oper oper, size_t nums) {
    if (oper.op == OP_ADD) {
        if (nums < oper.operandos) return false;
        oper_suma(p);
        return true;
    }
    else if (oper.op == OP_SUB) {
        if (nums < oper.operandos) return false;
        oper_resta(p);
        return true;
    }
    else if (oper.op == OP_MUL) {
        if (nums < oper.operandos) return false;
        oper_multi(p);
        return true;
    }
    else if (oper.op == OP_DIV) {
        if (nums < oper.operandos) return false;
        oper_div(p);
        return true;
    }
    else if (oper.op == OP_POW) {
        if (nums < oper.operandos) return false;
        oper_pot(p);
        return true;
    }
    else if (oper.op == OP_LOG) {
        if (nums < oper.operandos) return false;
        oper_log(p);
        return true;
    }
    else if (oper.op == OP_LOG) {
        if (nums < oper.operandos) return false;
        oper_log(p);
        return true;
    }
    else if (oper.op == OP_RAIZ) {
        if (nums < oper.operandos) return false;
        oper_raiz(p);
        return true;
    }
    else if (oper.op == OP_TERN) {
        if (nums < oper.operandos) return false;
        oper_tern(p);
        return true;
    }
    return false;
}

bool oper_suma(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    apilar_num(p, a + b);
    return true;
}

bool oper_resta(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    apilar_num(p, a - b);
    return true;
}

bool oper_multi(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    apilar_num(p, a * b);
    return true;
}

bool oper_div(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    if (!b) return false;
    apilar_num(p, a / b);
    return true;
}

bool oper_pot(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    if (b < 0) return false;
    apilar_num(p, (calc_num)pow((double)a, (double)b));
    return true;
}

bool oper_log(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    if (b < 2) return false;
    apilar_num(p, (calc_num)(log((double)a) / log((double)b)));
    return true;
}

bool oper_raiz(pilanum_t* p) {
    calc_num a;
    if (!desapilar_num(p, &a)) return false;
    if (a < 0) return false;
    apilar_num(p, (calc_num)sqrt((double)a));
    return true;
}

bool oper_tern(pilanum_t* p) {
    calc_num a, b, c;

    if (!desapilar_num(p, &c)) return false;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    apilar_num(p, a ? b : c);
    return true;
}