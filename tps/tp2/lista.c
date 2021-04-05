#include "lista.h"
#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                    DEFINICION STRUCT NODO
 * *****************************************************************/
typedef struct nodo{
    void* dato;
    struct nodo* prox;
} nodo_t;
/* ******************************************************************
 *                    PRIMITIVAS DEL NODO
 * *****************************************************************/

 //Crea un nodo. Recibe un puntero a un valor.
 //Post: Devuelve un nodo con un dato (*valor) y apunta a NULL. En el caso de que falle, deuvelve NULL.
nodo_t *nodo_crear(void *valor){
    nodo_t *nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL){
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;
    return nodo;
}

/* ******************************************************************
 *                    DEFINICION STRUCT LISTA
 * *****************************************************************/
struct lista{
    nodo_t *prim;
    nodo_t *ult;
    size_t largo;
};

/* ******************************************************************
 *                    PRIMITIVA DE LA LISTA
 * *****************************************************************/
lista_t *lista_crear(void){
    lista_t *lista = malloc(sizeof(lista_t));
    if(!lista){
        return NULL;
    }
    lista->prim = NULL;
    lista->ult= NULL;
    lista->largo = 0;
    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return !lista->largo;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t *nuevo_nodo = nodo_crear(dato);
    if(!nuevo_nodo){
        return false;
    }
    if(lista_esta_vacia(lista)){
        lista->ult = nuevo_nodo;
    }
    else{
        nuevo_nodo->prox = lista->prim;
    }
    lista->prim = nuevo_nodo;
    lista->largo += 1;
    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t *nuevo_nodo = nodo_crear(dato);
    if(!nuevo_nodo){
        return false;
    }
    if(lista_esta_vacia(lista)){
        lista->prim = nuevo_nodo;
    }
    else{
        lista->ult->prox = nuevo_nodo;
    }
    lista->ult = nuevo_nodo;
    lista->largo += 1;
    return true;
}

void *lista_borrar_primero(lista_t *lista){
    if(lista_esta_vacia(lista)){
        return NULL;
    }
    void *valor = lista->prim->dato;
    nodo_t *nodo_aux = lista->prim;
    lista->prim = nodo_aux->prox;
    lista->largo -= 1;
    if(lista_esta_vacia(lista)){
        lista->ult= NULL;
    }
    free(nodo_aux);
    return valor;
}

void *lista_ver_primero(const lista_t *lista){
    if(lista_esta_vacia(lista)){
        return NULL;
    }
    return lista->prim->dato;
}

void *lista_ver_ultimo(const lista_t* lista){
    if(lista_esta_vacia(lista)){
        return NULL;
    }
    return lista->ult->dato;
}

void lista_destruir(lista_t *lista, void (*destruir_dato)(void *)){
    while(!lista_esta_vacia(lista)){
        if(destruir_dato == NULL){
            lista_borrar_primero(lista);
            continue;
        }
        void *valor = lista_borrar_primero(lista);
        destruir_dato(valor);
    }
    free(lista);
}

size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

/* ******************************************************************
 *                    PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

 void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
    nodo_t *actual = lista->prim;
    while(actual){
        if(!visitar(actual->dato, extra)){
            break;
        }
        actual = actual->prox;
    }
}

/* ******************************************************************
 *                    PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/
struct lista_iter{
    nodo_t *actual;
    nodo_t *anterior;
    lista_t *lista;
};

lista_iter_t *lista_iter_crear(lista_t *lista){
    lista_iter_t *iter = malloc(sizeof(lista_iter_t));
    if (!iter){
        return NULL;
    }
    iter->actual = lista->prim;
    iter->anterior = NULL;
    iter->lista = lista;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t *iter){
    if(!lista_iter_al_final(iter)){
        iter->anterior = iter->actual;
        iter->actual = iter->actual->prox;
        return true;
    }
    return false;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(lista_iter_al_final(iter)){
        return NULL;
    }
    return iter->actual->dato;
}

bool lista_iter_al_final(const lista_iter_t *iter){
    return !iter->actual;
}

void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t *iter, void *dato){
    nodo_t *nuevo_nodo = nodo_crear(dato);
    if(!nuevo_nodo){
        return false;
    }
    nuevo_nodo->prox = iter->actual;
    if(iter->anterior){
        iter->anterior->prox = nuevo_nodo;
    }
    else{
        iter->lista->prim = nuevo_nodo;
    }
    if(lista_iter_al_final(iter)){
        iter->lista->ult = nuevo_nodo;
    }
    iter->actual = nuevo_nodo;
    iter->lista->largo += 1;
    return true;
}
void *lista_iter_borrar(lista_iter_t *iter){
    if(lista_iter_al_final(iter)){
        return NULL;
    }
    nodo_t *nodo_aux = iter->actual;
    void *valor = nodo_aux->dato;
    iter->actual = iter->actual->prox;
    if(iter->anterior){
        iter->anterior->prox = iter->actual;
    }
    else{
        iter->lista->prim = nodo_aux->prox;
    }
    if(!nodo_aux->prox){
        iter->lista->ult = iter->anterior;
    }
    free(nodo_aux);
    iter->lista->largo -= 1;
    return valor;
}
