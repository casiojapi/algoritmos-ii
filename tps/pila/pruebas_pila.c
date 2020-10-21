#include "pila.h"
#include "testing.h"

#include <stdlib.h>

#define TEST_ELEM 1618033

static void prueba_pila_vacia(void) {
    pila_t *p = pila_crear();
    print_test("la pila fue creada", p != NULL);
    print_test("la pila esta vacia", pila_esta_vacia(p));
    pila_destruir(p);
}

static void prueba_crear_destruir(void) {
    pila_t *p = pila_crear();
    print_test("la pila fue creada", p != NULL);
}

static void prueba_apilar_desapilar(void) {
    pila_t *p = pila_crear();
    int *elem = malloc(sizeof(int));
    *elem = TEST_ELEM;
    pila_apilar(p, elem);
    int *test = malloc(sizeof())
    print_test("apila int *?", (int *)pila_desapilar(p) == *elem);
    pila_apilar(p, NULL);
    print_test("apila NULL?", pila_desapilar(p) == NULL);
}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_crear_destruir();
    prueba_apilar_desapilar();
    prueba_apilar_desapilar();
}


/*
 * Función main() que llama a la función de pruebas.
 */

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_pila_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
