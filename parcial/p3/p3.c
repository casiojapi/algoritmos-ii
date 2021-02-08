// Maximo Santoro. Padron: 105572
// Parcial N3
// Ejercicios a hacer: 2 - 5 - 7

/*
2. Implementar en C una primitiva para el heap heap_t* heap_interseccion(const heap_t* h1, const heap_t* h2,
cmp_funct_t nueva_cmp) que reciba dos heaps (cuyos datos son cadenas) y devuelva un nuevo heap que tenga la
intersección de los elementos de ambos. Los heaps pueden tener misma función de comparación, o no, pero el heap resultante
deberá usar como función de comparación pasada por parámetro (nueva_cmp). Se puede asumir que cada heap tiene cada
elemento una única vez. La primitiva debe ejecutar en O(n + m), siendo n la cantidad de elementos de h1 y m la cantidad
de elementos de h2 (no se considerará como bien el ejercicio si no cumple con la complejidad). Justificar la complejidad del
algoritmo implementado.
*/

// Ej 2:
#include <stdlib.h>
#include "heap.h"

// typedef int (*cmp_func_t)(const void *a, const void *b);

void heapify(void *arreglo[], size_t tam, cmp_func_t cmp);
void downheap(void* arreglo[], size_t tam, size_t pos_padre, cmp_func_t cmp);

heap_t* heap_interseccion(const heap_t* h1, const heap_t* h2, cmp_func_t nueva_cmp) {
    heap_t* heap_final = heap_crear(nueva_cmp); //O(1)
    if (heap_final == NULL) return NULL; // O(1)
    // uno los dos arreglos en uno solo, y llamo a heapify a que los ordene 
    size_t cantidad_total_elem = h1->cantidad + h2->cantidad; // O(1)
    void** arr = malloc(sizeof(void*) * cantidad_total_elem); // O(1)
    if (arr == NULL) { // O(1)
        heap_destruir(heap_final, NULL); // O(1)
        return NULL; // O(1)
    }
    // de esta parte no estaba muy seguro ya que nunca habia unido dos arrays en c, pero creo que con esto deberia andar bien. 
    memcpy(arr, h1->arreglo, h1->cantidad); // aca no estaba seguro de si era O(n) u O(1), ya que no se como funciona internamente memcpy. Pero de todas formas, no interfiere en el orden de la primitiva, ya que en todo caso, si es O(n), el orden final de la primitiva permanece en O(n + m) + O(n) + O(m) = O(n + m)
    memcpy(arr + h1->cantidad, h2->arreglo, h2->cantidad); // aplica lo de arriba
    // heapify de los dos arreglos juntos. 
    heapify(arr, cantidad_total_elem, nueva_cmp);   // O(n + m) siendo n elementos de h1 y m elem de h2.
    // arreglo la invariante del heap
    heap_final->cantidad = cantidad_total_elem;
    heap_final->arreglo = arr;
    heap_final->cmp = nueva_cmp;
    heap_final->cantidad = cantidad_total_elem;
    // todo lo que queda, O(1)
    return heap_final;
}
// Por lo que queda O(n + m)

// en palabras, lo que pense es: agarrar los dos arreglos de los dos heaps, hacer un solo arreglo, y mandarle ese arreglo a heapify. Despues tengo que arreglar el tema de la invariante del heap, ya que mi implementacion de heapify no toca nada de eso, si no me equivoco, nada mas. 
// Hago esto para satisfacer el orden de la primitiva. En este caso O(n + m), siendo n la cantidad de elementos en h1, y m en h2. Heapify sabemos que tiene orden O(n) siendo n los elementos del arreglo a hacer un heap... Entonces si la cantidad de elementos mandados a nuestro heapify es n + m, quedaria la primitiva de orden O(n + m). (si es que no hacemos alguna operacion fuera de heapify que tenga un orden distinto que nos pueda distorisionar dicho orden obtenido)


// implementacion de heapify
void heapify(void *arreglo[], size_t tam, cmp_func_t cmp) {
    for (size_t i = (tam / 2) + 1; i >= 0; i--){
        downheap(arreglo, tam, i, cmp);
        if(i == 0) break; // como i es de tipo size_t no admite valores negativos
    }
}
// implementacion de downheap
void downheap(void* arreglo[], size_t tam, size_t pos_padre, cmp_func_t cmp) {
    if (tam - 1 == pos_padre) return;    // si llegamos al final, return.
    size_t h_izq = 2 * pos_padre + 1;
    size_t h_der = 2 * pos_padre + 2;
    size_t max = pos_max(arreglo, tam, pos_padre, h_izq, h_der, cmp);
    if(max != pos_padre){
        swap_elem(arreglo, pos_padre, max);
        downheap(arreglo, tam, max, cmp);
    }
}