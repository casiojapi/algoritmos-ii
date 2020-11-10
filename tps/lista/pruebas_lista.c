#include "lista.h"
#include "testing.h"

#include <stdlib.h>
#include <stdio.h>

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
    lista_destruir(l_4, free);
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

void prueba_volumen_primero() {
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

void prueba_volumen_ultimo() {
    lista_t* l = lista_crear();
    size_t *arr = malloc(sizeof(size_t) * TEST_VOLUMEN);
    print_test("se crea el arreglo de prueba", arr);
    bool inserta = true;
    size_t* test; 
    for (size_t i = 0; i < TEST_VOLUMEN; i++) {
        arr[i] = i;
        if (!lista_insertar_ultimo(l, arr + i))
            inserta = false;
    }
    print_test("inserta en volumen", inserta);

    for (size_t i = 0; i < TEST_VOLUMEN; i++) {
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
bool iterar_primeros_5(void* dato, void* extra) {
    return (*(size_t*)extra)++ < 4;
}

bool incrementar(void* dato, void* extra) {
    return ++(*(size_t*)extra);
}

bool es_primo(size_t n) {   // no le des importancia a la funcion en si, la idea era chequear si cortaba bien. 
    if (n < 2) return false;
    for (size_t i = 2; i < n/2; i++)   
        if (!(n % i)) return false;
    return true;
}

bool hasta_primo(void* dato, void* extra) {
    *((size_t*)extra) = *((size_t*)dato);
    return !es_primo(*(size_t*)dato);
}

void prueba_iterador_interno_sin_corte(void) {
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

void prueba_iterador_interno_con_corte(void) {
    lista_t* l = lista_crear();
    size_t* arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    size_t cont = 0;
    for (size_t i = 0; i < TEST_ITER; i++) {
        arr[i] = i;
        if (!lista_insertar_primero(l, arr + i))
            ok = false;
    }
    print_test("inserta los elementos", ok);
    lista_iterar(l, iterar_primeros_5, &cont);
    print_test("itera correctamente", cont == 5);
    lista_destruir(l, NULL);
    free(arr);
}

void prueba_interno_hasta_es_primo(void) {
    lista_t* l = lista_crear();
    size_t* arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    size_t n;
    for (size_t i = 0; i < TEST_ITER; i++) {
        arr[i] = i * 5 + 111;
        if (!lista_insertar_primero(l, arr + i))
            ok = false;
    }
    print_test("inserta los elementos", ok);
    lista_iterar(l, hasta_primo, &n);
    print_test("itera hasta el primer primo", es_primo(n));
    lista_destruir(l, NULL);
    free(arr);
}
// Pruebas para el iterador externo

void prueba_iterador_agregar_principio(void) {
    lista_t* l = lista_crear();
    lista_iter_t* iter = lista_iter_crear(l);
    int elem = TEST_ELEM;
    print_test("iterador inserta correctamente", lista_iter_insertar(iter, &elem));
    print_test("ver actual es lista->prim", lista_ver_primero(l) == lista_iter_ver_actual(iter));
    lista_iter_destruir(iter);
    lista_destruir(l, NULL);
}

void prueba_iterador_agregar_principio_no_vacia(void) {
    lista_t* l = lista_crear();

    size_t* arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    for (size_t i = 0; i < TEST_ITER; i++) {
        arr[i] = i * 5 + 111;
        if (!lista_insertar_primero(l, arr + i))
            ok = false;
    }
    print_test("inserta los elementos", ok);
    lista_iter_t* iter = lista_iter_crear(l);
    int elem = TEST_ELEM;
    print_test("iterador inserta correctamente", lista_iter_insertar(iter, &elem));
    print_test("ver actual es lista->prim", lista_ver_primero(l) == lista_iter_ver_actual(iter));
    lista_iter_destruir(iter);
    lista_destruir(l, NULL);
    free(arr);
}

void prueba_iterador_agregar_final(){
    lista_t* l = lista_crear();
    lista_iter_t* iter = lista_iter_crear(l);
    size_t *arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    bool avanza = true;
    for (size_t i = 0; i < TEST_ITER; i++){
        arr[i] = i;
        if (!lista_iter_insertar(iter, arr + i))
            ok = false;
        if (!lista_iter_avanzar(iter))
            avanza = false;
    }
    print_test("inserta correctamente", ok);
    print_test("avanza correctamente", avanza);

    print_test("iterador esta en el final", lista_iter_al_final(iter));
    size_t *al_final = malloc(sizeof(size_t));
    *al_final = TEST_ELEM;
    print_test("inserta por iter al final", lista_iter_insertar(iter, al_final));
    size_t* test_iter = lista_ver_ultimo(l);
    print_test("agrega el mismo elemento (lista insertar ultimo)", lista_insertar_ultimo(l, al_final));
    size_t* test_lista = lista_ver_ultimo(l);
    print_test("iter al final es equivalente a insertar ultimo", test_iter == test_lista);
    lista_destruir(l, NULL);
    free(al_final);
    free(arr);
    lista_iter_destruir(iter);
}

void prueba_agregar_medio(){
    lista_t* l = lista_crear();
    lista_iter_t* iter = lista_iter_crear(l);
    size_t *arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    for (size_t i = 0; i < TEST_ITER; i++){
        if (!lista_iter_insertar(iter, arr + i))
            ok = false;
    }
    print_test("inserta correctamente", ok);
    ok = true;

    for (size_t i = 0; i < TEST_ITER / 2; i++) {
        if (!lista_iter_avanzar(iter))
            ok = false;
    }
    print_test("avanza correctamente", ok);
    int elem = TEST_ITER;
    ok = lista_iter_insertar(iter, &elem);
    print_test("inserta correctamente", ok);

    lista_iter_t* iter_2 = lista_iter_crear(l);
    for (size_t i = 0; i < TEST_ITER / 2; i++) {
        if (!lista_iter_avanzar(iter_2))
            ok = false;
    }
    void* test = lista_iter_ver_actual(iter_2);
    print_test("avanza correctamente", ok);
    print_test("inserta en el medio", &elem == test);
    lista_iter_destruir(iter);
    lista_iter_destruir(iter_2);
    lista_destruir(l, NULL);
    free(arr);
}

void prueba_cambia_prim(){
    lista_t* l = lista_crear();
    lista_iter_t* iter = lista_iter_crear(l);
    size_t elem = TEST_ITER;
    int* antes = lista_ver_primero(l);
    print_test("inserta", lista_iter_insertar(iter, &elem));
    int* desp = lista_ver_primero(l);
    print_test("cambia prim", antes != desp);
    antes = lista_iter_ver_actual(iter);
    void* borrado = lista_iter_borrar(iter);
    print_test("borra el elemento deseado", borrado == antes);
    print_test("cambia prim - post", lista_ver_primero(l) != desp);
    lista_destruir(l, NULL);
    lista_iter_destruir(iter);
}

void prueba_cambia_ult(){
    lista_t* l = lista_crear();
    lista_iter_t* iter = lista_iter_crear(l);
    size_t *arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    bool avanza = true;
    for(size_t i = 0; i < TEST_ITER; i++) {
        arr[i] = i;
        if (!lista_iter_insertar(iter, arr + i))
            ok = false;
        if (i < TEST_ITER -1 && !lista_iter_avanzar(iter))
            avanza = false;
    }
    print_test("inserta correctamente", ok);
    print_test("avanza correctamente", avanza);
    size_t* antes = lista_ver_ultimo(l);
    size_t* borrado = lista_iter_borrar(iter);
    print_test("borra el elemento deseado", antes == borrado);
    size_t* despues = lista_ver_ultimo(l);
    print_test("cambia ult", antes != despues);
    lista_destruir(l, NULL);
    lista_iter_destruir(iter);
    free(arr);
}

void prueba_eliminar_elemento_medio(){
    lista_t* l = lista_crear();
    lista_iter_t* iter = lista_iter_crear(l);
    size_t *arr = malloc(sizeof(size_t) * TEST_ITER);
    bool ok = true;
    bool avanza = true;

    for(size_t i = 0; i < TEST_ITER; i++){
        arr[i] = i;
        if (!lista_iter_insertar(iter, arr + i))
            ok = false;
        if (i < TEST_ITER / 2)
            avanza = lista_iter_avanzar(iter);
    } 
    print_test("inserta correctamente", ok);
    print_test("avanza correctamente", avanza);
    size_t* antes = lista_iter_ver_actual(iter);
    void* borrado = lista_iter_borrar(iter);
    print_test("borra el elemento correcto", borrado == antes);
    size_t* despues = lista_iter_ver_actual(iter);
    print_test("elemento eliminado no esta mas", despues != antes);
    free(arr);
    lista_destruir(l, NULL);
    lista_iter_destruir(iter);
}


void pruebas_lista_estudiante() {
    prueba_crear_destruir();
    prueba_insertar_eliminar();
    prueba_elemento_null();
    prueba_volumen_primero();
    prueba_volumen_ultimo();
    prueba_iterador_interno_sin_corte();
    prueba_iterador_interno_con_corte();
    prueba_iterador_agregar_principio();
    prueba_iterador_agregar_final();
    prueba_iterador_agregar_principio_no_vacia();
    prueba_agregar_medio();
    prueba_cambia_prim();
    prueba_cambia_ult();
    prueba_eliminar_elemento_medio();
    prueba_interno_hasta_es_primo();
}

#ifndef CORRECTOR

int main(void)
{
    pruebas_lista_estudiante();
    return failure_count() > 0;
}

#endif
