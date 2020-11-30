#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


/* *****************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

/* Se trata de una lista que contiene datos de tipo void*
 * (punteros genéricos).  La lista en sí está definida en el .c.  */

struct lista;  // Definición completa en lista.c.
typedef struct lista lista_t;


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// Crea una lista. En caso de error de memoria, devuelve NULL.
// Post: devuelve una nueva lista vacía.
lista_t *lista_crear(void);

// Devuelve verdadero si la lista no tiene elementos alistados, false en caso contrario.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento en el primer lugar de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento en el ultimo lugar de la lista. Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el tamaño de la lista.
// Pre: la lista fue creada.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void (*destruir_dato)(void *));

/* *****************************************************************
 *                    PRIMITIVAS ITERADOR INTERNO
 * *****************************************************************/

// Recibe una lista, itera sobre ella y aplica una funcion "visitar" a cada uno de los datos en la lista.
// Deja de iterar en el instante en el cual la funcion visitar devuelva false o se llegue al final de la lista.
// Pre: la lista fue creada, recibe una funcion visitar valida.
// Post: se aplico la funcion por sobre cada elemento hasta que "visitar" devolvio false, o se llego al final de la lista.
 void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

/* *****************************************************************
 *                    PRIMITIVAS ITERADOR EXTERNO
 * *****************************************************************/

typedef struct lista_iter lista_iter_t;


// Recibe una lista, y crea un iterador externo para ella. 
// En el caso de una falla de memoria, devuelve NULL.
// Pre: la lista fue previamente creada.
// Post: devuelve un iterador externo apuntando al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Recibe un iterador externo y avanza un elemento, devuelve true si logra avanzar.
// Devuelve false en caso de que el iterador se encuentre originalmente en el final de la lista. 
// Pre: el iterador fue creado previamente. 
// Post: el iterador avanza una posicion de la lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Recibe un iterador externo y devuelve el dato que contiene el nodo actual.
// Devuelve NULL en caso de estar al final de la lista.
// Pre: el iterador fue creado previamente. 
// Post: devuelve correctamente el dato apuntado por el nodo actual. 
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Recibe un iterador y devuelve true si se encuentra en el final de la lista.
// Devuelve false en el caso contrario. 
// Una iterador se encuentra en el final de una lista si su nodo actual apunta a NULL.
// Pre: el iterador fue previamente creado. 
// Post: devuelve correctamente si esta o no en el final.
bool lista_iter_al_final(const lista_iter_t *iter);

// Recibe un iterador y libera su memoria. 
// Pre: el iterador fue previamente creado. 
// Post: se destruyo correctamente el iterador. 
void lista_iter_destruir(lista_iter_t *iter);

// Recibe un iterador y un dato, y inserta un nodo conteniendo a ese dato entre la posicion anterior y actual del iterador. 
// Devuelve false en caso de error de memoria. Devulve true si salio todo bien.
// Pre: el iterador fue creado previamente. 
// Post: se inserto correctamente un nodo conteniendo el dato dado por parametro.
// Post2: Ahora el nodo anterior esta apuntando al nuevo nodo, y este apunta al actual.
// Post3: la lista manitene su invariante. 
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Recibe un iterador y elimina el nodo actual en el que se encuetra. 
// Devuelve NULL en caso de encontrarse al final de la lista.
// Pre: el iterador fue creado previamente. 
// Post: se elimino correctamente el nodo actual.
// Post2: Ahora el nodo anterior esta apuntando al siguiente del actual.
// Post3: la lista manitene su invariante. 
void *lista_iter_borrar(lista_iter_t *iter);

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
