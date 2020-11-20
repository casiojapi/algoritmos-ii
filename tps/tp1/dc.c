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

bool calculadora(char* linea) {
    size_t nums = 0, nums_glob = 0, nums_req = 1;
    char** strv = dc_split(linea);
    if (!strv) return false;
    struct calc_token *t = malloc(sizeof(struct calc_token));
    if (!t) {
        fprintf(stdout, "ERROR\n");
        free_strv(strv);
        return false;
    }
    pilanum_t* pila = pilanum_crear();
    if (!pila) {
        fprintf(stdout, "ERROR\n");
        free_strv(strv);
        free(t);
        return false;
    }
    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], t)) {
            fprintf(stdout, "ERROR\n");
            free_strv(strv);
            free(t);
            pilanum_destruir(pila);
            return true;
        }
        else if (t->type == TOK_NUM) {
            apilar_num(pila, t->value);
            nums++;
            nums_glob++;
        }
        else if (t->type == TOK_OPER) {
            if (!operar(pila, t->oper, &nums)) {
                fprintf(stdout, "ERROR\n");
                free_strv(strv);
                free(t);
                pilanum_destruir(pila);
                return true;
            }
            else {
                nums -= t->oper.operandos - 1;
                nums_req += t->oper.operandos - 1;
            }
        }
        else {
            fprintf(stdout, "ERROR\n");
            free_strv(strv);
            free(t);
            pilanum_destruir(pila);
            return true;
        }
    }
    calc_num* res = malloc(sizeof(calc_num));
    if (!res) {     // esto creo que me quedo medio "codigo repetido", pero no se me ocurrio otra cosa la verdad.
        fprintf(stdout, "ERROR\n");
        free_strv(strv);
        free(t);
        pilanum_destruir(pila);
        return false;
    }
    //printf("%zd, %zd\n", nums_glob, nums_req);
    if ((nums != 1) || (nums_glob != nums_req)) {
        fprintf(stdout, "ERROR\n");
        free_strv(strv);
        free(t);
        pilanum_destruir(pila);
        free(res);
        return true;
    }

    if (!desapilar_num(pila, res)) {
        fprintf(stdout, "ERROR\n");
        free_strv(strv);
        free(t);
        pilanum_destruir(pila);
        free(res);
        return true;
    }
    if (!pila_esta_vacia(pila)) {
        fprintf(stdout, "ERROR\n");
        free_strv(strv);
        free(t);
        free(res);
        pilanum_destruir(pila);
        return true;
    }
    fprintf(stdout, "%ld\n", *res);
    free_strv(strv);
    free(t);
    free(res);
    pilanum_destruir(pila);
    return true;
}

bool operar(pilanum_t* p, struct calc_oper oper, size_t* nums) {
    if (oper.op == OP_ADD) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_suma(p);
    }
    else if (oper.op == OP_SUB) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_resta(p);
    }
    else if (oper.op == OP_MUL) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_multi(p);
    }
    else if (oper.op == OP_DIV) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_div(p);
    }
    else if (oper.op == OP_POW) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_pot(p);
    }
    else if (oper.op == OP_LOG) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_log(p);
    }
    else if (oper.op == OP_RAIZ) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_raiz(p);
    }
    else if (oper.op == OP_TERN) {
        if (*nums < oper.operandos) {
            return false;
        }
        return oper_tern(p);
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
    if (b == 0) return false;
    apilar_num(p, a / b);
    return true;
}

bool oper_pot(pilanum_t* p) {
    calc_num a, b;
    if (!desapilar_num(p, &b)) return false;
    if (!desapilar_num(p, &a)) return false;
    if (b < 0) return false;
    apilar_num(p, floor(pow((double)a, (double)b)));
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
    if (a < 0 /*|| a == 2*/) return false;
    apilar_num(p, floor(sqrt((double)a)));
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