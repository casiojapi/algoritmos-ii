#include <stdio.h>
#include <stdbool.h>

// arbol recursivo (sin nodos especeficamente nodos)
typedef struct ab {
    struct ab* izq;
    struct ab* der;
    char* clave;
    void* dato;
} ab_t;

// arbol con raiz 
struct ab {
    nodo_t* raiz;
} ab_t;

typedef struct nodo {
    struct nodo* izq;
    struct nodo* der;
    char* clave;
    void* dato;
} nodo_t;

size_t altura(nodo_t* nodo) {
    if (!nodo) return 0;
    return max(altura(nodo->der), altura(nodo->izq)) + 1;
}





size_t contador_de_hojas(ab_t* ab) {    // O(n)
    if (!ab) return 0;
    if (!ab->izq && !ab->der) return 1;
    return contador_de_hojas(ab->izq) + contador_de_hojas(ab->der);
}

size_t altura(const ab_t* ab) {
    if (!ab)
        return 0;
    return max(altura(ab->izq), altura(ab->der)) + 1;
}
// O(n)

bool arboles_iguales(ab_t* ab_1, ab_t* ab_2) {
    if (!ab_1 || !ab_2)
        return !ab_1 && !ab_2;
    return arboles_iguales(ab_1->izq, ab_2->izq) && arboles_iguales(ab_1->der, ab_2->der);
}

// implementar una primitiava para el ABB, que devuelva una lista con las claves del mismo, ordenadas tal que si insertaramos las claves en un ABB
// vacio, dicho ABB tendira la misma estructura que el arbol original.

void _abb_obtener_claves(abb_nodo_t* actual, lista_t* lista) {   // implemento la agregacion a la lista en "in-order" para que despues cuando 
    if (actual == NULL) return;
    lista_insertar_ultimo(lista, (void*)actual->clave);
    _abb_obtener_claves(actual->izq, lista);
    _abb_obtener_claves(actual->der, lista);
    return;
}

// y el wrapper

lista_t* lista_ordenada(abb_t* abb) {
    lista_t* l = lista_crear();
    _abb_obtener_claves(abb->raiz, l);  // O(n)
    return l;
}



// Ejercicio 2: Funcion de O(n) que recibe un arreglo y su largo, y que devuelve true o false si hay un elemento que aparece mas de una vez. Justificar el orden
// resolucion con HASH

bool repetidos(void* arreglo[], size_t n) {
    hash_t* hash = hash_crear(NULL);
    size_t veces = 0;
    for (size_t i = 0; i < n; i++) {
        if (hash_pertenece(hash, arreglo[i]))
            veces = hash_obtener(hash, arreglo[i])
        veces++;
        hash_guardar(hash, arreglo[i], veces);
        if (veces > n / 2)
            return true;
    }
    hash_destruir(hash);
    return false;
}


// Obtener claves de un hash cerrado

lista_t* hash_claves(const hash_t* hash) {
    lista_t* claves = lista_crear();
    if (!claves)
        return NULL;
    for (size_t i = 0; i < hash->tam; i++) {
        if (hash->tabla[i] == OCUPADO)
            lista_insertar_ultimo(claves, hash->tabla[i].clave);
    }
    return claves;
}

// Obtener claves de un hash ABIERTO

lsita_t* hash_aberto_claves(const hash_t* hash) {
    lista_t* claves = lista_crear();
    if (!claves) return NULL;

    for (size_t i = 0; i < hash->tam; i++) {
        lista_iter_t* iter = lista_iter_crear(hash->tabla[i]);
        while (lista_iter_al_final(iter)) {
            campo_hash_t* campo = lista_iter_ver_actual(iter);
            lista_insertar_ultimo(claves, campo->clave);
            lista_iter_avanzar(iter);
        }
        lista_iter_destruir(iter);
    }
    return claves;
}


// invertir arbol - invierte el arbol, hijos izq de cada nodo pasa a ser derecho. 

typedef struct arbol_inv {
    struct arbol_inv* izq;
    struct arbol_inv* der;
} arbol_t;

void arbol_invertir(arbol_t* ab) {
    if (!ab) return;
    arbol_t* der_antes = ab->der;
    ab->der = ab->izq;
    ab->izq = der_antes;
    arbol_invertir(ab->der);
    arbol_invertir(ab->izq);
    return;
}

// Nodos mayores a una clave

lista_t* abb_mayores(const abb_t* abb, const char* clave) {
    lista_t* mayores = lista_crear();
    if (!mayores) {
        return NULL;
    }
    _abb_mayores(abb, clave, mayores);
    return mayores;
}

void _abb_mayores(const abb_t* abb, const char* clave, lista_t* claves) {
    // caso base SIEMPRE
    if (abb == NULL) {
        return;
    }
    // si la actual es mayor, llamamos a la izquierda y guardamos la actual
    if (strcmp(abb->clave, clave) > 0) {
        _abb_mayores(abb->izq, clave, claves);
        lista_insertar_primero(claves, abb->clave);
    }
    _abb_mayores(abb->der, clave, claves);
}
