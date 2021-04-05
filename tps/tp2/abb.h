#ifndef ABB_H
#define ABB_H

#include <stdbool.h>
#include <stddef.h>

typedef struct abb abb_t;

typedef int (*abb_comparar_clave_t) (const char *, const char *);
typedef void (*abb_destruir_dato_t) (void *);

// Primitivas del ABB.


// Crea un árbol, y tambien asocia al árbol una funcion de comparacion y destruccion.
// Post: devuelve un árbol con sus respectivas funciones de comparacion y destruiccion si es que fueron dadas.
//Devuelve NULL en el caso de que falle la creación.
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

// Recibe un árbol, una clave y un dato, e inserta un elemento en el árbol con esos atributos daddos.
// Pre: recibe una clave, un árbol y un dato valido.
// Post: devuelve verdadero si todo salio como esperado.
// Post: devuelve falso si hubo algun error al guardarlo.
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

// Recibe un árbol y la clave de un elemento que se desea borrar.
// Si no se encuentra la clave del elemento, devuelve NULL.
// De encontrarse, se elimina el elemento, y se devuelve su respectivo dato.
// Pre: recibe un árbol y clave validos.
// Post: borra efectivamente el elemento, y devuelve el dato asociado al elemento,
// o NULL si no encuentra la clave.
void *abb_borrar(abb_t *arbol, const char *clave);


// Recibe un árbol y la clave del elemento que se desea obtener el dato asociado.
// De no encontrarse la clave, devuelve NULL.
// Si se encuentra, se devuelve el dato.
// Pre: recibe un árbol y clave validos.
// Post: devuelve el dato asociado al elemento, o NULL si no esta la clave.
void *abb_obtener(const abb_t *arbol, const char *clave);

// Devuelve true o false, dependediendo de si la clave pasada por parametro se encuentra o no (respectivamente) en el árbol.
// Pre: el árbol fue creado correctamente.
// Post: si se encontraba, efectivamente devuelve true. Caso contrario, devuelve false.
bool abb_pertenece(const abb_t *arbol, const char *clave);


// Devuelve la cantidad de elementos en el árbol.
// Pre: el árbol fue creado correctamente.
// Post: devolvio la cantidad exacta de elementos en el árbol.
size_t abb_cantidad(abb_t *arbol);

// Recibe un árbol, se recorren todos sus elementos y se aplica la función de destruir dato (en el caso de que exista) a cada uno de ellos  y se libera toda la memoria asociada a él.
// Pre: recibe un árbol válido
// Post: se aplicó la funcion destruir dato a sus elementos y toda la memoria asociada al árbol quedó liberada.
void abb_destruir(abb_t *arbol);


// Iterador interno
//Pre: recibe un árbol válido
//Post: Se recorrió el abb in order hasta el final o hasta que la función visitar haya devuelto false.
//En cada iteración se aplicó la función visitar a los elementos visitados.
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);


// Iterador externo
typedef struct abb_iter abb_iter_t;

//Crea un iterador externo del abb que lo recorre in order.
//Pre: recibe un árbol válido.
//Post: Se creó el iterador interno, en el caso de fallar devuelve NULL. El iterador se posiciona en la raíz (de ser existente)
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//Avanza el iterador interno.
//Post: en el caso de que era posible avanzar, se devolvió true y se avanzó el iterador. De lo contrario, devolvió false.
bool abb_iter_in_avanzar(abb_iter_t *iter);

//Devuelve el dato actualmente visitado por el iterador.
void *abb_iter_in_ver_actual(const abb_iter_t *iter);

//Devuelve false si el iterador no está al final o true si el iterador está al final (es decir, no puede avanzar)
bool abb_iter_in_al_final(const abb_iter_t *iter);

//Se destruye el iterador y se libera toda la memoria asociada a él.
void abb_iter_in_destruir(abb_iter_t* iter);

#endif //ABB_H
