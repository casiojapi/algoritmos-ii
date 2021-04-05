#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "doctores.h"
#include "hash.h"
#include "csv.h"
#include "mensajes.h"
#include "pacientes.h"

struct doctor{
    char *nombre;
    char *especialidad;
    size_t cant_atendidos;
};

struct doctores{
    abb_t* abb_doctores;
    hash_t* especialidades;
    size_t cant_docs;
};

void doctor_destruir(void *dato){
    doctor_t *doctor = dato;
    free(doctor->nombre);
    free(doctor->especialidad);
    free(doctor);
}

char* doctor_especialidad(doctor_t *doctor){
    return doctor->especialidad;
}

char* doctor_nombre(doctor_t *doctor) {
    return doctor->nombre;
}

size_t doctor_cant_atendidos(doctor_t *doctor){
    return doctor->cant_atendidos;
}

void doctor_sumar_atendido(doctor_t* doctor) {
    doctor->cant_atendidos++;
}



void *constructor_doctor(char** campos, void* espec){
    doctor_t *doctor = malloc(sizeof(doctor_t));
    if (!doctor) return NULL;

    char *nombre = strdup(campos[0]);
    char *especialidad = strdup(campos[1]);

    doctor->nombre = nombre;
    doctor->especialidad = especialidad;
    doctor->cant_atendidos = 0;
    if (!especialidades_pertenece(espec, especialidad)) {
        lista_esp_t* nueva_lista = lista_esp_crear(cmp_anios_paciente);
        if (nueva_lista == NULL) return NULL;
        especialidades_guardar(espec, especialidad, nueva_lista);
    }
    return doctor;
}



doctores_t *doctores_crear(const char* ruta_csv, especialidades_t *especialidades){
    doctores_t *doctores = malloc(sizeof(doctores_t));
    if (!doctores) return NULL;
    abb_t *abb_doctores = abb_crear(strcmp, doctor_destruir);
    if(!abb_doctores){
        free(doctores);
        return NULL;
    }

    lista_t *lista_doctores = csv_crear_estructura(ruta_csv, constructor_doctor, especialidades);
    if (!lista_doctores){
        abb_destruir(abb_doctores);
        hash_destruir(especialidades);
        free(doctores);
        return NULL;
    }
    doctores->especialidades = especialidades;
    doctores->cant_docs = 0;

    while(!lista_esta_vacia(lista_doctores)){
        doctor_t* doctor = lista_borrar_primero(lista_doctores);
        if(!doctor || !abb_guardar(abb_doctores, doctor->nombre, doctor)){
            abb_destruir(abb_doctores);
            free(doctores);
            return NULL;
        }
        doctores->cant_docs++;
    }
    lista_destruir(lista_doctores, NULL);
    doctores->abb_doctores = abb_doctores;

    return doctores;
}


void doctores_destruir(doctores_t *doctores){
    abb_destruir(doctores->abb_doctores);
    free(doctores);
}

doctor_t* doctores_buscar(doctores_t *doctores, char* nombre) {
    doctor_t *doctor = abb_obtener(doctores->abb_doctores, nombre);
    return doctor;
}

abb_t* doctores_obtener_abb(doctores_t* doctores) {
    return doctores->abb_doctores;
}

especialidades_t *doctores_obtener_especialidades(doctores_t* doctores){
    return doctores->especialidades;
}

size_t doctores_cantidad(doctores_t* doctores) {
    return doctores->cant_docs;
}
