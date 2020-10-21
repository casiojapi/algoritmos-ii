#include "pila.h"
#include "testing.h"

#define NULL (void *)0

static void prueba_pila_vacia(void) {
    pila_t *p = pila_crear();
    print_test("la pila fue creada", p != NULL);
    print_test("la pila esta vacia", pila_esta_vacia(p));
}

static void prueba_crear_destruir(void) {
    pila_t *p = pila_crear();
    print_test("la pila fue creada", p != NULL);
}

static void prueba_apilar_desapilar(void) {
    pila_t *p = pila_crear();
    int *elem;
    

}

void pruebas_pila_estudiante() {
    prueba_pila_vacia();
    prueba_crear_destruir();
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
