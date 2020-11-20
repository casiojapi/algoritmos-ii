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
    return h;
}

/* Guarda un elemento en el hash, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura hash fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool hash_guardar(hash_t *hash, const char *clave, void *dato) {
    
}