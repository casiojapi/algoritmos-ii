#include "heap.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//Función auxiliar para comparar enteros
int comparar_enteros(const void *a, const void *b){
    int valor1 = *(int*)a;
    int valor2 = *(int*)b;
    if(valor1 == valor2) return 0;
    if(valor1 < valor2) return -1;
    return 1;
}

static void pruebas_heap_vacio(void){
    printf("\nINICIO PRUEBAS HEAP VACIO:\n");
    heap_t *heap = heap_crear(comparar_enteros);
    print_test("El heap se creó correctamente", heap);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Ver máximo en un heap vacío devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar un heap vacío devuelve NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
    print_test("El heap se destruyó correctamente", true);
}

static void pruebas_heap_arreglo_null(void){
    printf("\nINICIO PRUEBAS CREAR HEAP CON ARREGLO NULL DE TAMAÑO 0:\n");
    heap_t *heap = heap_crear_arr(NULL, 0, comparar_enteros);
    print_test("El heap se creó correctamente", heap);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Ver máximo en un heap vacío devuelve NULL", heap_ver_max(heap) == NULL);
    print_test("Desencolar un heap vacío devuelve NULL", heap_desencolar(heap) == NULL);

    heap_destruir(heap, NULL);
    print_test("El heap se destruyó correctamente", true);
}

static void pruebas_heap_arreglo(void){
    printf("\nINICIO PRUEBAS CREAR HEAP CON ARREGLO DE ENTEROS DE TAMAÑO 10:\n");
    void **arreglo = malloc(sizeof(void*) * 10);
    int valores[] = {10, 20, 3, -5, 8, 5, 0, 33, -2, 1};
    int valores_ordenados[] = {33, 20, 10, 8, 5, 3, 1, 0, -2, -5};
    for(size_t i = 0; i < 10; i++){
        arreglo[i] = &valores[i];
    }
    heap_t *heap = heap_crear_arr(arreglo, 10, comparar_enteros);
    print_test("El heap se creó correctamente", heap);
    print_test("El heap está vacío es false", !heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 10", heap_cantidad(heap) == 10);
    print_test("Ver máximo devuelve valor esperado", heap_ver_max(heap) == &valores[7]);
    bool ok = true;
    for(size_t i = 0; i < 10; i++){
        ok &= (*(int*)heap_ver_max(heap) == valores_ordenados[i]);
        ok &= (*(int*)heap_desencolar(heap) == valores_ordenados[i]);
    }
    print_test("Se desencolaron todos los elementos correctamente verificando máximo y orden", ok);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("El heap se destruyó correctamente", true);
    free(arreglo);
}

static void pruebas_heap_encolar(void){
    printf("\nINICIO PRUEBAS HEAP ENCOLAR ELEMENTOS ORDENADOS MENOR A MAYOR(CANT = 6):\n");
    int valores[] = {0, 1, 2, 3, 4, 5};
    heap_t *heap = heap_crear(comparar_enteros);
    print_test("El heap se creó correctamente", heap);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    bool ok = true;
    for(size_t i = 0; i < 6; i++){
        ok &= heap_encolar(heap, &valores[i]);
        ok &= (*(int*)heap_ver_max(heap) == valores[i]);
    }
    print_test("Se encolaron todos los elementos ordenados verificando en cada paso que el máximo cambie", ok);
    print_test("El heap está vacío es false", !heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 6", heap_cantidad(heap) == 6);
    heap_destruir(heap, NULL);
    print_test("El heap se destruyó correctamente", true);
}

static void pruebas_heap_desencolar(void){
    printf("\nINICIO PRUEBAS HEAP DESENCOLAR ELEMENTOS (CANT = 6):\n");
    int valores[] = {0, 1, 2, 3, 4, 5};
    int valores_ordenados[] = {5, 4, 3, 2, 1, 0};
    heap_t *heap = heap_crear(comparar_enteros);
    print_test("El heap se creó correctamente", heap);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    bool ok = true;
    for(size_t i = 0; i < 6; i++){
        ok &= heap_encolar(heap, &valores[i]);
        ok &= (*(int*)heap_ver_max(heap) == valores[i]);
    }
    print_test("Se encolaron todos los elementos ordenados verificando en cada paso que el máximo cambie", ok);
    print_test("El heap está vacío es false", !heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 6", heap_cantidad(heap) == 6);
    ok = true;
    for(size_t i = 0; i < 6; i++){
        ok &= (*(int*)heap_ver_max(heap) == valores_ordenados[i]);
        ok &= (*(int*)heap_desencolar(heap) == valores_ordenados[i]);
    }
    print_test("Se desencolaron todos los elementos correctamente verificando máximo y orden", ok);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("El heap se destruyó correctamente", true);
}

static void pruebas_heap_destruir_free(void){
    printf("\nINICIO PRUEBAS HEAP DESTRUIR_ELEMENTO = FREE:\n");
    void **arreglo = malloc(sizeof(void*) * 10);
    for(int i = 0; i < 10; i++){
        int *elemento = malloc(sizeof(int));
        *elemento = i;
        arreglo[i] = elemento;
    }
    heap_t *heap = heap_crear_arr(arreglo, 10, comparar_enteros);
    print_test("El heap se creó correctamente (elementos alojados en memoria dinámica)", heap);
    print_test("El heap está vacío es false", !heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 10", heap_cantidad(heap) == 10);
    heap_destruir(heap, free);
    print_test("El heap se destruyó correctamente con destruir_elemento = free", true);
    free(arreglo);
}

static void pruebas_heapsort(void){
    printf("\nINICIO PRUEBAS HEAPSORT:\n");
    void **arreglo = malloc(sizeof(void*) * 10);
    int valores[] = {10, 20, 3, -5, 8, 5, 0, 33, -2, 1};
    int valores_ordenados[] = {-5, -2, 0, 1, 3, 5, 8, 10, 20, 33};
    for(size_t i = 0; i < 10; i++){
        arreglo[i] = &valores[i];
    }
    heap_sort(arreglo, 10, comparar_enteros);
    bool ok = true;
    for(size_t i = 0; i < 10; i++){
        ok &= (*(int*)arreglo[i] == valores_ordenados[i]);
    }
    print_test("Se ordenó el arreglo mediante HeapSort correctamente", ok);
    free(arreglo);
}

static void pruebas_heapsort_volumen(size_t largo){
    printf("\nINICIO PRUEBAS HEAPSORT VOLUMEN:\n");
    void **arreglo = malloc(sizeof(void*) * largo);
    int *valores = malloc(sizeof(int) * largo);
    for(size_t i = 0; i < largo ; i++){
        valores[i] = rand();
        arreglo[i] = &valores[i];
    }
    heap_sort(arreglo, largo, comparar_enteros);
    bool ok = true;
    int anterior = *(int*)arreglo[0];
    for(size_t i = 0; i < largo; i++){
        ok &= (*(int*)arreglo[i] >= anterior);
        if (!ok) break;
        anterior = *(int*)arreglo[i];
    }
    print_test("Se ordenó el arreglo mediante HeapSort correctamente", ok);
    free(arreglo);
    free(valores);
}

static void pruebas_heap_volumen_arreglo(size_t largo){
    printf("\nINICIO PRUEBAS HEAP VOLUMEN (CREANDO POR ARREGLO):\n");
    void **arreglo = malloc(sizeof(void*) * largo);
    int *valores = malloc(sizeof(int) * largo);
    for(size_t i = 0; i < largo ; i++){
        valores[i] = rand() % 1000;
        arreglo[i] = &valores[i];
    }
    heap_t *heap = heap_crear_arr(arreglo, largo, comparar_enteros);
    print_test("El heap se creó correctamente mediante un arreglo del tamaño ingresado", heap);
    print_test("El heap está vacío es false", !heap_esta_vacio(heap));
    print_test("Cantidad de elementos es la correcta", heap_cantidad(heap) == largo);
    bool ok = true;
    int anterior = *(int*)heap_ver_max(heap);
    for(size_t i = 0; i < largo; i++){
        ok &= (*(int*)heap_ver_max(heap) <= anterior);
        if (!ok) break;
        anterior = *(int*)heap_desencolar(heap);
    }
    print_test("Se desencolaron todos los elementos verificando que en cada paso que sea el máximo y sea menor o igual al elemento anteriormente desencolado", ok);
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    heap_destruir(heap, NULL);
    print_test("El heap se destruyó correctamente", true);
    free(arreglo);
    free(valores);
}

static void pruebas_heap_volumen_destruir_free(size_t largo){
    printf("\nINICIO PRUEBAS HEAP VOLUMEN ENCOLANDO Y DESTRUIR_ELEMENTO = FREE:\n");
    heap_t *heap = heap_crear(comparar_enteros);
    print_test("El heap se creó correctamente", heap);
    print_test("El heap está vacío", heap_esta_vacio(heap));
    print_test("Cantidad de elementos es 0", heap_cantidad(heap) == 0);
    bool ok = true;
    for(int i = 0; i < largo; i++){
        int *elemento = malloc(sizeof(int));
        *elemento = rand() % 1000;
        ok &= heap_encolar(heap, elemento);
    }
    print_test("Se encolaron todos los elementos correctamente (alojados en memoria dinámica)", ok);
    print_test("El heap está vacío es false", !heap_esta_vacio(heap));
    print_test("Cantidad de elementos es la correcta", heap_cantidad(heap) == largo);
    heap_destruir(heap, free);
    print_test("El heap se destruyó correctamente con destruir_elemento = free", true);
}


void pruebas_heap_estudiante(void){
    pruebas_heap_vacio();
    pruebas_heap_arreglo_null();
    pruebas_heap_arreglo();
    pruebas_heap_encolar();
    pruebas_heap_desencolar();
    pruebas_heap_destruir_free();
    pruebas_heapsort();
    pruebas_heapsort_volumen(10000);
    pruebas_heap_volumen_arreglo(10000);
    pruebas_heap_volumen_destruir_free(10000);
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

// int main(void) {
//     pruebas_heap_estudiante();
//     return failure_count() > 0;  // Indica si falló alguna prueba.
// }

#endif
