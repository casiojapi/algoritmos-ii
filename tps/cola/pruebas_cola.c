#include "cola.h"
#include "testing.h"

#include <stdlib.h>
#include <stdio.h>

#define TEST_ELEM 1618033
#define TEST_VOLUMEN 100000

static void prueba_pila_vacia(void)
{
    pila_t *p = pila_crear();
    print_test("la pila fue creada", p != NULL);
    print_test("la pila esta vacia", pila_esta_vacia(p));
    pila_destruir(p);
}

static void prueba_crear_destruir(void)
{
    pila_t *p = pila_crear();
    print_test("la pila fue creada", p != NULL);
    pila_destruir(p);
}

static void prueba_apilar_desapilar(void)
{
    pila_t *p = pila_crear();
    int *elem = malloc(sizeof(int));
    *elem = TEST_ELEM;
    bool apila = pila_apilar(p, elem);
    print_test("apilar da true", apila);
    int *test = pila_desapilar(p);
    print_test("apila int * - 1 ", test == elem);
    print_test("se mantiene invariante despues de apilar-desapilar - 1", pila_esta_vacia(p));
    free(elem);
    int test_dos = TEST_ELEM;
    apila = pila_apilar(p, &test_dos);
    print_test("apilar da true", apila);
    test = pila_desapilar(p);
    print_test("apila int - 2", test == &test_dos);
    print_test("se mantiene invariante despues de apilar-desapilar - 2", pila_esta_vacia(p));
    pila_destruir(p);
}

static void prueba_volumen(void)
{
    bool apila = true;
    pila_t *p = pila_crear();
    size_t **vector_elem = malloc(sizeof(size_t *) * TEST_VOLUMEN);
    for (size_t i = 0; i < TEST_VOLUMEN; i++)
    {
        size_t test = TEST_ELEM * i;
        vector_elem[i] = &test;
        apila = pila_apilar(p, vector_elem[i]);
        if (!apila)
            print_test("APILAR DA TRUE?", apila);
        size_t *copia = pila_ver_tope(p);
        if (copia != vector_elem[i])
            print_test("ver tope es igual a lo apilado", 0);
    }

    print_test("apila volumen", apila);

    apila = true;

    for (size_t i = 0; i < TEST_VOLUMEN; i++)
    {
        size_t *elem_post = pila_desapilar(p);
        if (vector_elem[TEST_VOLUMEN - i - 1] != elem_post)
        {
            apila = 0;
            print_test("desapila volumen", apila);
        }
    }
    print_test("desapila volumen", apila);
    print_test("esta vacia", pila_esta_vacia(p));
    print_test("despues de apilar-desapilar, ver tope es invalido", pila_ver_tope(p) == NULL);
    print_test("despues de apilar-desapilar, desapilar es invalido", pila_desapilar(p) == NULL);
    free(vector_elem);
    pila_destruir(p);
}

static void prueba_recien_creada(void)
{
    pila_t *p = pila_crear();
    print_test("recien creada, esta vacia", pila_esta_vacia(p));
    int *test = pila_ver_tope(p);
    print_test("recien creada, ver tope", test == NULL);
    test = pila_desapilar(p);
    print_test("recien creada, desapilar", test == NULL);
    pila_destruir(p);
}

static void prueba_apilar_null(void)
{
    pila_t *p = pila_crear();
    bool apila = pila_apilar(p, NULL);
    print_test("apilar da true", apila);
    int *test = pila_desapilar(p);
    print_test("apila NULL", test == NULL);
    pila_destruir(p);
}

void pruebas_pila_estudiante() {
    prueba_cola_vacia();
    prueba_crear_destruir();
    prueba_encolar_desencolar();
    prueba_volumen();
    prueba_recien_creada();
    prueba_encolar_null();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;
}

#endif
