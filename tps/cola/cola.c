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
    return !cola->prim;
}

bool cola_encolar(cola_t *cola, void *valor) {
    nodo_t *n = nodo_crear(NULL);
    if (n == NULL) return false;
    if (cola->prim == NULL) {
        cola->prim = n;
        cola->ult = n;
    } else {
        cola->ult->sig = n;
        cola->ult = n;
    }
    return true;
}

void *cola_ver_primero(const cola_t *cola) {
    if (cola_esta_vacia(cola)) return NULL;
    return cola->prim->dato;
}

// Saca el primer elemento de la cola. Si la cola tiene elementos, se quita el
// primero de la cola, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la cola fue creada.
// Post: se devolvió el valor del primer elemento anterior, la cola
// contiene un elemento menos, si la cola no estaba vacía.
void *cola_desencolar(cola_t *cola) {
    if (cola_esta_vacia(cola)) return NULL;
    nodo_t *pre = cola->prim;
    cola->prim = pre->sig;
    void *dato = pre->dato;
    nodo_destruir(pre);
    return dato;
}   
