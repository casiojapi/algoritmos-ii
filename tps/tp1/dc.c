#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "calc_helper.h"
#include "pila.h"
#include "strutil.h"

bool calculadora(char* linea);
bool operar(pilanum_t* p, struct calc_oper oper, size_t* nums);
bool oper_suma(pilanum_t* p);
bool oper_resta(pilanum_t* p);
bool oper_multi(pilanum_t* p);
bool oper_div(pilanum_t* p);
bool oper_pot(pilanum_t* p);
bool oper_log(pilanum_t* p);
bool oper_raiz(pilanum_t* p);
bool oper_tern(pilanum_t* p);

void liberar_calculadora_error(char** strv, struct calc_token* token, pilanum_t* pila, calc_num* res, bool error);
bool imprimir_resultado(char** strv, struct calc_token* t, pilanum_t* pila, size_t nums);
bool desapilar_operandos(pilanum_t* p, calc_num* a, calc_num* b, calc_num* c);

int main(void) {
    char* linea = NULL;
	size_t n = 0;
	while (getline(&linea, &n, stdin) != -1) {
		if (!calculadora(linea)) {
            free(linea);
            return 1;
        }
    }
    free(linea);
	return 0;
}

void liberar_calculadora_error(char** strv, struct calc_token* token, pilanum_t* pila, calc_num* res, bool error) {
    if (error)
        fprintf(stdout, "ERROR\n");
    if (strv)
        free_strv(strv);
    if (token)
        free(token);
    if (pila)
        pilanum_destruir(pila);
    if (res)
        free(res);
    return;
}

bool imprimir_resultado(char** strv, struct calc_token* t, pilanum_t* pila, size_t nums) {
    calc_num* res = malloc(sizeof(calc_num));
    if (!res) {
        liberar_calculadora_error(strv, t, pila, NULL, true);
        return false;
    }
    if ((nums != 1) /*|| (nums_glob != nums_req)*/) {
        liberar_calculadora_error(strv, t, pila, res, true);
        return true;
    }
    if (!desapilar_num(pila, res)) {
        liberar_calculadora_error(strv, t, pila, res, true);
        return true;
    }
    if (!pila_esta_vacia(pila)) {
        liberar_calculadora_error(strv, t, pila, res, true);
        return true;
    }
    fprintf(stdout, "%ld\n", *res);
    liberar_calculadora_error(strv, t, pila, res, false);
    return true;
}

bool calculadora(char* linea) {
    size_t nums = 0;
    char** strv = dc_split(linea);
    if (!strv) return false;
    struct calc_token *t = malloc(sizeof(struct calc_token));
    if (!t) {
        liberar_calculadora_error(strv, t, NULL, NULL, false);
        return false;
    }
    pilanum_t* pila = pilanum_crear();
    if (!pila) {
        liberar_calculadora_error(strv, t, NULL, NULL, true);
        return false;
    }
    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], t, false)) {
            liberar_calculadora_error(strv, t, pila, NULL, true);
            return true;
        }
        else if (t->type == TOK_NUM) {
            apilar_num(pila, t->value);
            nums++;
            //nums_glob++;
        }
        else if (t->type == TOK_OPER) {
            if (nums < t->oper.operandos || !operar(pila, t->oper, &nums)) {
                liberar_calculadora_error(strv, t, pila, NULL, true);
                return true;
            }
            else
                nums -= t->oper.operandos - 1;
        }
        else {
            liberar_calculadora_error(strv, t, pila, NULL, true);
            return true;
        }
    }
    return imprimir_resultado(strv, t, pila, nums);
}

bool operar(pilanum_t* p, struct calc_oper oper, size_t* nums) {
    if (oper.op == OP_ADD)
        return oper_suma(p);
    else if (oper.op == OP_SUB)
        return oper_resta(p);
    else if (oper.op == OP_MUL)
        return oper_multi(p);
    else if (oper.op == OP_DIV)
        return oper_div(p);
    else if (oper.op == OP_POW)
        return oper_pot(p);
    else if (oper.op == OP_LOG)
        return oper_log(p);
    else if (oper.op == OP_RAIZ)
        return oper_raiz(p);
    else if (oper.op == OP_TERN)
        return oper_tern(p);
    return false;
}

bool oper_suma(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_operandos(p, &a, &b, NULL)) return false;
    apilar_num(p, a + b);
    return true;
}

bool oper_resta(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_operandos(p, &a, &b, NULL)) return false;
    apilar_num(p, a - b);
    return true;
}

bool oper_multi(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_operandos(p, &a, &b, NULL)) return false;
    apilar_num(p, a * b);
    return true;
}

bool oper_div(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_operandos(p, &a, &b, NULL)) return false;
    if (b == 0) return false;
    apilar_num(p, a / b);
    return true;
}

bool oper_pot(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_operandos(p, &a, &b, NULL)) return false;
    if (b < 0) return false;
    apilar_num(p, floor(pow((double)a, (double)b)));
    return true;
}

bool oper_log(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_operandos(p, &a, &b, NULL)) return false;
    if (b < 2) return false;
    apilar_num(p, (calc_num)(log((double)a) / log((double)b)));
    return true;
}

bool oper_raiz(pilanum_t* p) {
    calc_num a;
    if (!desapilar_num(p, &a)) return false;
    if (a < 0 ) return false;
    apilar_num(p, floor(sqrt((double)a)));
    return true;
}

bool oper_tern(pilanum_t* p) {
    calc_num a, b, c;
    if (!desapilar_operandos(p, &a, &b, &c)) return false;
    apilar_num(p, a ? b : c);
    return true;
}

bool desapilar_operandos(pilanum_t* p, calc_num* a, calc_num* b, calc_num* c) {
    if (c)
        if (!desapilar_num(p, c)) return false;
    if (b)
        if (!desapilar_num(p, b)) return false;
    if (a)
        if (!desapilar_num(p, a)) return false;
    return true;
}