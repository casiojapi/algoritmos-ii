// Maximo Santoro. Padron: 105572. DNI: 42822674
// Final - Algoritmos y Programacion II - 5/4/2021

#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "hash.h"
#include "pila.h"

// // ej 1 - pila
// Se cuenta con un TDA Pila implementado con una estructura enlazada. Implementar en C una primitiva que reciba
// dos pilas, P1 y P2, y cree una nueva pila P3 que tenga todos los elementos de P1, seguidos por todos los elementos de
// P2, en tiempo constante. Tanto P1 como P2 deben quedar destruidas.
// Ejemplo: si tenemos P1 = [8; 7; 5] (el tope es 5) y P2 = [4; 1; 6] (el tope es 6), al finalizar el algoritmo P3 = [8;
// 7; 5; 4; 1; 6] (tope 6). Aclaración: Se puede (y debe) definir cómo es la estructura de la pila para poder cumplir
// con lo pedido, siempre manteniendo que sea una estructura enlazada.

typedef struct nodo {
    void* dato;
    struct nodo* sig;
} nodo_t;

typedef struct pila {
    nodo_t* prim;
    nodo_t* ult;
    size_t largo;
} pila_t;

// defino la pila con una estructura enlazada (con nodos)
// no voy a usar ninguna otra primitiva como "pila_crear()" asi muestro como seria la implementacion interna de cada cosa que se debe hacer. Pero lo optimo seria crear cada primitiva para este tipo de pila enlazada.
pila_t* pila_union(pila_t* p1, pila_t* p2) {
    pila_t* res = malloc(sizeof(pila_t));   // creo la pila
    if (res == NULL) return NULL;   // chequeo que no hayan errores de memoria

    if (p1 == NULL && p2 == NULL) {     // si las dos pilas son NULL, devuelvo una pila enlazada vacia.
        res->largo = 0;
        res->prim = NULL;
        res->ult = NULL;
        // no libero la memoria de las pilas ya que son NULL
        return res; 
    }

    if (p1 == NULL || p1->largo == 0) {   // si p1 es NULL o esta vacia devuelvo una copia de p2. 
        res->largo = p2->largo;
        res->prim = p2->prim;
        res->ult = p2->ult;
        free(p2);
        return res;
    }
    else if (p2 == NULL || p2->largo == 0) {  // si p2 es NULL o esta vacia devuelvo una copia de p1
        res->largo = p1->largo;
        res->prim = p1->prim;
        res->ult = p1->ult;
        free(p1);
        return res;
    }
    // si las 2 pilas son validas y ninguna de las dos esta vacia, entonces procedo a unirlas en la nueva pila "res"
    res->prim = p1->prim;   // el primer nodo de p3 apunta al primer nodo de p1
    p1->ult->sig = p2->prim;    // el ultimo nodo de p1 apunta al primer nodo de p2
    res->ult = p2->ult;     // el ultimo nodo de p3 apunta al ultimo nodo de p2
    res->largo = p1->largo + p2->largo; // sumo los largos
    free(p1);   // destruyo las dos pilas iniciales.
    free(p2);   // lo libero con free porque desconozco de que haria pila_destruir(), ya que no quiero liberar la memoria de los nodos. Solo la de las pilas. Podria usar pila_destruir(p1, NULL); pila_destruir(p2, NULL); pero con el free basta. 
    return res;
}

// Y efectivamente la primitiva anda en tiempo constante (O(1)), ya que lo unico que hago son operaciones de asignacion y comparacion, por ende, todo O(1) e independiente de la cantidad de nodos que tenga cada pila.

// // ej 4

// Implementar una primitiva para el ABB (cuyas claves son números positivos) bool abb_camino_suma(const abb_t*
// abb, int s) que reciba un ABB y un número S y determine si hay un camino dentro del ABB cuyas claves sumen
// exactamente S. Realizar la menor cantidad de comparaciones posibles. Indicar y justificar la complejidad del algoritmo
// implementado.

#include "abb.h"

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

bool abb_camino_suma(const abb_t* abb, int s) {
    if (abb == NULL) return false;
    hash_t* dicc = hash_crear(NULL);
    if (dicc == NULL) return false;
    bool res =  _abb_camino_suma(dicc, abb->raiz, 0, s);
    hash_destruir(dicc);
    return res;
}

bool _abb_camino_suma(hash_t* dicc, nodo_abb_t* nodo, int *suma, int s) {
    if (nodo == NULL) return false;
    if (*suma + (int)(nodo->dato) == s)
        return true;
    else if (*suma + (int)(nodo->dato) > s)
        return false;

    *suma += (int)(nodo->dato);

    if (!hash_guardar(dicc, nodo->clave, nodo->dato)) {
        hash_destruir(dicc);
        return false;
    }

    if (_abb_camino_suma(dicc, nodo->izq, suma, s))
        return true;
    if (_abb_camino_suma(dicc, nodo->der, suma, s))
        return true;
    
    *suma -= (int)(nodo->dato);
    hash_borrar(dicc, nodo->clave);
    return false;
}

// me resulta medio complicado ver la complejidad del algoritmo, pero si no me equivoco, esto en el peor de los casos recorreria una vez todos los elementos del abb. Imaginandome que el numero S exageradamente grande (cosa que nunca pueda llegar a sumar ese numero), voy llamando a cada lado de cada nodo, hasta que ese nodo sea una hoja (o sea NULL). Por lo que terminaria siendo O(n) (aunque estoy podando casos)
// creo que lo puedo resolver con teorema maestro.
// a = 2 -> 2 llamados recursivos
// b = 2 -> proporcion del tamagno original
// c = 0 -> costes extras n^c = 1 -> c = 0
// por ende log 2 (2) = 1, y 1 > 0. 1 > C -> O(n ^ (log B (A))) -> O(n^1) -> O(n)