#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

// Primitivas del ABB.


// Crea un arbol, y tambien asocia al arbol una funcion de comparacion y destruccion. 
// Post: devuelve un arbol con sus respectivas funciones de comparacion y destruiccion si es que fueron dadas. 
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Recibe un arbol, una clave y un dato, e inserta un nodo en el arbol con esos atributos daddos. 
// Pre: recibe una clave, un arbol y un dato valido. 
// Post: devuelve verdadero si todo salio como esperado.
// Post: devuelve falso si hubo algun error al guardarlo. 
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Recibe un arbol y la clave de un nodo que se desea borrar. 
// Si no se encuentra la clave del nodo, devuelve NULL.
// De encontrarse, se elimina el nodo, y se devuelve su respectivo dato. 
// Pre: recibe un arbol y clave validos. 
// Post: borra efectivamente el nodo, y devuelve el dato asociado al nodo,
// o NULL si no encuentra la clave. 
void *abb_borrar(abb_t *arbol, const char *clave);


// Recibe un arbol y la clave del nodo que se desea obtener el dato asociado. 
// De no encontrarse la clave, devuelve NULL.
// Si se encuentra, se devuelve el dato.
// Pre: recibe un arbol y clave validos. 
// Post: devuelve el dato asociado al nodo, o NULL si no esta la clave. 
void *abb_obtener(const abb_t *arbol, const char *clave);

// Devuelve true o false, dependediendo de si la clave pasada por parametro se encuentra o no (respectivamente) en el arbol.
// Pre: el arbol fue creado correctamente.
// Post: si se encontraba, efectivamente devuelve true. Caso contrario, devuelve false.
bool abb_pertenece(const abb_t *arbol, const char *clave);


// Devuelve la cantidad de nodos en el Arbol.
// Pre: el arbol fue creado correctamente. 
// Post: devolvio la cantidad exacta de nodos en el arbol. 
size_t abb_cantidad(abb_t *arbol);

// Recibe un arbol y libera toda la memoria asociada a el.
// Pre: recibe un arbol valido
// Post: toda la memoria asociada al arbol queda liberada. 
void abb_destruir(abb_t *arbol);


// Iterador interno

void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

// Iterador externo

typedef struct abb_iter abb_iter_t;

abb_iter_t *abb_iter_in_crear(const abb_t *arbol);
bool abb_iter_in_avanzar(abb_iter_t *iter);
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);
bool abb_iter_in_al_final(const abb_iter_t *iter);
void abb_iter_in_destruir(abb_iter_t* iter);

#endif //ABB_H
