#include "pila.h"
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
    int elem = TEST_ELEM;
    bool apila = pila_apilar(p, &elem);
    print_test("apila correctamente", apila);
    int *test = pila_desapilar(p);
    print_test("apila int *", *test == elem);
    apila = pila_apilar(p, NULL);
    print_test("apila correctamente", apila);
    test = pila_desapilar(p);
    print_test("apila NULL", test == NULL);
    print_test("se mantiene invariante despues de apilar-desapilar", pila_esta_vacia(p));
    pila_destruir(p);
}

static void prueba_destruir(void)
{
    pila_t *p = pila_crear();
    int **vec = malloc(sizeof(int *) * 50);
    for (int i = 0; i < 50; i++)
    {
        vec[i] = malloc(sizeof(int));
        *(vec[i]) = i;
        pila_apilar(p, vec[i]);
    }
    for (size_t i = 0; i < 50; i++)
    {
        free(vec[i]);
    }
    free(vec);
    pila_destruir(p);
}

static void prueba_volumen(void)
{
    bool test = true;
    pila_t *p = pila_crear();

    for (size_t i = 0; i < TEST_VOLUMEN; i++)
    {
        size_t *elem = malloc(sizeof(size_t));
        *elem = i;
        bool apila = pila_apilar(p, elem);
        if (!apila)
            fprintf(stderr, "no apila\n");
        size_t *copia = pila_ver_tope(p);
        if (*copia != *elem)
            test = false;
    }

    print_test("apila volumen", test);

    test = true;

    for (size_t i = 0; i < TEST_VOLUMEN; i++)
    {
        size_t *copia = pila_ver_tope(p);
        size_t *elem_post = pila_desapilar(p);
        if (*copia != *elem_post)
            test = 0;
        free(copia);
    }
    print_test("desapila volumen", test);
    print_test("esta vacia", pila_esta_vacia(p));
    print_test("despues de apilar-desapilar, ver tope es invalido", pila_ver_tope(p) == NULL);
    print_test("despues de apilar-desapilar, desapilar es invalido", pila_desapilar(p) == NULL);
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

//static void prueba_apilar_null(void);

void pruebas_pila_estudiante()
{
    prueba_pila_vacia();
    prueba_destruir();
    prueba_crear_destruir();
    prueba_apilar_desapilar();
    prueba_volumen();
    prueba_recien_creada();
}

/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR // Para que no dé conflicto con el main() del corrector.

int main(void)
{
    pruebas_pila_estudiante();
    return failure_count() > 0; // Indica si falló alguna prueba.
}

#endif
