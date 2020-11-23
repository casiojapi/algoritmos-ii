#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hash.h"
#define CAPACIDAD_INICIAL 33

typedef enum estado {
    VACIO,
    OCUPADO,
    BORRADO
} estado_t;


typedef struct hash_elem {
    char* clave;
    void* dato;
    estado_t estado;
} hash_elem_t;


struct hash {
    hash_elem_t* tabla;
    size_t capacidad, cantidad, borrados;
    hash_destruir_dato_t destruir_dato;
};  

size_t hash_proximo(const hash_t* hash, size_t pos_actual);

// En esta funcion se me ocurrieron bastantes cosas, principalmente, crear un nuevo hash. 
// Pero iba a tener que usar hash guardar por lo que terminaria quedando una llamada recursiva a redimensionar, y preferi hacerlo a pedal.
bool hash_redimensionar(hash_t* hash, size_t nuevo_tam) {    
    hash_elem_t* tabla_post = calloc(nuevo_tam, sizeof(hash_elem_t));
    if (!tabla_post) return false;
    hash_elem_t* tabla_pre = hash->tabla;
    size_t capacidad_pre = hash->capacidad;
    hash->tabla = tabla_post;
    hash->capacidad = nuevo_tam;
    hash->cantidad = 0;
    for (size_t i = 0; i < capacidad_pre; i++) {
        if (tabla_pre[i].estado == OCUPADO) {
            if (!hash_guardar(hash, tabla_pre[i].clave, tabla_pre[i].dato))
                return false;
        }
    }
    return true;
}
// Si ya existe una clave en el hash, devuelve su posicion, y un bool "existia" true por la interfaz.
// De no existir previamente, devuelve la primer posicion disponible para agregar el elemento a la tabla, y el bool devuelto por la interfaz como false. 
size_t hash_buscar_clave(const hash_t* hash, const char* clave, size_t pos, bool* existia);
// Voy a usar djb2
// fuente: http://www.cse.yorku.ca/~oz/hash.html#djb2

unsigned long f_hash(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

/* Crea el hash
 */
hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* h = calloc(1, sizeof(hash_t));
    if (!h) return NULL;
    h->tabla = calloc(CAPACIDAD_INICIAL, sizeof(hash_elem_t));
    if (!h->tabla) {
        free(h);
        return NULL;
    }
    h->capacidad = CAPACIDAD_INICIAL;
    h->destruir_dato = destruir_dato;
    return h;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    if ((hash->cantidad / hash->capacidad) >= 0.7)  // cuando el factor de carga es mayor a 0.7, redimensiono.
        if (!hash_redimensionar(hash, hash->capacidad * 2))
            return false;
    bool existia;
    size_t pos = hash_buscar_clave(hash, clave, f_hash(clave) % hash->capacidad, &existia);
    if (existia) {
        if (hash->destruir_dato)
            hash->destruir_dato(hash->tabla[pos].dato);
        hash->tabla[pos].dato = dato;
    } else {
        hash->tabla[pos].dato = dato;
        hash->tabla[pos].clave = strdup(clave);
        hash->tabla[pos].estado = OCUPADO;
        hash->cantidad++;
    }
    return true;
}
/* Borra un elemento del hash y devuelve el dato asociado.  Devuelve

 * Pre: La estructura hash fue inicializada
 * NULL si el dato no estaba.

 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *hash_borrar(hash_t *hash, const char *clave) {
    bool pertenece;
    size_t pos = hash_buscar_clave(hash, clave, f_hash(clave) % hash->capacidad, &pertenece);
    if (!pertenece) return NULL;
    void* dato = hash->tabla[pos].dato;
    free(hash->tabla[pos].clave);
    hash->tabla[pos].estado = BORRADO;
    hash->tabla[pos].dato = NULL;
    hash->cantidad--;
    return dato;
}

/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada
 */
void *hash_obtener(const hash_t *hash, const char *clave) {
    bool pertenece;
    size_t pos = hash_buscar_clave(hash, clave, f_hash(clave) % hash->capacidad, &pertenece);
    if (!pertenece) return NULL;
    return hash->tabla[pos].dato;
}

/* Determina si clave pertenece o no al hash.
 * Pre: La estructura hash fue inicializada
 */
bool hash_pertenece(const hash_t *hash, const char *clave) {
    bool pertenece;
    hash_buscar_clave(hash, clave, f_hash(clave) % hash->capacidad, &pertenece);
    return pertenece;
}

/* Devuelve la cantidad de elementos del hash.
 * Pre: La estructura hash fue inicializada
 */
size_t hash_cantidad(const hash_t *hash) {
    return hash->cantidad;
}

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura hash fue inicializada
 * Post: La estructura hash fue destruida
 */
void hash_destruir(hash_t *hash) {
    for (size_t i = 0; i < hash->capacidad;  i++) {
        if (hash->tabla[i].estado == OCUPADO) {
            free(hash->tabla[i].clave);
            if (hash->destruir_dato)
                hash->destruir_dato(hash->tabla[i].dato);
        }
    }
    free(hash->tabla);
    free(hash);
}

size_t hash_buscar_clave(const hash_t* hash, const char* clave, size_t pos, bool* existia) {
    size_t i = 0, espacio_libre = 0;
    *existia = false;
    while (i < hash->capacidad) {
        if (!espacio_libre && (hash->tabla[pos].estado == VACIO || hash->tabla[pos].estado == BORRADO))
            espacio_libre = pos;
        if (hash->tabla[pos].estado == OCUPADO && !strcmp(clave, hash->tabla[pos].clave)) {
            *existia = true;
            return pos;
        }
        i++;
        pos++;
        if (pos == hash->capacidad)
            pos = 0;
    }
    return espacio_libre;
}

// iterador
typedef struct hash_iter {
    hash_t* hash;
    size_t actual, recorridos;
} hash_iter_t;

// Crea iterador
hash_iter_t *hash_iter_crear(const hash_t *hash) {
    hash_iter_t* iter = malloc(sizeof(hash_iter_t));
    if (!iter) return NULL;
    iter->hash = (hash_t*)hash;
    iter->actual = 0;
    iter->recorridos = 0;
    return iter;
}

// Avanza iterador
bool hash_iter_avanzar(hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return false;
    size_t prox = hash_proximo(iter->hash, iter->actual);
    if (iter->actual == prox) 
        return false;
    iter->actual = prox;
    iter->recorridos++;
    return true;
}

// Devuelve clave actual, esa clave no se puede modificar ni liberar.
const char *hash_iter_ver_actual(const hash_iter_t *iter) {
    if (hash_iter_al_final(iter)) return NULL;
    char* s = malloc(sizeof(char) * strlen(iter->hash->tabla[iter->actual].clave) + 1) ;
    strcpy(s, iter->hash->tabla[iter->actual].clave);
    return s;
}

// Comprueba si terminó la iteración
bool hash_iter_al_final(const hash_iter_t *iter) {
    return iter->recorridos == iter->hash->cantidad;
}

// Destruye iterador
void hash_iter_destruir(hash_iter_t *iter) {
    free(iter);
}

size_t hash_proximo(const hash_t* hash, size_t pos_actual) {
    size_t i;
    for (i = pos_actual + 1; i < hash->capacidad; i++) {
        if (hash->tabla[i].estado == OCUPADO)
            return i;
    }
    return pos_actual;
}