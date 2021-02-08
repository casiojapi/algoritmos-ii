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

void lista_invertir(lista_t* lista) {
    nodo_t* actual = lista->primero;
    nodo_t* ant = NULL;
    nodo_t* sig = actual ? actual->prox : NULL;
    lista->ultimo = lista->primero;
    while (actual) {
        actual->prox = ant;
        ant = actual;
        actual = sig;
        sig = actual ? actual->prox : NULL;

    }
    lista->primero = ant;
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

int buscar_minimo(int arr[], size_t n) {
    if (n == 0) return -1;
    if (n == 1) return arr[0];
    int izq = buscar_minimo(arr, (n+1)/2);
    int der = buscar_minimo(arr + n/2, (n+1)/2);
    return izq < der ? izq : der;
}

int elemento_desordenado(int arr[], size_t n) {
    if (n == 2) return arr[0] > arr[1] ? arr[0]: -1;
    int izq = elemento_desordenado(arr, (n+1)/2);
    int der = elemento_desordenado(arr + (n+1)/2, (n+1)/2);
    if (izq == der)
        return -1;
    return izq == -1 ? der : izq;
}

int primer_cero(int arr[], size_t n) {
    if (arr[0] == 0) return 0;
    if (!n || arr[n-1] == 1) return -1;
    return primer_cero(arr + 1, n -1) + 1;
}



#include "pila.h"

void ordenar_datos(pila_t* pila, void* dato);

void ordenar_pila(pila_t* pila) {
    pila_t* aux = pila_crear(); //O(1)

    while (!pila_esta_vacia(pila)) {
        void* dato = pila_desapilar(pila);  //O(1)
        ordenar_datos(aux, dato);
    }
    while (!pila_esta_vacia(aux)) {
        pila_apilar(pila, pila_desapilar(aux));
    }
}

void ordenar_datos(pila_t* pila, void* dato) {
    if (pila_esta_vacia(pila)) {
        pila_apilar(pila, dato);
        return;
    }

    if (*(int*)pila_ver_tope(pila) >= *(int*)dato) {
        pila_apilar(pila, dato);
        return;
    }
    void* aux = pila_desapilar(pila);
    ordenar_datos(pila, dato);
    pila_apilar(pila, aux);
}