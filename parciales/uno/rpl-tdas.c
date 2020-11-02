void invertir_arreglo(void** arreglo, size_t n) {
    pila_t* p = pila_crear();
    if (p == NULL) return;
    for (size_t i = 0; i < n; i++) {
        if(!pila_apilar(p, arreglo[i]))
            return;
    }
    for (size_t i = 0; i < n; i++) {
        arreglo[i] = pila_desapilar(p);
    }
    pila_destruir(p);
}

void* lista_ante_k_ultimo(lista_t* lista, size_t k) {
    nodo_t* actual = lista->primero;
    nodo_t* forw = lista->primero;

    for (size_t i = 0; i < k; i++) {
        forw = forw->prox;
    }
    while (forw) {
        forw = forw->prox;
        actual = actual->prox;
    }
    return actual->dato;
}

bool pila_es_piramidal(pila_t* pila) {
    bool es = true;
    pila_t* aux = pila_crear();
    int *up = malloc(sizeof(int));
    int *down = malloc(sizeof(int));
    while (!pila_esta_vacia(pila)) {
        pila_apilar(aux, pila_desapilar(pila));
    }
    down = pila_ver_tope(aux);
    pila_apilar(pila, pila_desapilar(aux));

    while (!pila_esta_vacia(aux)) {
        up = pila_ver_tope(aux);
        pila_apilar(pila, pila_desapilar(aux));
        if (*down <= *up)
            es = false;
        down = up;
    }

    return es;
}