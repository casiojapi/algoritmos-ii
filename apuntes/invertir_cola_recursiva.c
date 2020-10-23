void invertir_cola(cola_t *cola)
{
    if (cola_esta_vacia(cola))
        return;

    void *dato = cola_desencolar(cola);
    invertir_cola(cola);
    cola_encolar(cola, dato);
}