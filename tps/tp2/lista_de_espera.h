#ifndef LISTA_DE_ESPERA_H
#define LISTA_DE_ESPERA_H

#include <stdbool.h>
#include "heap.h"
#include "hash.h"
//typedef int (*cmp_func_t)(const void *a, const void *b);
// La estructura de datos "lista_esp", o sea lista de espera, se implemento para guardar mas eficazmente a los pacientes de cada especialidadd en una cola discriminando por urgencia, orden de llegada y antiguedad en la clinica.
// Internamente se uso un cola (URGENTE) y un heap de minimos (REGULAR). (mas detalles en el informe.)
typedef struct lista_esp lista_esp_t;
typedef void (*destruir_dato_t)(void *);

// Crea una lista de espera, recibe una funcion de comparacion para ordenar internamente los pacientes no urgentes.
// Pre: recibe una funcion de comparacion valida.
// Post: se crea corretamente la lista de espera.
lista_esp_t* lista_esp_crear(cmp_func_t cmp);

// Devuelve la cantidad de pacientes esperando a ser atendidos en una lista de espera.
// Pre: recibe una lista de espera valida.
// Post: devuelve la cantidad de pacientes esperando en la lista de espera correctamente.
size_t lista_esp_cantidad(lista_esp_t* lista_esp);

// Ingresa (encola) un paciente urgente a una lista de espera dada.
// Pre: recibe una lista de espera valida y un paciente valido.
// Post: encola correctamente al paciente urgente en la lista de espera.
bool lista_esp_turno_urgente(lista_esp_t* lista_esp, void* paciente);

// Ingresa (encola) un paciente regular a una lista de espera dada.
// Pre: recibe una lista de espera valida y un paciente valido.
// Post: encola correctamente al paciente regular en la lista de espera.
bool lista_esp_turno_regular(lista_esp_t* lista_esp, void* paciente);

// Destruye la lista de espera dada por parametro.
// Pre: recibe una lisa de espera valida.
// Post: libera toda la memoria asociada a la lista dada por parametro.
void lista_esp_destruir(void* lista);

// desencola al siguiente paciente en la lista de espera, discriminando por urgencia, orden de llegada y antiguedad en la clinica.
void* lista_esp_siguiente(lista_esp_t* lista_esp);

// Usamos un hash para guardar cada especialidad, con su lista de espera respectiva como dato.
typedef hash_t especialidades_t;

// Crea una estructura de especialidades.
// Post: devuelve una estructura de especialidades correctamente.
especialidades_t* especialidades_crear();

// Libera la memoria asociada a la estructura de especialidades dada por parametro.
// Pre: recibe una estrucura de especialidades valida.
// Post: libera toda la memoria asociada a la estructura de especialidades dada por parametro.
void especialidades_destruir(especialidades_t* especialidades);

// Devuelve true en caso de que la especialidad dada por parametro pertenzca a la estructura de especialidades, y false en caso contrario.
// Pre: recibe una estructura de especialidades y una especialidad valida.
// Post: devuelve truue en caso de que la especialidad dada se encuentre en la estrucura, y false ne caso contrario.
bool especialidades_pertenece(especialidades_t* especialidades, char* especialidad);

// Guarda la espcialidad dada por paramaetro con su dato asociado en la estructura de especialidades.
// Pre: recibe una estructura de espcialidaes valida, una cadena con una especialidad valida y un dato.
// Post: Devuelve true en caso de haber guardado todo correctamente, false en caso contrario.
bool especialidades_guardar(especialidades_t* especialidades, char* especialidad, void* dato);

// Obtiene el dato asociado a una especialidad dada por parametro, de la estructura de especialidades.
// Pre: recibe una estructura de especialidades valida y una cadena con una espcialidad valida.
// Post: devuelve el dato asociado a la especialidad dada correctamente. En caso de que la especialidad dada no pertenezca, devuelve NULL.
void* especialidades_obtener(especialidades_t* especialidades, char* especialidad);

#endif
