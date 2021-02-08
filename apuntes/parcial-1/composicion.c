struct composicion {
    pila_t* funciones;
    size_t n;
};

composicion_t* composicion_crear() {
    composicion_t* comp = malloc(sizeof(composicion_t));
    if (comp == NULL) return NULL;
    comp->funciones = pila_crear();
    if (comp->funciones == NULL){
        free(comp);
        return NULL;
    }
    comp->n = 0;
    return comp;

}

void composicion_destruir(composicion_t* composicion) {
    pila_destruir(composicion->funciones);
    free(composicion);
}

bool composicion_agregar_funcion(composicion_t* composicion, funcion_t f) {
    if (!pila_apilar(composicion->funciones, f))
        return false;
    composicion->n++;
    return true;
}

double composicion_aplicar(composicion_t* composicion, double x) {
    double res = x;
    for (size_t i = 0; i < composicion->n; i++) {
        funcion_t func = pila_desapilar(composicion->funciones);
        res = func(res);
    }
    return res;
}