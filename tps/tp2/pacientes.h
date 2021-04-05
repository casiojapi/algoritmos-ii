#ifndef PACIENTES_H
#define PACIENTES_H
#include "hash.h"
#include "abb.h"

// Funciones y estructuras que se usan para almacenar y utilizar la informacion de los pacientes.

typedef struct paciente paciente_t;
typedef hash_t pacientes_t;

// libera la memoria asociada a la estrucura de el paciente dado por parametro.
// Pre: recibe una estructura de paciente valida.
// Post: libera toda la memoria asociada a la estrucura del paciente dado correctamente.
void paciente_destruir(void *dato);

// Funcion que crea una estructura de paciente a partir de los campos que entran como comando.
// Pre: recibe campos validos.
// Post: crea una estructura de pacientes con sus atributos respectivos correctamente.
void *paciente_constructor(char** campos, void* extra);

//Devuelve el nombre del paciente.
//Pre: recibe un paciente valido.
//Post: se devuelve la cadena del nombre del paciente.
char* paciente_nombre(paciente_t* paciente);

// Crea una estructra de pacientes a partir de una ruta csv.
// Pre: recibe una ruta de un archivo csv valida
// Post: crea una estructura con todos los pacientes en el archivo csv correctamente.
pacientes_t *pacientes_crear(const char* ruta_csv);

// Recibe una estructura de pacientes, y obitene y devuelve al estructura del paciente dado por parametro.
// Pre: recibe una estructura de pacientes valida, y una cadena con un nombre de paciente valido.
// Post: devuelve el paciente dado por parametro, o NULL en caso de no existir.
paciente_t* pacientes_obtener(pacientes_t* pacientes, char* nombre_paciente);

// Devuelve true si el paciente dado por parametro existe en la estructura de pacientes dada.
// Pre:; recibe una estructura de pacientes valida, y un string con el nombre del paciente a buscar valido.
// Post: devuelve true en caso de que el paciente pertenezca, false en caso contrario.
bool pacientes_pertenece(pacientes_t* pacientes, char* nombre_paciente);

// Destruye la estructura de pacientes dada por parametro.
// Pre: recibe una estructura de pacientes valida.
// Post: libera toda la memoria asociada a la estructura dada por parametro.
void pacientes_destruir(pacientes_t *pacientes);

// funcion de comparacion de anios entre pacientes.
// Pre: recibe 2 pacientes validos.
// Post: los compara, devolviendo 0 si son iguales, 1 si p1 > p1, y -1 si p1 < p2
int cmp_anios_paciente(const void* p1, const void* p2);

#endif
