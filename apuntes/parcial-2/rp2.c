// Maximo Santoro. Padron: 105572. DNI: 42822674

// 1. Una nueva actualización de Tinder permite encontrar el Match perfecto. Para aquellos que se inscriban a este nuevo feature,
// sus perfiles serán categorizados (automáticamente) para luego encontrar un Match perfecto con otra persona que tenga
// igual categoría. Hasta ahora se cuenta con un hash que tiene como clave el ID del usuario (cadena), y como valor asociado
// un código (también cadena) que responde a la categorización del perfil. Implementar una función en C que reciba dicho
// diccionario y que devuelva true si fue posible encontrarle pareja a todos los que participaron en esta actualización, false si
// por lo menos alguno quedó solo. Indicar y justificar el orden de la función.
// Aclaración: los Match perfectos son para parejas. Aún no se permite armar tríos o poliamor.


// 2. Implementar en C una primitiva para el ABB que nos permita obtener la segunda máxima clave del ABB, con firma const
// char* abb_segundo_maximo(const abb_t*). En caso de tener menos de dos elementos, devolver NULL. La primitiva debe
// ejecutar en O(log n). Justificar el orden del algoritmo propuesto.


// 3. Realizar un seguimiento de aplicar RadixSort para ordenar el siguiente arreglo de fechas en formato DDMM, donde deben
// quedar primero ordenado por mes, y dentro del mismo mes, por día:
// 1806 - 2711 - 0707 - 1110 - 3004 - 3103 - 0107 - 1004 - 3003 - 1911

// ejercicio 2

#include <stdlib.h>
#include <stdbool.h>

typedef struct nodo_abb {
    struct nodo_abb *izq;
    struct nodo_abb *der;
    char *clave;
    void *dato;
} nodo_abb_t;

//Definición del struct abb

typedef struct abb {
    nodo_abb_t *raiz;
    size_t cant;
    // abb_comparar_clave_t comparar;
    // abb_destruir_dato_t destruir;
} abb_t;



char* abb_obtener_max(nodo_abb_t* nodo) {
    if (nodo->der == NULL) return nodo->clave;
    return abb_obtener_max(nodo->der);
}

char* abb_maximo(nodo_abb_t* nodo, nodo_abb_t* padre) {
    if (nodo->der == NULL) {
        if (nodo->izq)
            return abb_obtener_max(nodo->izq);
        return padre->clave;
    }
    return abb_maximo(nodo->der, nodo);
}

// rta ej 2
const char* abb_segundo_maximo(const abb_t* abb) {
    if (abb->cant < 2) return NULL;
    nodo_abb_t* raiz = abb->raiz;
    if (raiz->der == NULL)
        abb_maximo(raiz->izq, raiz);
    else 
        abb_maximo(raiz->der, raiz);
}

// Justificacion del orden. 
// la primitiva va a tener una complejidad de O(log n), ya que como mucho, va a recorrer la altura entera del arbol. o sea una sola rama. (tal vez la distancia que recorra sea la distancia que mide la rama)
// Esto lo vemos claramente porque descartamos una mitad siempre que avanzamos, como en una busqueda binaria que tambien es O(log n).




// 1. Una nueva actualización de Tinder permite encontrar el Match perfecto. Para aquellos que se inscriban a este nuevo feature,
// sus perfiles serán categorizados (automáticamente) para luego encontrar un Match perfecto con otra persona que tenga
// igual categoría. Hasta ahora se cuenta con un hash que tiene como clave el ID del usuario (cadena), y como valor asociado
// un código (también cadena) que responde a la categorización del perfil. Implementar una función en C que reciba dicho
// diccionario y que devuelva true si fue posible encontrarle pareja a todos los que participaron en esta actualización, false si
// por lo menos alguno quedó solo. Indicar y justificar el orden de la función.
// Aclaración: los Match perfectos son para parejas. Aún no se permite armar tríos o poliamor.


// rta ej 1
#include "hash.h"

bool match_perfecto(hash_t* hash) {
    hash_t* categorias = hash_crear(free);
    hash_iter_t* iter = hash_iter_crear(hash);

    while (!hash_iter_al_final(iter)) {
        char* id_actual = hash_iter_ver_actual(iter);
        char* cat = hash_obtener(hash, id_actual); // obtengo categoria actual

        if (hash_pertenece(categorias, cat)) {
            size_t* cant = hash_obtener(categorias, cat);
            (*cant)++;
        } else {
            size_t* cant = malloc(sizeof(size_t));
            (*cant) = 1;
            hash_guardar(categorias, cat, cant);
        }
        hash_iter_avanzar(iter);
    }

    hash_iter_destruir(iter);

    hash_iter_t* iter_cat = hash_iter_crear(categorias);

    while (!hash_iter_al_final(iter_cat)) {

        char* categoria_actual = hash_iter_ver_actual(iter_cat);
        size_t* cant = hash_obtener(categorias, categoria_actual);

        if (*cant % 2 != 0) {
            hash_iter_destruir(iter_cat);
            hash_destruir(categorias);
            return false;
        }
        hash_iter_avanzar(iter_cat);
    }
    hash_iter_destruir(iter_cat);
    hash_destruir(categorias);
    return true;
}

// Orden y justificacion

// el orden de la funcion deberia ser O(n + k), siendo N la cantidad de usuarios, y K la cantidad de categorias distintas que hay. 
// el primer while, seria O(n), ya que recorre todo el hash de usuarios, una vez, y se mantiene en O(n), ya que todas las operaciones que hago dentro de este while son constantes. 

// Luego en el segundo while, tengo un O(k), o sea ,itero ese while K veces, siendo k la cantidad de categorias distintas. Y dentro de este while siempre hago operaciones constantes. 

// Tambien tengo los hash destruir, que serian O(n), pero estos al ejecutarse una sola vez, no me interfieren en la complejidad general de la funcion. 

// Por lo tanto quedaria O(N+K)



//ej 3 en p2.pdf