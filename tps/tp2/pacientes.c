#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pacientes.h"
#include "csv.h"
#include "hash.h"
#include "mensajes.h"


// Struct y funciones para Paciente
struct paciente{
    char *nombre;
    int anio;
};

void paciente_destruir(void *dato){
    paciente_t *paciente = dato;
    free(paciente->nombre);
    free(paciente);
}

void *paciente_constructor(char** campos, void* extra){
      paciente_t *paciente = malloc(sizeof(paciente_t));
      if (!paciente) return NULL;

      char *nombre = strdup(campos[0]);
      char *end;
      int anio = (int)strtol(campos[1], &end, 10);
      if(*end != '\0'){
          free(paciente);
          printf(ENOENT_ANIO, campos[1]);
          return NULL;
      }
      paciente->nombre = nombre;
      paciente->anio = anio;

      return paciente;
 }

 char* paciente_nombre(paciente_t* paciente){
    return paciente->nombre;
 }

pacientes_t *pacientes_crear(const char* ruta_csv){
    pacientes_t *pacientes = hash_crear(paciente_destruir);
    if(!pacientes) return NULL;

    lista_t *lista_pacientes = csv_crear_estructura(ruta_csv, paciente_constructor, NULL);
    if (!lista_pacientes){
        hash_destruir(pacientes);
        return NULL;
    }
    while(!lista_esta_vacia(lista_pacientes)){
        paciente_t* paciente = lista_borrar_primero(lista_pacientes);
        if(!paciente || !hash_guardar(pacientes, paciente->nombre, paciente)){
            hash_destruir(pacientes);
            return NULL;
        }
    }
    lista_destruir(lista_pacientes, NULL);

    return pacientes;
}

paciente_t* pacientes_obtener(pacientes_t* pacientes, char* nombre_paciente) {
    return hash_obtener(pacientes, nombre_paciente);
}

bool pacientes_pertenece(pacientes_t* pacientes, char* nombre_paciente) {
    return hash_pertenece((hash_t*)pacientes, nombre_paciente);
}
void pacientes_destruir(pacientes_t *pacientes){
    hash_destruir(pacientes);
}

int cmp_anios_paciente(const void* p1, const void* p2) {
    paciente_t* paciente1 = (paciente_t*)p1;
    paciente_t* paciente2 = (paciente_t*)p2;

    if(paciente1->anio == paciente2->anio) return 0;
    if(paciente1->anio > paciente2->anio) return -1;
    return 1;
}
