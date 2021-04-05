// Maximo Santoro. Padron: 105572. DNI: 42822674
// Final - Algoritmos y Programacion II - 26/3/2021

#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"
#include "hash.h"
// ej 4
// Implementar en C una función lista_t* lista_filtrar_repetido(const lista_t*) que reciba una lista de cadenas
// y devuelva una nueva lista con los mismos elementos, pero sin repetidos (nos quedamos sólo con la primera aparición).
// La lista original no puede ser modificada. Indicar y justificar la complejidad de la función implementada.


lista_t* lista_filtrar_repetido(const lista_t* lista) {
    hash_t* hash = hash_crear(NULL);        // O(1) -> creo un hash para ir guardando las apariciones de cada clave.
    lista_iter_t* iter = lista_iter_crear(lista);   // O(1) -> creo un iterador para poder iterar la lista sin usar su implementacion interna ya que esto es una funcion y no una primitiva
    lista_t* lista_final = lista_crear();       // O(1) -> creo una la lista nueva para devolver el resultado

    while (!lista_iter_al_final(iter)) {        // O(n), siendo n los elementos en la lista original, y todas las operaciones dentro del while son O(1)
        char* clave = lista_iter_ver_actual(iter);  // O(1)
        if (!hash_pertenece(hash, clave)) {     // O(1)
            hash_guardar(hash, clave, clave);   // O(1)
            lista_insertar_ultimo(lista_final, clave);  // O(1)
        }
        lista_iter_avanzar(iter);       // O(1)
    }

    hash_destruir(hash);    // en este caso es O(1) ya que destruyo solo la estructura y no los datos dentro de la tabla.
    lista_iter_destruir(iter);  // O(1)
    return lista_final;
}

// La funcion tendria de complejidad O(n), siendo n los elementos en la lista original.