#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "calc_helper.h"
#include "pila.h"
#include "cola.h"
#include "strutil.h"

#define MAX_STR 1429496729600

bool conversor(char* linea);
void print_output(cola_t*);
size_t tok_prec(struct calc_token* t);

int main(void) {
    char* linea = NULL;
	size_t n = 0;
	while (getline(&linea, &n, stdin) != -1)
		if (!conversor(linea))
            return 1;
	free(linea);
	return 0;
}

bool conversor(char* linea) {
    char** strv = infix_split(linea);
    if (!strv) return false;
    struct calc_token *t = calloc(1, sizeof(struct calc_token));
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
                free(t);
                free_strv(strv);
                return false;
    }
    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], t)) {
            break;
        }
        else if (t->type == TOK_NUM) {
            struct calc_token* valor = token_copiar(t);
            if (!valor) {
                cola_destruir(output, free);
                pila_destruir(operadores);
                free(t);
                free_strv(strv);
                return false;
            }
            if (!cola_encolar(output, valor)) {
                free(valor);
                cola_destruir(output, free);
                pila_destruir(operadores);
                free(t);
                free_strv(strv);
                return false;
            }
        }
        else if (t->type == TOK_OPER) {     // aca implemente el shunting-yard que esta en wikipedia
            struct calc_token* tope = pila_ver_tope(operadores);
            while (tope && ((tok_prec(tope) > tok_prec(t)) || ((tok_prec(tope) == tok_prec(t)) && (t->oper.asociatividad != ASSOC_RIGHT))) && (t->type != TOK_LPAREN)) {
                if (!cola_encolar(output, pila_desapilar(operadores))) {
                    free(tope);
                    cola_destruir(output, free);
                    pila_destruir(operadores);
                    free(t);
                    free_strv(strv);
                    return false;
                }
                tope = pila_ver_tope(operadores);
            }
            struct calc_token* nuevo_oper = token_copiar(t);
            if (!nuevo_oper) {
                cola_destruir(output, free);
                pila_destruir(operadores);
                free(t);
                free_strv(strv);
                return false;
            }
            pila_apilar(operadores, nuevo_oper);
        }

        else if (t->type == TOK_LPAREN) {   
            struct calc_token* nuevo_oper = token_copiar(t);
            if (!nuevo_oper) {
                cola_destruir(output, free);
                pila_destruir(operadores);
                free(t);
                free_strv(strv);
                return false;
            }
            pila_apilar(operadores, nuevo_oper);
        }

        else if (t->type == TOK_RPAREN) {
            struct calc_token* tope = pila_ver_tope(operadores);
            while (tope && (tope->type != TOK_LPAREN/* && !pila_esta_vacia(operadores)*/)) {
                if (!cola_encolar(output, pila_desapilar(operadores))) {
                        free(tope);
                        cola_destruir(output, free);
                        pila_destruir(operadores);
                        free(t);
                        free_strv(strv);
                        return false;
                }
                tope = pila_ver_tope(operadores);
            }
            tope = pila_desapilar(operadores);
            free(tope);
        }
    }
    while (!pila_esta_vacia(operadores)) {
        if (!cola_encolar(output, pila_desapilar(operadores))) {
            cola_destruir(output, free);
            pila_destruir(operadores);
            free(t);
            free_strv(strv);
            return false;
        }
    }
    print_output(output);
    free(t);
    cola_destruir(output, NULL);
    pila_destruir(operadores);
    free_strv(strv);
    return true;
}

void print_output(cola_t* output) {
    while (!cola_esta_vacia(output)) {
        struct calc_token* out = cola_desencolar(output);
        if (out->type == TOK_NUM) {
            fprintf(stdout, "%ld ", out->value);
        }
        else if (out->type == TOK_OPER) {
            if (out->oper.op == OP_ADD) {
                fprintf(stdout, "+ ");
            }
            else if (out->oper.op == OP_SUB) {
                fprintf(stdout, "- ");
            }
            else if (out->oper.op == OP_MUL) {
                fprintf(stdout, "* ");
            }
            else if (out->oper.op == OP_DIV) {
                fprintf(stdout, "/ ");
            }
            else if (out->oper.op == OP_POW) {
                fprintf(stdout, "^ ");
            }
            else if (out->oper.op == OP_LOG) {
                fprintf(stdout, "log ");
            }
            else if (out->oper.op == OP_RAIZ) {
                fprintf(stdout, "sqrt ");
            }
            else if (out->oper.op == OP_TERN) {
                fprintf(stdout, "? ");
            }
        }
        free(out);
    }
    fprintf(stdout, "\n");
    return;
}

size_t tok_prec(struct calc_token* t) {
    return t->oper.precedencia;
}