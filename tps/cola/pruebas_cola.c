#include "cola.h"
#include "testing.h"

#include <stdlib.h>
#include <stdio.h>

#define TEST_ELEM 1618033
#define TEST_VOLUMEN 100000

// ok
static void prueba_cola_vacia(void) {
    cola_t *c = cola_crear();
    print_test("la cola fue creada", c != NULL);
    print_test("la cola esta vacia", cola_esta_vacia(c));
    cola_destruir(c, NULL);
}
//
static void prueba_destruir_vacia_null(void) {
    cola_t *c = cola_crear();
    print_test("la cola fue creada", c);
    cola_destruir(c, NULL);
}

static void prueba_destruir_null(void) {
    cola_t *c = cola_crear();
    print_test("la cola 2 fue creada", c);
    print_test("la cola 2 esta vacia", cola_esta_vacia(c));
    int* elem = malloc(sizeof(int));
    print_test("se creo el elemento de prueba", elem);
    bool encola = cola_encolar(c, elem);
    print_test("encola - cola 2", encola);
    int* check = cola_ver_primero(c);
    print_test("encola correctamente", elem == check);
    cola_destruir(c, NULL);
    free(elem);
}

static void prueba_destruir_free(void) {
    cola_t *c = cola_crear();
    print_test("la cola fue creada", c);
    print_test("la cola esta vacia", cola_esta_vacia(c));
    int* elem = malloc(sizeof(int));
    print_test("se creo el elemento de prueba", elem);
    bool encola = cola_encolar(c, elem);
    print_test("encola", encola);
    int* check = cola_ver_primero(c);
    print_test("encola correctamente", elem == check);
    cola_destruir(c, free);
}

static void prueba_destruccion_free(void) {
    cola_t *c = cola_crear();
    int *t = malloc(sizeof(int));
    *t = TEST_ELEM;
    bool encola = cola_encolar(c, t);
    print_test("encolar da true", encola);
    cola_destruir(c, free); 
}

static void prueba_destruir_vacia_free(void) {
    cola_t *c = cola_crear();
    print_test("la cola 3 fue creada", c);
    print_test("la cola 3 esta vacia", cola_esta_vacia(c));
    cola_destruir(c, free);
}

//
static void prueba_encolar_desencolar(void) {
    cola_t *c = cola_crear();
    int *elem = malloc(sizeof(int));
    bool encola = cola_encolar(c, elem);
    print_test("encolar da true - 1", encola);
    int* check = cola_ver_primero(c);
    print_test("encola correctamente - 1", elem == check);
    int *elem_2 = malloc(sizeof(int));
    encola = cola_encolar(c, elem_2);
    print_test("encolar da true - 2", encola);
    int* test = cola_desencolar(c);
    print_test("encola int - 2", test == elem);
    test = cola_desencolar(c);
    print_test("encola int * - 1 ", test == elem_2);
    print_test("se mantiene invariante despues de encolar-desencolar - 2", cola_esta_vacia(c));
    cola_destruir(c, NULL);
    free(elem);
    free(elem_2);   
}

//
static void prueba_volumen(void) {
    bool encola = true;
    cola_t *c = cola_crear();
    size_t *vector_elem = malloc(sizeof(size_t) * TEST_VOLUMEN);
    for (size_t i = 0; i < TEST_VOLUMEN; i++)
        if (!cola_encolar(c, vector_elem + i))
            encola = false;
    

    print_test("encola volumen", encola);
    encola = true;
    
    for (size_t i = 0; i < TEST_VOLUMEN; i++) {
        size_t *elem_post = cola_desencolar(c);
        if (vector_elem + i != elem_post)
            encola = false;
    }
    print_test("desencola el ciclo de volumen", encola);
    print_test("esta vacia", cola_esta_vacia(c));
    print_test("despues de encolar-desencolar, ver tope es invalido", cola_ver_primero(c) == NULL);
    print_test("despues de encolar-desencolar, desencolar es invalido", cola_desencolar(c) == NULL);
    free(vector_elem);
    cola_destruir(c, NULL);
}

//
static void prueba_recien_creada(void) {
    cola_t *c = cola_crear();
    print_test("recien creada, esta vacia", cola_esta_vacia(c));
    int *test = cola_ver_primero(c);
    print_test("recien creada, ver tope", test == NULL);
    test = cola_desencolar(c);
    print_test("recien creada, desencolar", test == NULL);
    cola_destruir(c, NULL);
}

static void prueba_encolar_null(void) {
    cola_t *c = cola_crear();
    bool encola = cola_encolar(c, NULL);
    print_test("encolar da true", encola);
    print_test("ver primero NULL", !cola_ver_primero(c));
    int *test = cola_desencolar(c);
    print_test("encola NULL", !test);
    print_test("esta vacia - post-NULL", cola_esta_vacia(c));
    cola_destruir(c, NULL);
}


void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_destruir_vacia_null();
    prueba_destruir_vacia_free();
    prueba_destruir_free();
    prueba_destruir_null();
    prueba_encolar_desencolar();
    prueba_volumen();
    prueba_recien_creada();
    prueba_encolar_null();
    prueba_destruccion_free();
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_cola_estudiante();
    return failure_count() > 0;
}

#endif
