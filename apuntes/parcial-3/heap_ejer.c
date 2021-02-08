// ejercicio de k merge
// escribir en C una funcion k_merge que reciba k arreglos ordenados y devuelva uno nuevo con todos los elementos ordenados entre si. 
#include <stdlib.h>
#include "heap.h"

typedef struct minimo {
    size_t valor_pos;
    size_t arr_pos;
    int valor;
} minimo_t;

// Necesitamos saber de que arreglo vienen y en que posicion del arreglo estan.

minimo_t* _crear_min(size_t valor_pos, size_t arr, int valor) {
    minimo_t* min = malloc(sizeof(minimo_t));
    if (!min) return NULL;
    min->valor_pos = valor_pos;
    min->arr_pos = arr;
    min->valor = valor;
    return min;
}

int* k_merge(int** arr, size_t k, size_t h) {
    heap_t* minimos = heap_crear(cmp_min_arr); //O(1)
    int* res = malloc(sizeof(int) * k * h);

    for (size_t i = 0; i < k; i++) { // o(k * (log k))
        heap_encolar(minimos, _crear_min(0, i, arr[i][0])); // o(log k)
    }
    for (size_t i = 0; !heap_esta_vacio(minimos); i++) {  // o ((h*k) * (2 * (log k)))
        minimo_t* min = heap_desencolar(minimos); // o(log k)
        res[i] = min->valor;
        if (min->valor_pos + 1 >= h) {
            free(min);
            continue;
        }
        size_t pos = min->valor_pos + 1;
        heap_encolar(minimos, _crear_min(pos, min->arr_pos, arr[min->arr_pos][pos]));   // o(log k)
        free(min);
    }
    heap_destruir(minimos, NULL);
    return res;
} // O ((h + k) * (log k))

void** tres_mas_grandes(heap_t* heap) {
    void** res = malloc(sizeof(void*) * 3);
    if (res == NULL) return NULL;
    
    res[0] = heap->arreglo[0];
    void* h_izq = heap->arreglo[1];
    void* h_der = heap->arreglo[2];
    if (heap->cmp(h_izq, h_der) > 0) {
        res[1] = h_izq;
        if (heap->cmp(heap->arreglo[3], heap->arreglo[4]) > 0) {
            if (heap->cmp(heap->arreglo[3], h_der) > 0)
                res[2] = heap->arreglo[3];
            else
                res[2] = h_der;
        }
        else {
            if (heap->cmp(heap->arreglo[4], h_der) > 0)
                res[2] = heap->arreglo[4];
            else
                res[2] = h_der;
        }
    }
    else {
        res[1] = h_der;
        if (heap->cmp(heap->arreglo[5], heap->arreglo[6]) > 0) {
            if (heap->cmp(heap->arreglo[5], h_izq) > 0)
                res[2] = heap->arreglo[5];
            else
                res[2] = h_izq;
        }
        else {
            if (heap->cmp(heap->arreglo[6], h_izq) > 0)
                res[2] = heap->arreglo[6];
            else
                res[2] = h_izq;
        }
    }
    return res;
}