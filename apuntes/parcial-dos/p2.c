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
