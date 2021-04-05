#ifndef DOCTORES_H
#define DOCTORES_H

#include "abb.h"
#include "lista_de_espera.h"

// Funciones y estructuras para almacenar y utilizar la informacion de los doctores.

typedef struct doctor doctor_t;
typedef struct doctores doctores_t;

// Recibe un struct doctor, y libera la memoria asociada a el.
// Pre: recibe un doctor válido
// Post: se libero toda la memoria asociada al doctor.
void doctor_destruir(void *dato);

// Recibe un struct doctor, y devuelve una cadena con su especialidad.
// Pre: recibe un doctor valido.
// Post: devuelve la especialidad del doctor pedido correctamente.
char* doctor_especialidad(doctor_t* doctor);

// Recibe un struct doctor, y devuelve una cadena con su nombre.
// Pre: recibe un doctor valido.
// Post: devuelve el nombre del doctor pedido correctamente.
char* doctor_nombre(doctor_t *doctor);

// Recibe un struct doctor, y devuelve un size_t con la cantidad de pacientes atendidos por ese doctor.
// Pre: recibe un doctor valido.
// Post: devuelve la cantidad de pacientes atendidos por el doctor dado correctamente.
size_t doctor_cant_atendidos(doctor_t *doctor);

// Recibe un struct doctor, y agrega un atendido a su contador de pacientes atendidos.
// Pre: recibe un doctor valido
// Post: el doctor atendio un paciente mas.
void doctor_sumar_atendido(doctor_t* doctor);

// Recibe los campos que entran como comando, y una estructura de datos que almacena todas las especialidades. (en este caso un hash).
// Y a partir de lo mencionado, crea el struct doctor con toda la informacion asociada al mismo necesaria. Y en caso de no tener antes registrada la especialidad, la agrega a la estructura de especialidades.
// Pre: recibe campos y especialidades validas.
// Post: Devuelve un struct doctor con toda su informacion respectiva.
// Post: agrega la especialidad en caso de estar en la estructura de especialidades anteriormente
void *constructor_doctor(char** campos, void* espec);

// Primitivas doctorES

// Crea una estructura de datos a partir de la ruta_csv para doctores y la estructura de especialidades, almacenando cada doctor en la dicha estructura.
// Pre: recibe una ruta al archivo csv valida.
// Post: creo correctamente la estructura con todos los doctores en el archivo csv.
doctores_t *doctores_crear(const char* ruta_csv, especialidades_t *especialidades);

// Destruye la estructua de doctores.
// Pre: recibe una estructura valida de doctores.
// Post: libera toda la memoria asociada a la estructura de doctores correctamente.
void doctores_destruir(doctores_t *doctores);

// Recibe un string con el nombre del doctor a buscar y lo busca dentro de una estructura de doctores dada. En caso de no estar, devuelve NULL.
// Pre: recibe una estructura de doctores valida e inicializada.
// Pre: recibe un nombre valido.
// Post: devuelve la estructura del doctor pedido, en caso de no existir, devuelve NULL
doctor_t* doctores_buscar(doctores_t *doctores, char* nombre);

// Devuelve el abb de doctores asociado a la estructura de doctores.
// Pre: recibe una estructura de doctores valida.
// Post: devuelve el abb asociado a la estructura de doctores correctamente.
abb_t* doctores_obtener_abb(doctores_t* doctores);

//Devuelve la estructura de especialidades asociada a la estructura de doctores.
// Pre: recibe una estructura de doctores valida.
// Post: devuelve la estructura de especialidades asociada a la estructura de doctores correctamente.
especialidades_t *doctores_obtener_especialidades(doctores_t* doctores);

// Devuelve la cantidad de doctores que hay en la estructura de doctores dada por parametro.
// Pre: recibe una estructura de doctores valida.
// Post: devuelve un size_t con la cantidad de doctores en la estructura dada correctamente.
size_t doctores_cantidad(doctores_t* doctores);

#endif
