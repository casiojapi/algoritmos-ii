#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "calc_helper.h"
#include "pila.h"
#include "cola.h"
#include "strutil.h"

#define MAX_STR 100

bool conversor(char* linea);

int main(void) {
    char aux[MAX_STR];
    while (fgets(aux, MAX_STR, stdin)) {
        if (!conversor(aux)) {
            fprintf(stderr, "ERROR - conversion.\n");
            return 1;
        }
    }
    return 0;
}

bool conversor(char* linea) {
    char** strv = infix_split(linea);
    if (!strv) return false;
    struct calc_token *t = malloc(sizeof(struct calc_token));
    if (!t) {
        free_strv(strv);
        return false;
    }
    cola_t* output = cola_crear();
    if (!output) {
        free(t);
        free_strv(strv);
        return false;
    }
    pila_t* operadores = pila_crear();
    if (!operadores) {
        cola_destruir(output, NULL);
        free(output);
        free(t);
        free_strv(strv);
        return false;
    }
    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], t)) {
            break;
        }
        else if (t->type == TOK_NUM) {
            calc_num* valor = malloc(sizeof(calc_num));
            if (!valor) {
                cola_destruir(output, free);
                pila_destruir(operadores);
                free(operadores);
                free(output);
                free(t);
                free_strv(strv);
                return false;
            }
            *valor = t->value;
            if (!cola_encolar(output, valor)) {
                cola_destruir(output, free);
                pila_destruir(operadores);
                free(operadores);
                free(output);
                free(t);
                free_strv(strv);
                return false;
            }
        }
        else if (t->type == TOK_OPER) {
            while (!pila_esta_vacia(operadores)) {
                struct calc_oper* tope_oper = pila_ver_tope(operadores);
                while ((tope_oper->precedencia > t->oper.precedencia) || (((tope_oper->precedencia == t->oper.precedencia) && (t->oper.asociatividad == ASSOC_LEFT)) && (t->oper.op != OP_LPAREN))) {
                    while (pila_esta_vacia(operadores)) {
                        if (!cola_encolar(output, pila_desapilar(operadores))) {
                            free(tope_oper);
                            cola_destruir(output, free);
                            pila_destruir(operadores);
                            free(operadores);
                            free(output);
                            free(t);
                            free_strv(strv);
                            return false;
                        }
                    }
                }
                
            }
            struct calc_oper* nuevo_oper = malloc(sizeof(struct calc_oper));
            
            if (!nuevo_oper) {
                free(operadores);
                free(output);
                free(t);
                free_strv(strv);
                return false;
            }
            nuevo_oper->asociatividad = t->oper.asociatividad;
            nuevo_oper->op = t->oper.op;
            nuevo_oper->operandos = t->oper.operandos;
            nuevo_oper->precedencia = t->oper.precedencia;
            pila_apilar(operadores, nuevo_oper);
        }
        else if (t->type == TOK_LPAREN) {
            struct calc_oper* nuevo_oper = malloc(sizeof(struct calc_oper));
            if (!nuevo_oper) {
                free(operadores);
                free(output);
                free(t);
                free_strv(strv);
                return false;
            }
            pila_apilar(operadores, nuevo_oper);
        }
    }
    return true;
}
/*
else if the token is a left parenthesis (i.e. "("), then:
        push it onto the operator stack.
    else if the token is a right parenthesis (i.e. ")"), then:
        while the operator at the top of the operator stack is not a left parenthesis:
            pop the operator from the operator stack onto the output queue.
         If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. 
        if there is a left parenthesis at the top of the operator stack, then:
            pop the operator from the operator stack and discard it
  After while loop, if operator stack not null, pop everything to output queue 
if there are no more tokens to read then:
    while there are still operator tokens on the stack:
         If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. 
        pop the operator from the operator stack onto the output queue.
exit.
*/