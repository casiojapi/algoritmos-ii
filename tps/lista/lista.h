#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>


/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* Se trata de una lista que contiene datos de tipo void*
 * (punteros genéricos).  La lista en sí está definida en el .c.  */

struct lista;  // Definición completa en lista.c.
typedef struct lista lista_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA lista
 * *****************************************************************/

// Crea una lista.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Destruye la lista.
// Pre: la lista fue creada.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista);

// Devuelve verdadero si la lista no tiene elementos alistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor es el nuevo tope.
bool lista_alistar(lista_t *lista, void *valor);

// Obtiene el valor del tope de la lista. Si la lista tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del tope de la lista, cuando la lista no está
// vacía, NULL en caso contrario.
void *lista_ver_tope(const lista_t *lista);

// Saca el elemento tope de la lista. Si la lista tiene elementos, se quita el
// tope de la lista, y se devuelve ese valor. Si la lista está vacía, devuelve
// NULL.
// Pre: la lista fue creada.
// Post: si la lista no estaba vacía, se devuelve el valor del tope anterior
// y la lista contiene un elemento menos.
void *lista_desalistar(lista_t *lista);


/* *****************************************************************
 *                    PRUEBAS PARA LA lista
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_lista.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct lista).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test(), como se ha visto en TPs anteriores.
void pruebas_lista_estudiante(void);

#endif  // _lista_H
