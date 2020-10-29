#include "cola.h"
#include "testing.h"

#include <stdlib.h>
#include <stdio.h>

#define TEST_ELEM 1618033
#define TEST_VOLUMEN 100000

// ok
static void prueba_cola_vacia(void)
{
    cola_t *c = cola_crear();
    print_test("la cola fue creada", c != NULL);
    print_test("la cola esta vacia", cola_esta_vacia(c));
    cola_destruir(c, NULL);
}

//
static void prueba_crear_destruir(void)
{
    cola_t *c = cola_crear();
    print_test("la cola fue creada", c != NULL);
    cola_destruir(c, NULL);
}

//
static void prueba_encolar_desencolar(void)
{
    cola_t *c = cola_crear();
    int *elem = malloc(sizeof(int));
    *elem = TEST_ELEM;
    bool encola = cola_encolar(c, elem);
    print_test("encolar da true", encola);
    int *test = cola_desencolar(c);
    print_test("encola int * - 1 ", test == elem);
    print_test("se mantiene invariante despues de encolar-desencolar - 1", cola_esta_vacia(c));
    free(elem);
    int test_dos = TEST_ELEM;
    encola = cola_encolar(c, &test_dos);
    print_test("encolar da true", encola);
    test = cola_desencolar(c);
    print_test("encola int - 2", test == &test_dos);
    print_test("se mantiene invariante despues de encolar-desencolar - 2", cola_esta_vacia(c));
    cola_destruir(c, NULL);
}

//
static void prueba_volumen(void)
{
    bool encola = true;
    cola_t *c = cola_crear();
    size_t **vector_elem = malloc(sizeof(size_t *) * TEST_VOLUMEN);
    for (size_t i = 0; i < TEST_VOLUMEN; i++)
    {
        size_t test = TEST_ELEM * i;
        vector_elem[i] = &test;
        encola = cola_encolar(c, vector_elem[i]);
    }

    print_test("encola volumen", encola);
    encola = true;
    
    for (size_t i = 0; i < TEST_VOLUMEN; i++)
    {
        size_t *elem_post = cola_desencolar(c);

        if (vector_elem[TEST_VOLUMEN - 1 - i] != elem_post)
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
static void prueba_recien_creada(void)
{
    cola_t *c = cola_crear();
    print_test("recien creada, esta vacia", cola_esta_vacia(c));
    int *test = cola_ver_primero(c);
    print_test("recien creada, ver tope", test == NULL);
    test = cola_desencolar(c);
    print_test("recien creada, desencolar", test == NULL);
    cola_destruir(c, NULL);
}

//ok
static void prueba_encolar_null(void)
{
    cola_t *c = cola_crear();
    bool encola = cola_encolar(c, NULL);
    print_test("encolar da true", encola);
    int *test = cola_desencolar(c);
    print_test("encola NULL", test == NULL);
    cola_destruir(c, NULL);
}

//
void pruebas_cola_estudiante()
{
    prueba_cola_vacia();
    prueba_crear_destruir();
    prueba_encolar_desencolar();
    prueba_volumen();
    prueba_recien_creada();
    prueba_encolar_null();
}


#ifndef CORRECTOR

int main(void)
{
    pruebas_cola_estudiante();
    return failure_count() > 0;
}

#endif
