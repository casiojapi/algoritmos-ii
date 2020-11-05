#include "lista.h"
#include "testing.h"

#include <stdlib.h>

#define TEST_ELEM 314159265
#define TEST_VOLUMEN 100000
#define TEST_ITER 777

// Pruebas para las primitivas de la lista

void prueba_crear_destruir(void) {
    lista_t* l = lista_crear();
    print_test("la lista 1 se creo correctamente", l);
    print_test("la lista 1 esta vacia", lista_esta_vacia(l));
    lista_destruir(l, NULL);

    lista_t*l_2 = lista_crear();
    print_test("la lista 2 fue creada", l_2);
    print_test("la lista 2 esta vacia", lista_esta_vacia(l_2));
    int* elem = malloc(sizeof(int));
    print_test("se creo el elemento de prueba", elem);
    bool inserta = lista_insertar_primero(l_2, elem);
    print_test("inserta - lista 2", inserta);
    int* check = lista_ver_primero(l_2);
    print_test("inserta correctamente - lista 2", elem == check);
    lista_destruir(l_2, NULL);
    free(elem);

    lista_t *l_3 = lista_crear();
    print_test("la lista 3 fue creada", l_3);
    print_test("la lista 3 esta vacia", lista_esta_vacia(l_3));
    int* elem_3 = malloc(sizeof(int));
    print_test("se creo el elemento de prueba", elem_3);
    inserta = lista_insertar_primero(l_3, elem_3);
    print_test("inserta primero - lista 3", inserta);
    int* check_3 = lista_ver_primero(l_3);
    print_test("inserta correctamente - lista 3", elem_3 == check_3);
    lista_destruir(l_3, free);

    lista_t*l_4 = lista_crear();
    print_test("la lista 4 fue creada", l_4);
    print_test("la lista 4 esta vacia", lista_esta_vacia(l_4));
    int* elem_4 = malloc(sizeof(int));
    print_test("se creo el elemento de prueba", elem_4);
    inserta = lista_insertar_ultimo(l_4, elem_4);
    print_test("inserta ultimo (en lista vacia) - lista 4", inserta);
    int* check_4 = lista_ver_primero(l_4);
    print_test("inserta correctamente - lista 4", elem_4 == check_4);
    lista_destruir(l_4, NULL);
    free(elem_4);
}

void prueba_insertar_eliminar(void) {
    lista_t *l = lista_crear();
    int *elem = malloc(sizeof(int));
    bool inserta = lista_insertar_primero(l, elem);
    print_test("insertar da true - 1", inserta);
    int* check = lista_ver_primero(l);
    print_test("inserta correctamente - 1", elem == check);
    int *elem_2 = malloc(sizeof(int));
    inserta = lista_insertar_ultimo(l, elem_2);
    print_test("insertar da true - 2", inserta);
    check = lista_ver_ultimo(l);
    print_test("inserta correctamente - 2", elem_2 == check);
    int* test = lista_borrar_primero(l);
    print_test("inserta int* - 1", test == elem);
    test = lista_borrar_primero(l);
    print_test("inserta int* - 2 ", test == elem_2);
    print_test("se mantiene invariante despues de insertar-desinsertar", lista_esta_vacia(l));
    lista_destruir(l, NULL);
    free(elem);
    free(elem_2);   
}
void prueba_volumen() {
    lista_t* l = lista_crear();
    size_t *arr = malloc(sizeof(size_t) * TEST_VOLUMEN);
    print_test("se crea el arreglo de prueba", arr);
    bool inserta = true;
    size_t* test; 
    for (size_t i = 0; i < TEST_VOLUMEN; i++) {
        arr[i] = i;
        if (!lista_insertar_primero(l, arr + i))
            inserta = false;
    }
    print_test("inserta en volumen", inserta);

    for (size_t i = TEST_VOLUMEN - 1 ; i > 0; i--) {
        test = lista_borrar_primero(l);
        if (*test != i)
            inserta = false;
    }
    print_test("borra en volumen", inserta);
    lista_destruir(l, NULL);
    free(arr);
}

void prueba_elemento_null(void) {
    lista_t* l = lista_crear();
    print_test("inserta NULL", lista_insertar_primero(l, NULL));
    print_test("ver primero NULL", !lista_ver_primero(l));
    print_test("ver ultimo NULL", !lista_ver_ultimo(l));
    print_test("elimina NULL", !lista_borrar_primero(l));
    print_test("vacia despues de NULL", lista_esta_vacia(l));
    lista_destruir(l, NULL);
}

// Pruebas para el iterador interno

bool incrementar(void* dato, void* extra) {
    return ++(*(size_t*)extra);
}

void prueba_iterador_interno(void) {
    lista_t* l = lista_crear();
    size_t* arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    size_t cont = 0;
    for (size_t i = 0; i < TEST_ITER; i++) {
        arr[i] = i * TEST_ITER;
        if (!lista_insertar_primero(l, arr + i))
            ok = false;
    }
    print_test("inserta los elementos", ok);
    lista_iterar(l, incrementar, &cont);
    print_test("itera correctamente", cont == TEST_ITER);
    lista_destruir(l, NULL);
    free(arr);
}

// Pruebas para el iterador externo

void prueba_iterador_agregar_principio(void) {

}

void pruebas_lista_estudiante() {
    prueba_crear_destruir();
    prueba_insertar_eliminar();
    prueba_elemento_null();
    prueba_volumen();
    prueba_iterador_interno();
    prueba_iterador_agregar_principio();
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_lista_estudiante();
    return failure_count() > 0;
}

#endif
