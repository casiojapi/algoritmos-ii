#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include "funciones_tp2.h"
#include "pacientes.h"
#include "doctores.h"
#include "lista_de_espera.h"
#include "comandos.h"
#include "mensajes.h"
#include "hash.h"
#include "cola.h"


// Funciones que se usan para procesar y ejecutar los comandos.

void pedir_turno(pacientes_t *pacientes, doctores_t *doctores, especialidades_t* listas_de_espera, char* nombre_paciente, char* especialidad, char* urgencia) {
    bool ok = true;
    if (!pacientes_pertenece(pacientes, nombre_paciente)) {
        printf(ENOENT_PACIENTE, nombre_paciente);
        ok = false;
    }
    if (!especialidades_pertenece(listas_de_espera, especialidad)) {
        printf(ENOENT_ESPECIALIDAD, especialidad);
        ok = false;
    }
    if ((strcmp("URGENTE", urgencia) || !strcmp("REGULAR", urgencia)) && (!strcmp("URGENTE", urgencia) || strcmp("REGULAR", urgencia))) {
        printf(ENOENT_URGENCIA, urgencia);
        ok = false;
    }
    if (ok) {
        lista_esp_t* lista_de_espera_actual = especialidades_obtener(listas_de_espera, especialidad);

        if (!strcmp("URGENTE", urgencia))
            lista_esp_turno_urgente(lista_de_espera_actual, pacientes_obtener(pacientes, nombre_paciente));
        else if (!strcmp("REGULAR", urgencia))
            lista_esp_turno_regular(lista_de_espera_actual, pacientes_obtener(pacientes, nombre_paciente));

        size_t cant_actual = lista_esp_cantidad(lista_de_espera_actual);
        printf(PACIENTE_ENCOLADO, nombre_paciente);
        printf(CANT_PACIENTES_ENCOLADOS, cant_actual, especialidad);
    }
}

// Atender siguiente
void atender_siguiente(doctores_t* doctores, char* nombre_doctor) {
    bool ok = true;
    doctor_t* doctor = doctores_buscar(doctores, nombre_doctor);
    if (!doctor) {
        printf(ENOENT_DOCTOR, nombre_doctor);
        ok = false;
    }
    if (ok) {
        char* especialidad = doctor_especialidad(doctor);
        especialidades_t *especialidades = doctores_obtener_especialidades(doctores);
        lista_esp_t* lista_de_espera = especialidades_obtener(especialidades, especialidad);
        paciente_t* paciente = lista_esp_siguiente(lista_de_espera);
        if (paciente == NULL) {
            printf(SIN_PACIENTES);
            return;
        }
        char* nombre_paciente = paciente_nombre(paciente);
        printf(PACIENTE_ATENDIDO, nombre_paciente);
        size_t cant_actual = lista_esp_cantidad(lista_de_espera);
        printf(CANT_PACIENTES_ENCOLADOS, cant_actual, especialidad);
        doctor_sumar_atendido(doctor);
    }
}


void informe_doctores(doctores_t* doctores, char* inicio, char* fin) {
    if (!strcmp(inicio, "")) inicio = NULL;
    if (!strcmp(fin, "")) fin = NULL;

    cola_t *cola_doctores = cola_crear();
    if(!cola_doctores) return;

    size_t cant_docs = 0;

    abb_iter_t* iter = abb_iter_in_crear(doctores_obtener_abb(doctores));
    if(!iter) {
        cola_destruir(cola_doctores, NULL);
        return;
    }

    while (inicio && !abb_iter_in_al_final(iter)) {
        doctor_t* doc = abb_iter_in_ver_actual(iter);
        if (strcmp(doctor_nombre(doc), inicio) >= 0) break;
        abb_iter_in_avanzar(iter);
    }

    while (!abb_iter_in_al_final(iter)) {
        doctor_t* doc = abb_iter_in_ver_actual(iter);
        if (fin && strcmp(doctor_nombre(doc), fin) > 0) break;
        if(!cola_encolar(cola_doctores, doc)){
            cola_destruir(cola_doctores, doctor_destruir);
            abb_iter_in_destruir(iter);
            return;
        }
        cant_docs++;
        abb_iter_in_avanzar(iter);
    }
    printf(DOCTORES_SISTEMA, cant_docs);
    for(size_t i = 1; !cola_esta_vacia(cola_doctores); i++){
          doctor_t *doc = cola_desencolar(cola_doctores);
          printf(INFORME_DOCTOR, i, doctor_nombre(doc), doctor_especialidad(doc), doctor_cant_atendidos(doc));
    }
    cola_destruir(cola_doctores, NULL);

    abb_iter_in_destruir(iter);
}
