#include "pila.h"

#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */

#define SIZE_BASE 10
#define CTE_REALLOC 2

struct pila {
    void **datos;
    size_t cantidad;   // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

pila_t *pila_crear(void){
    pila_t *p = malloc(sizeof(pila_t));
    if (p == NULL) return NULL;
    p->datos = malloc(sizeof(void *) * SIZE_BASE);
    if (p->datos == NULL) {
        free(p);
        return NULL;
    }
    p->cantidad = 0;
    p->capacidad = SIZE_BASE;
    return p;
}

void pila_destruir(pila_t *pila){
    for (size_t i = 0; i < pila->cantidad; i++)
        free(pila->datos[i]);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
    return (pila->cantidad == 0) ? true : false;
}

bool pila_apilar(pila_t *pila, void *valor){
    if (pila->cantidad >= pila->capacidad){
        void *aux = realloc(pila->datos, sizeof(void *) * pila->capacidad * CTE_REALLOC);
        if (aux == NULL) return false;
        pila->datos = aux;
        pila->capacidad *= CTE_REALLOC;
    }
    pila->datos[pila->cantidad++] = valor;
    return true;
}

void *pila_ver_tope(const pila_t *pila){
    if (pila->capacidad == 0) return NULL;
    return pila->datos[pila->capacidad];
}

void *pila_desapilar(pila_t *pila){
    if (pila->cantidad == 0) return NULL;
    return pila->datos[pila->capacidad--];
}