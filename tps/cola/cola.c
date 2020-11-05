#include "cola.h"
#include <stdlib.h>

typedef struct nodo {
    void *dato;
    struct nodo *sig;
} nodo_t;

static nodo_t *nodo_crear(void *dato){
    nodo_t *n = malloc(sizeof(nodo_t));
    if (n == NULL) return NULL;
    n->dato = dato;
    n->sig = NULL;
    return n;
}

static void nodo_destruir(nodo_t *nodo){
    free(nodo);
}

struct cola {
    nodo_t *prim;
    nodo_t *ult;
};

cola_t *cola_crear(void) {
    cola_t *c = malloc(sizeof(cola_t));
    if (c == NULL) return NULL;
    c->prim = NULL;
    c->ult = NULL;
    return c;
}

bool cola_esta_vacia(const cola_t *cola) {
    return !cola->prim && !cola->ult;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *n = nodo_crear(valor);
    if (!n) return false;
    if (cola_esta_vacia(cola))
        cola->prim = n;
    else
        cola->ult->sig = n;

    cola->ult = n;
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) return NULL;
    return cola->prim->dato;
}

void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) return NULL;
    nodo_t *pre = cola->prim;
    cola->prim = pre->sig;
    if (!cola->prim)
        cola->ult = NULL;
    void *dato = pre->dato;
    nodo_destruir(pre);
    return dato;
}   

void cola_destruir(cola_t *cola, void (*destruir_dato)(void *)) {
    nodo_t *actual = cola->prim;
    while (actual) {
        actual = actual->sig;
        void* dato = cola_desencolar(cola);
        if (destruir_dato != NULL)
            destruir_dato(dato);
    }
    free(cola);
}