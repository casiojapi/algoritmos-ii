#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hash.h"
#define CAP_INIC 33

typedef enum estado {
    VACIO,
    OCUPADO,
    BORRADO
} estado_t;


typedef struct hash_memb {
    char* clave;
    void* dato;
    estado_t estado;
} hash_memb_t;


struct hash {
    hash_memb_t* tabla;
    size_t capacidad, cantidad, borrados;
    hash_destruir_dato_t destruir_dato;
};  


// Voy a usar djb2
// fuente: http://www.cse.yorku.ca/~oz/hash.html#djb2

unsigned long f_hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}

/* Crea el hash
 */
hash_t *hash_crear(hash_destruir_dato_t destruir_dato) {
    hash_t* h = calloc(1, sizeof(hash_t));
    if (!h) return NULL;
    h->tabla = calloc(CAP_INIC, sizeof(hash_memb_t));
    if (!h->tabla) {
        free(h);
        return NULL;
    }
    h->capacidad = CAP_INIC;
    h->destruir_dato = destruir_dato;
    return h;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    // if cant / cap >= 0.7 redimensiona * 2
    size_t pos = f_hash(clave) % hash->capacidad;
    while (hash->tabla[pos].estado == OCUPADO) {
        pos *= pos;
        if (pos > hash->capacidad)
            pos %= hash->capacidad;
    }
    
}


/* Borra un elemento del hash y devuelve el dato asociado.  Devuelve
 * NULL si el dato no estaba.
 * Pre: La estructura hash fue inicializada
 * Post: El elemento fue borrado de la estructura y se lo devolvió,
 * en el caso de que estuviera guardado.
 */
void *hash_borrar(hash_t *hash, const char *clave);

/* Obtiene el valor de un elemento del hash, si la clave no se encuentra
 * devuelve NULL.
 * Pre: La estructura hash fue inicializada
 */
void *hash_obtener(const hash_t *hash, const char *clave);

/* Determina si clave pertenece o no al hash.
 * Pre: La estructura hash fue inicializada
 */
bool hash_pertenece(const hash_t *hash, const char *clave);

/* Devuelve la cantidad de elementos del hash.
 * Pre: La estructura hash fue inicializada
 */
size_t hash_cantidad(const hash_t *hash);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura hash fue inicializada
 * Post: La estructura hash fue destruida
 */
void hash_destruir(hash_t *hash) {
    for (size_t i = 0; i < hash->capacidad;  i++) {
        if (hash->tabla[i].estado == OCUPADO && hash->destruir_dato) {
            hash->destruir_dato(hash->tabla[i].dato);
        }
    }
    free(hash->tabla);
    free(hash);
}
