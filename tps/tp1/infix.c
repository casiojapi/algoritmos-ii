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
bool imprimir_cola(cola_t* output, pila_t* operadores);
size_t obtener_precedencia(struct calc_token* t);

bool creacion_de_estructuras(char* linea, char** strv, struct calc_token *t, cola_t* output, pila_t* operadores);
bool condicion_de_corte(struct calc_token* t, struct calc_token* tope);
void destruir_token(struct calc_token* t);
void destruir_conversor(struct calc_token* t, cola_t* output, pila_t* operadores, char** strv, struct calc_token* tope, struct calc_token* valor);

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
        destruir_conversor(t, NULL, NULL, strv, NULL, NULL);
        return false;
    }
    pila_t* operadores = pila_crear();
    if (!operadores) {
                destruir_conversor(t, output, NULL, strv, NULL, NULL);
                return false;
    }

    for (size_t i = 0; strv[i]; i++) {
        if (!calc_parse(strv[i], t, true)) {
            break;
        }
        else if (t->type == TOK_NUM) {
            struct calc_token* valor = token_copiar(t);
            if (!valor) {
                destruir_conversor(t, output, operadores, strv, NULL, NULL);
                return false;
            }
            if (!cola_encolar(output, valor)) {
                destruir_conversor(t, output, operadores, strv, NULL, valor);
                return false;
            }
        }
        else if (t->type == TOK_OPER) {     // aca implemente el shunting-yard que esta en wikipedia
            struct calc_token* tope = pila_ver_tope(operadores);
            while (tope && condicion_de_corte(t, tope) && (t->type != TOK_LPAREN)) {
                if (!cola_encolar(output, pila_desapilar(operadores))) {
                    destruir_conversor(t, output, operadores, strv, tope, NULL);
                    return false;
                }
                tope = pila_ver_tope(operadores);
            }
            struct calc_token* nuevo_oper = token_copiar(t);
            if (!nuevo_oper) {
                destruir_conversor(t, output, operadores, strv, NULL, NULL);
                return false;
            }
            pila_apilar(operadores, nuevo_oper);
        }
        else if (t->type == TOK_LPAREN) {   
            struct calc_token* nuevo_oper = token_copiar(t);
            if (!nuevo_oper) {
                destruir_conversor(t, output, operadores, strv, NULL, NULL);
                return false;
            }
            pila_apilar(operadores, nuevo_oper);
        }
        else if (t->type == TOK_RPAREN) {
            struct calc_token* tope = pila_ver_tope(operadores);
            while (tope && (tope->type != TOK_LPAREN)) {
                if (!cola_encolar(output, pila_desapilar(operadores))) {
                        destruir_conversor(t, output, operadores, strv, tope, NULL);
                        return false;
                }
                tope = pila_ver_tope(operadores);
            }
            tope = pila_desapilar(operadores);
            destruir_token(tope);
        }
    }
    if (!imprimir_cola(output, operadores)) {
        destruir_conversor(t, output, operadores, strv, NULL, NULL);
        return false;
    }
    destruir_conversor(NULL, output, operadores, strv, NULL, NULL);
    free(t);
    return true;
}

bool imprimir_cola(cola_t* output, pila_t* operadores) {
    while (!pila_esta_vacia(operadores)) {
        if (!cola_encolar(output, pila_desapilar(operadores)))
            return false;
    }
    while (!cola_esta_vacia(output)) {
        struct calc_token* out = cola_desencolar(output);
        if (out->type == TOK_NUM) {
            fprintf(stdout, "%ld ", out->value);
            free(out);
        }
        else if (out->type == TOK_OPER) {
            
            if (out->oper.texto) {
                fprintf(stdout, "%s", out->oper.texto);
                destruir_token(out);
            }
            else
                free(out);
        }
    }
    fprintf(stdout, "\n");
    return true;
}

size_t obtener_precedencia(struct calc_token* t) {
    if (t->type == TOK_OPER) 
        return t->oper.precedencia;
    return 0;
}

void destruir_token_wrapper(void* dato) {
    destruir_token((struct calc_token*) dato);
}

void destruir_conversor(struct calc_token* t, cola_t* output, pila_t* operadores, char** strv, struct calc_token* tope, struct calc_token* valor) {
    if (t)
        destruir_token(t);
    if (output)
        cola_destruir(output, destruir_token_wrapper);
    if (operadores)
        pila_destruir(operadores);
    if (strv)
        free_strv(strv);
    if (tope)
        destruir_token(tope);
    if (valor)
        destruir_token(valor);
    return;
}

bool condicion_de_corte(struct calc_token* t, struct calc_token* tope) {
    bool precedencia = (obtener_precedencia(tope) > obtener_precedencia(t)) || (obtener_precedencia(tope) == obtener_precedencia(t));
    return precedencia && (t->oper.asociatividad != ASSOC_RIGHT);
}

