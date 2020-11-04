#include "lista.h"
#include <stdlib.h>

//PRIMITIVAS TDA LISTA

typedef struct nodo {
    void* dato;
    struct nodo* prox;
} nodo_t;

static nodo_t *nodo_crear(void *dato, nodo_t* prox){
    nodo_t *n = malloc(sizeof(nodo_t));
    if (!n) return NULL;
    n->dato = dato;
    n->prox = prox;
    return n;
}

static void nodo_destruir(nodo_t *nodo){
    free(nodo);
}
typedef struct lista {
    nodo_t* prim;
    nodo_t* ult;
    size_t largo;
} lista_t;


lista_t *lista_crear(void){
    lista_t* l = malloc(sizeof(lista_t));
    if (!l) return NULL;
    l->prim = NULL;
    l->ult = NULL;
    l->largo = 0;
    return l;
}

bool lista_esta_vacia(const lista_t *lista){
    return !lista->largo;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* n = nodo_crear(dato, lista->prim);
    if (!n) return false;

    lista->prim = n;

    if (lista_esta_vacia(lista))
        lista->ult = n;

    lista->largo++;
    return true;

}

bool lista_insertar_ultimo(lista_t *lista, void *dato) {
    nodo_t* n = nodo_crear(dato, NULL);
    if (!n) return false;

    if (lista_esta_vacia(lista)){
        lista->prim = n;
        lista->ult = n;
        lista->largo++;
        return true;
    }
    lista->ult->prox = n;
    lista->ult = n;
    lista->largo++;
    return true;
}

void *lista_borrar_primero(lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;

    void *dato = lista->prim->dato;
    nodo_t* viejo = lista->prim;
    lista->prim = viejo->prox;
    nodo_destruir(viejo);
    lista->largo--;
    if (!lista_largo(lista)) // if largo es 0, o sea que originalmente tenia 1 elemento.
        lista->ult = NULL;
    return dato;

}

void *lista_ver_primero(const lista_t *lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista) {
    if (lista_esta_vacia(lista)) return NULL;
    return lista->ult->dato;
}

size_t lista_largo(const lista_t *lista) {
    return lista->largo;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    if (lista_esta_vacia(lista)) {
        free(lista);
        return;
    }
    nodo_t* actual = lista->prim;
    nodo_t* sig = actual;
    while (actual) {
        sig = actual->prox;
        if (destruir_dato)
            destruir_dato(actual->dato);
        free(actual);
        actual = sig;
    }
    free(lista);
}

// PRIMITIVAS ITERADOR INTERNO

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
    nodo_t* actual = lista->prim;
    while (actual) {
        if (!visitar(actual->dato, extra))
            break;
        actual = actual->prox;
    }
}

// PRIMIRIVAS INTERADOR EXTERNO

struct lista_iter {
    lista_t* lista;
    nodo_t* act;
    nodo_t* ant;
};


lista_iter_t *lista_iter_crear(lista_t *lista) {
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (!iter) return NULL;
    iter->lista = lista;
    iter->act = lista->prim;
    iter->ant = NULL;
    return iter;
}


bool lista_iter_avanzar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return false;
    iter->ant = iter->act;
    iter->act = iter->ant->prox;
    return true;
}


void *lista_iter_ver_actual(const lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return NULL;
    return iter->act->dato;
}


bool lista_iter_al_final(const lista_iter_t *iter) {
    return !iter->act;
}

void lista_iter_destruir(lista_iter_t *iter) {
    free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
    nodo_t* nuevo = nodo_crear(dato, iter->act);
    if (!nuevo) return false;

    iter->lista->largo++;

    if (!iter->ant)
        iter->lista->prim = nuevo;

    else 
        iter->ant->prox = nuevo;

    iter->act = nuevo;

    if (lista_iter_al_final(iter))
        iter->lista->ult = nuevo;

    return true;
}


void *lista_iter_borrar(lista_iter_t *iter) {
    if (lista_iter_al_final(iter)) return NULL;
    void* dato = lista_iter_ver_actual(iter);
    iter->lista->largo--;
    
    if (!iter->ant)
        iter->lista->prim = iter->act->prox;
    else
        iter->ant->prox = iter->act->prox;
    
    nodo_t* eliminar = iter->act;
    iter->act = iter->act->prox;
    nodo_destruir(eliminar);
    if (lista_iter_al_final(iter))
        iter->lista->ult = iter->ant;
    return dato;
}