#ifndef COMANDOS_H
#define COMANDOS_H

#include "lista_de_espera.h"

// La funcion pide un turno para el paciente dado por parametro en su cola correspondiente a su urgencia y especialidad. 
// Recibe una estructura con todos los pacientes, otra con todos los doctores, una estructura que guarda todas las especialidades disponibles, el nombre del paciente, la especialidad requerida por el paciente y la urgencia del turno.
// Pre: recibe todas las estructuras validas e inicializadas, y cada cadena debe ser valida. 
// Post: Encola al paciente en la lista de espera correspondiente a su especialidad, y a su urgencia. 
void pedir_turno(pacientes_t* pacientes, doctores_t* doctores, especialidades_t* listas_de_espera, char* nombre_paciente, char* especialidad, char* urgencia);

// La funcion hace que el doctor dado por parametro atienda al siguiente paciente en su lista de espera correspondiente. En caso de no haber pacientes esperando. No atiende a nadie.
// Recibe una estructura con todos los doctores disponibles y el nombre del doctor a atender. 
// Pre: recibe una estructura de doctores valida, y una cadena con el nombre del doctor valida. 
// Post: atiende al pacciente correspondiente segun su prioridad, orden de llegada y/o antiguedad en la clinica. 
void atender_siguiente(doctores_t* doctores, char* nombre_doctor);

// La Funcion imprime desde un doctor "inicio", hasta un doctor "fin", todos los doctores que hay registrados, con su numero de pacientes atendidos correspondientes. 
// Pre: recibe una estructura de doctores valida.
// Pre: recibe dos strings "inicio" y "fin", validos de doctores existentes. 
// Post: imprime correctamente todo el rango de doctores pedido por parametro, con la informacion adicional correspondiente. 
void informe_doctores(doctores_t* doctores, char* inicio, char* fin);

#endif
