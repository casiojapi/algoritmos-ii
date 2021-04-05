#ifndef LISTA_H
#define LISTA_H
#include <stdbool.h>
#include <stdlib.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* La lista está planteada como una lista simplemente enlazada de punteros genéricos. */

typedef struct lista lista_t;

//Iterador externo de la lista.

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
// Crea una lista.
// Post: devuelve una nueva lista vacía, en el caso de fallar devuelve NULL.
lista_t *lista_crear(void);

// Devuelve true si la lista no tiene elementos, false en caso contrario.
// Pre: La lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un elemento nuevo al principio de la lista, siendo el nuevo primero de la lista.
// Pre: La lista fue creada.
// Post: devuelve true si se pudo insertar correctamente, o false en el caso contrario.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un elemento nuevo al final de la lista, siendo el nuevo último de la lista.
// Pre: La lista fue creada.
// Post: devuelve true si se pudo insertar correctamente, o false en el caso contrario.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista y lo devuelve. En el caso de que la lista esté vacía, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se eliminó el primer elemento y se devolvió su valor.
void *lista_borrar_primero(lista_t *lista);

// Devuelve el primer elemento de la lista. En el caso de que la lista esté vacía, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el primer elemento de la lista, o NULL si estaba vacía.
void *lista_ver_primero(const lista_t *lista);

// Devuelve el último elemento de la lista. En el caso de que la lista esté vacía, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvió el último elemento de la lista, o NULL si estaba vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista.
// Pre: La lista fue creada.
size_t lista_largo(const lista_t *lista);


// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* ******************************************************************
 *                    PRIMITIVA DEL ITERADOR INTERNO
 * *****************************************************************/

// Recorre la lista recibida hasta que ésta termine o la funcion visitar devuelva false (condición de corte).
// A cada elemento iterado se le aplica la función visitar.
// Pre: La lista fue creada.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* ******************************************************************
*                    PRIMITIVAS DEL ITERADOR EXTERNO
* *****************************************************************/

// Devuelve el iterador externo de la lsita, o NULL en caso de que falle.
// Pre: La lista fue creada.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza el iterador una posición a lo largo de la lista. Si llegó al final (luego del último elemento) devuelve false, caso contrario devuelve true.
// Pre: El iterador fue creado.
// Post: El iterador se encuentra posicionado en el elemento siguiente en el que estaba antes.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el elemento en la posición actual de la lista.
// Pre: El iterador fue creado.
// Post: Se devolvió el elemento de la lista en la posición actual del iterador. Si estaba al final, devuelve NULL.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Devuelve false si no se llegó al final de la lista, o true en el caso contrario.
// Pre: El iterador fue creado.
bool lista_iter_al_final(const lista_iter_t *iter);

// Pre: El iterador fue creado.
// Post: El iterador fue destruido.
void lista_iter_destruir(lista_iter_t *iter);


// Pre: El iterador fue creado.
// Post: Se insertó un elemento en la posición anterior a la actual. EL iterado se posicionó en la posición del elemento agregado.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Pre: El iterador fue creado.
// Post: Se eliminó el elemento en la posición del iterador. El iterador se posicionó en el siguiente elemento del borrado.
void *lista_iter_borrar(lista_iter_t *iter);

/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación realizada.
//
// Las pruebas deben emplazarse en el archivo ‘pruebas_lista.c’, y
// solamente pueden emplear la interfaz pública tal y como aparece en lista.h
// (esto es, las pruebas no pueden acceder a los miembros del struct cola).
//
// Para la implementación de las pruebas se debe emplear la función
// print_test().
void pruebas_lista_estudiante(void);

#endif  // LISTA_H
