void lista_eliminar_pares(lista_t* l) { //O(n)
    nodo_t* actual = l->prim;
    nodo_t* anterior = NULL;

    size_t pos = 0;
    while (actual) {
        nodo_t* sig = actual->sig;
        if (pos == 0) {
            l->prim = sig;
            free(actual);
        }

        if (pos % 2) {
            anterior = actual;
        }

        if (!pos % 2 && pos) {
            anterior->sig = sig;
            free(actual);
        }
        actual = sig;
        pos++;
    }
    return;
}