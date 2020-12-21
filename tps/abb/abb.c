#define _POSIX_C_SOURCE 200809L //strdup
#include "abb.h"
#include <stdlib.h>
#include <string.h>
#include "pila.h"

//Definición del struct nodo

typedef struct nodo_abb {
    struct nodo_abb *izq;
    struct nodo_abb *der;
    char *clave;
    void *dato;
} nodo_abb_t;

//Definición del struct abb

struct abb {
    nodo_abb_t *raiz;
    size_t cant;
    abb_comparar_clave_t comparar;
    abb_destruir_dato_t destruir;
};

//Funciones auxiliares

bool buscar_clave(nodo_abb_t *nodo_actual, nodo_abb_t **nodo_padre, nodo_abb_t **nodo_buscado, const char *clave, abb_comparar_clave_t cmp);
void abb_destruir_nodos(nodo_abb_t* nodo, abb_destruir_dato_t destruir);
void abb_destruir_nodo_unico(nodo_abb_t* nodo, abb_destruir_dato_t destruir);
void nodo_in_order(nodo_abb_t* nodo, bool visitar(const char *, void *, void *), void *extra, bool *seguir);

//Primitivas ABB

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));
    if(!abb) return NULL;
    abb->raiz = NULL;
    abb->cant = 0;
    abb->comparar = cmp;
    abb->destruir = destruir_dato;
    return abb;
}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato) {
    nodo_abb_t* padre = NULL;
    nodo_abb_t* buscado = NULL;
    if (buscar_clave(arbol->raiz, &padre, &buscado, clave, arbol->comparar)) {
        if (arbol->destruir) {
            arbol->destruir(buscado->dato);
        }
        buscado->dato = dato;
        return true;
    }
    nodo_abb_t *nodo_nuevo = malloc(sizeof(nodo_abb_t));
    if(!nodo_nuevo) return false;
    nodo_nuevo->izq = NULL;
    nodo_nuevo->der = NULL;
    nodo_nuevo->clave = strdup(clave);
    nodo_nuevo->dato = dato;
    if (!arbol->raiz) {
        arbol->raiz = nodo_nuevo;
    }
    else if (arbol->comparar(clave, padre->clave) < 0) {
        padre->izq = nodo_nuevo;
    }
    else {
        padre->der = nodo_nuevo;
    }
    arbol->cant++;
    return true;
}

void *abb_borrar(abb_t *arbol, const char *clave) {
    nodo_abb_t* padre = NULL;
    nodo_abb_t* buscado = NULL;
    if(!buscar_clave(arbol->raiz, &padre, &buscado, clave, arbol->comparar)){
        return NULL;
    }
    void *dato = buscado->dato;
    if (!buscado->izq && !buscado->der) { //Nodo a borrar no tiene hijos(es hoja)
        if(arbol->cant > 1 && padre->izq == buscado){
            padre->izq = NULL;
        }
        else if (arbol->cant > 1){
            padre->der = NULL;
        }
        abb_destruir_nodo_unico(buscado, NULL); //Al borrar una clave no se destruye el dato, se devuelve
        arbol->cant--;
    }
    else if (!buscado->izq || !buscado->der) {     // Borrar nodo con 1 hijo. (puenteo al buscado y lo libero despues)
        nodo_abb_t *buscado_hijo = buscado->izq ? buscado->izq : buscado->der;
        if(padre){
            if (padre->izq == buscado)
                padre->izq = buscado_hijo;
            else
                padre->der = buscado_hijo;
        }
        else{ //El nodo buscado es raiz
            arbol->raiz = buscado_hijo;
        }
        abb_destruir_nodo_unico(buscado, NULL);
        arbol->cant--;
    }
    else {      // Borrar nodo con 2 hijos. Algoritmo: busco reemplazante (inmediato a derecha), guardo su clave y dato, borro el reemplazante, piso clave y valor del buscado
        nodo_abb_t* reemplazante = buscado->der;
        //nodo_abb_t* actual = reemplazante->izq; Si el hijo derecho no tiene hijo izq se rompe
        nodo_abb_t* actual = reemplazante;
        while (actual) {
            reemplazante = actual;
            actual = reemplazante->izq;
        }
        char* clave_reemplazante = strdup(reemplazante->clave);
        void* dato_reemplazante = abb_borrar(arbol, clave_reemplazante);
        free(buscado->clave); //Libero la memoria pedida por strdup en abb_guardar del buscado
        buscado->clave = clave_reemplazante;
        buscado->dato = dato_reemplazante;
    }
    if(!arbol->cant)
        arbol->raiz = NULL;
    return dato;
}


void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* buscado = NULL;
    if(!buscar_clave(arbol->raiz, &padre, &buscado, clave, arbol->comparar)){
        return NULL;
    }
    return buscado->dato;
}

bool abb_pertenece(const abb_t *arbol, const char *clave){
    nodo_abb_t* padre = NULL;
    nodo_abb_t* buscado = NULL;
    return buscar_clave(arbol->raiz, &padre, &buscado, clave, arbol->comparar);
}


size_t abb_cantidad(abb_t *arbol){
    return arbol->cant;
}

void abb_destruir(abb_t *arbol) {
    abb_destruir_nodos(arbol->raiz, arbol->destruir);
    free(arbol);
}

// Funcion auxiliar para abb_destruir. Destruye todos los nodos de un arbol recursivamente, liberando la memoria de su struct, clave y de haber funcion destruir dato, de su dato tambien.
// Post: libero efectivamente la memoria de todos los nodos, sus respectivas claves de un arbol y datos si paso la funcion de destruccion previamente.
void abb_destruir_nodos(nodo_abb_t* nodo, abb_destruir_dato_t destruir) {
    if (!nodo) return;
    abb_destruir_nodos(nodo->der, destruir);
    abb_destruir_nodos(nodo->izq, destruir);
    abb_destruir_nodo_unico(nodo, destruir);
    return;
}

// Funcion auxiliar que destruye un solo nodo.
// Pre: el nodo es valido.
// Post: la memoria asociada al nodo fue liberada.
void abb_destruir_nodo_unico(nodo_abb_t* nodo, abb_destruir_dato_t destruir) {
    if (destruir)
        destruir(nodo->dato);
    free(nodo->clave);
    free(nodo);
    return;
}

//Busca el nodo cuya clave es la ingresada por parámetro. Recibe un nodo inicial, y los punteros padre y buscado. En el caso de encontrar el nodo, se modifica mediante el puntero a nodo_buscado.
//Pertenezca o no la clave al ABB, se devuelve por puntero la referencia al nodo padre del nodo buscado (si no pertenece, ese nodo será su padre).
//Pre: El ABB fue creado.
//Post: Devuelve true si la clave pertenece al abb o false en caso contrario.
bool buscar_clave(nodo_abb_t *nodo_actual, nodo_abb_t **nodo_padre, nodo_abb_t **nodo_buscado, const char *clave, abb_comparar_clave_t cmp){
    if(!nodo_actual) return false;
    int comparar = cmp(clave, nodo_actual->clave);
    if(comparar == 0){
        *nodo_buscado = nodo_actual;
        return true;
    }
    *nodo_padre = nodo_actual;
    if(comparar < 0){
        return buscar_clave(nodo_actual->izq, nodo_padre, nodo_buscado, clave, cmp);
    }
    else{
        return buscar_clave(nodo_actual->der, nodo_padre, nodo_buscado, clave, cmp);
    }
}

// Iterador interno

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra) {
    bool seguir = true;
    nodo_in_order(arbol->raiz, visitar, extra, &seguir);
}

void nodo_in_order(nodo_abb_t* nodo, bool visitar(const char *, void *, void *), void *extra, bool *seguir) {
    if (!nodo || !*seguir) return;
    nodo_in_order(nodo->izq, visitar, extra, seguir);
    if(*seguir){
        if(!visitar(nodo->clave, nodo->dato, extra)){
            *seguir = false;
            return;
        }
        nodo_in_order(nodo->der, visitar, extra, seguir);
    }
    return;
}

// Iterador externo

// funcion auxiliar

void iter_apilar_nodos_izq(abb_iter_t* iter, nodo_abb_t* nodo);

typedef struct abb_iter {
    pila_t* pila;
} abb_iter_t;

abb_iter_t *abb_iter_in_crear(const abb_t *arbol) {     // Apilo raiz
    abb_iter_t* iter = malloc(sizeof(abb_iter_t));
    if (!iter) return NULL;

    iter->pila = pila_crear();
    if (!iter->pila) {
        free(iter);
        return NULL;
    }
    iter_apilar_nodos_izq(iter, arbol->raiz);
    return iter;
}

bool abb_iter_in_avanzar(abb_iter_t *iter) {    // desapilo, apilo hijo derecho e hijo izquierdo del desapilado.
    if (abb_iter_in_al_final(iter)) return false;
    nodo_abb_t* actual = (nodo_abb_t*)pila_desapilar(iter->pila);
    iter_apilar_nodos_izq(iter, actual->der);
    return true;
}
const char *abb_iter_in_ver_actual(const abb_iter_t *iter) {    // veo tope de la pila
    if (abb_iter_in_al_final(iter)) return NULL;
    nodo_abb_t* nodo = pila_ver_tope(iter->pila);
    return nodo->clave;
}
bool abb_iter_in_al_final(const abb_iter_t *iter) { // verifico si la pila esta vacia
    return pila_esta_vacia(iter->pila);
}
void abb_iter_in_destruir(abb_iter_t* iter) { // destruyo la pila y struct iter
    pila_destruir(iter->pila);
    free(iter);
    return;
}

void iter_apilar_nodos_izq(abb_iter_t* iter, nodo_abb_t* actual) {
    if (!actual || !pila_apilar(iter->pila, actual)) return;
    iter_apilar_nodos_izq(iter, actual->izq);
}