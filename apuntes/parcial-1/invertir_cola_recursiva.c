void invertir_cola(cola_t *cola)
{
    if (cola_esta_vacia(cola))
        return;

    void *dato = cola_desencolar(cola);
    invertir_cola(cola);
    cola_encolar(cola, dato);
}

void cola_invertir(cola_t *cola)
{
    nodo_t *actual = cola->prim;
    nodo_t *anterior = NULL;
    nodo_t *siguiente = actual ? actual->sig : NULL;
    cola->ult = cola->prim;
    while (actual)
    {
        actual->sig = anterior;
        anterior = actual;
        actual = siguiente;
        siguiente = actual ? actual->sig : NULL;
    }
    cola->prim = anterior;
}