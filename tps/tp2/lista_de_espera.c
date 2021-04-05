#include <stdlib.h>
#include <stdio.h>
#include "cola.h"
#include "heap.h"
#include "hash.h"
#include "lista_de_espera.h"

struct lista_esp {
    cola_t* urgentes;
    heap_t* regulares;
    cmp_func_t cmp;
    size_t cantidad;
};

lista_esp_t* lista_esp_crear(cmp_func_t cmp){
    cola_t* cola = cola_crear();
    if (cola == NULL) return NULL;
    heap_t* heap = heap_crear(cmp);
    if (heap == NULL) {
        cola_destruir(cola, NULL);
        return NULL;
    }

    lista_esp_t* lista_esp = malloc(sizeof(lista_esp_t));
    if (lista_esp == NULL) {
        cola_destruir(cola, NULL);
        heap_destruir(heap, NULL);
        return NULL;
    }

    lista_esp->urgentes = cola;
    lista_esp->regulares = heap;
    lista_esp->cmp = cmp;
    lista_esp->cantidad = 0;
    return lista_esp;
}

size_t lista_esp_cantidad(lista_esp_t* lista_esp) {
    return lista_esp->cantidad;
}

bool lista_esp_turno_urgente(lista_esp_t* lista_esp, void* paciente) {
    if (paciente == NULL) return false;
    if (!cola_encolar(lista_esp->urgentes, paciente))
        return false;
    lista_esp->cantidad++;
    return true;
}

bool lista_esp_turno_regular(lista_esp_t* lista_esp, void* paciente) {
    if (paciente == NULL) return false;
    if (!heap_encolar(lista_esp->regulares, paciente))
        return false;
    lista_esp->cantidad++;
    return true;
}

void* lista_esp_siguiente(lista_esp_t* lista_esp) {
    if (lista_esp->cantidad == 0) return NULL;
    lista_esp->cantidad--;
    if (cola_esta_vacia(lista_esp->urgentes))
        return heap_desencolar(lista_esp->regulares);
    return cola_desencolar(lista_esp->urgentes);
}

void lista_esp_destruir(void* lista) {
    lista_esp_t* lista_esp = (lista_esp_t*)lista;
    cola_destruir(lista_esp->urgentes, NULL);
    heap_destruir(lista_esp->regulares, NULL);
    free(lista_esp);
}

especialidades_t* especialidades_crear() {
    hash_t* especialidades = hash_crear(lista_esp_destruir);
    if (especialidades == NULL) return NULL;
    return (especialidades_t*)especialidades;
}

void especialidades_destruir(especialidades_t* especialidades) {
    hash_destruir((hash_t*)especialidades);
}

bool especialidades_pertenece(especialidades_t* especialidades, char* especialidad) {
    return hash_pertenece((hash_t*)especialidades, especialidad);
}

bool especialidades_guardar(especialidades_t* especialidades, char* especialidad, void* dato) {
    return hash_guardar((hash_t*)especialidades, especialidad, dato);
}

void* especialidades_obtener(especialidades_t* especialidades, char* especialidad) {
    return hash_obtener((hash_t*)especialidades, especialidad);
}
