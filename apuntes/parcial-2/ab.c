#include <stdio.h>
#include <stdlib.h>
#include <stfbool.h>

// Arbol binario normal. 

// Raiz: el padre del arbol. el hijo izq de la raiz, es la raiz del sub-arbol izquierdo. 
// Hoja: nodo sin hijos
// Nodo interno: nodo con al menos un hijo

// Busqueda -> O(n)
struct ab {
    struct ab* izq;
    struct ab* der;
    void* dato;
};
size_t altura(const ab_t* ab) {
    if (!ab)
        return 0;
    return max(altura(ab->izq), altura(ab->der)) + 1;
}
// O(n)


// Preorder: mi -> izq -> der

// Inorder: izq -> mi -> der
// Postorder: izq -> der -> mi
// Por Niveles (encolando) por niveles de izq a derre

// ABB: es un AB que cumple con que: 
// + el hijo izquierdo, y todos sus hijos, son menores que la raiz.
// + el hijo derecho, y todos sus hijos, son mayores que la raiz. (propiedades que se cumplen recursivamente)

// Cuando se recorre un ABB in-order, queda ORDENADO.

// Por lo que la busqueda en ABBs es como una busqueda binaria, o sea que O(log n)

// y se inserta como en quicksort. O(log n)

// si el arbol esta balanceado, obtener, guardar, pertenece y borrar son O(log n)

// LA VENTAJA QUE TIENE FRENTE AL HASH, ES QUE SI USO UN INORDER, ME QUEDA TODO EN ORDEN... COSA QUE EN HASH NO EXISTE. 

// el caso patologico cuando se va insertando A, B, C, D, E, F, G ... o sea, que degrada en una lista enlazada. 


////////////////////////////////////////

typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
} nodo_abb_t;

struct abb {
    nodo_abb_t* raiz;
    size_t cant;
    abb_destruir_dato_t destruir;
    abb_comparar_clave_t comparar;
};
// Borrado en ABBs.

// si es una hoja, la matas y listo, nodo anterior ahora apunta a NULL y listo.
// si tiene un solo hijo, matas al middleman, y el ese hijo ahora apunta al abuelo. (o al reves)
// si tiene 2 hijos, buscamos un reemplazante.

// ----------------

// Funciones de comparacion.
// devuelve > 0 si el el primero es mator, devuelve < 0 si es menor o == 0 si son iguales.
// podemos comparar lo que se nos cante. 
// o sea, ordenar segun el criterio que se te cante. 

typedef int (*abb_comparar_clave_t)(const char*, const char*);
// y entra en el abb

size_t contador_de_hojas(ab_t* ab) {    // O(n)
    if (!ab) return 0;
    if (!ab->izq && !ab->der) return 1;
    return contador_de_hojas(ab->izq) + contador_de_hojas(ab->der);
}

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
