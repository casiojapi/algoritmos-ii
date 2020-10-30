#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//div y conquer que de O(n log n)
//ej 3
int _mdm(int *arr, size_t inicio, size_t fin) {
    if (inicio > fin) return NULL;
    if (inicio == fin) return arr[inicio];

    size_t medio = (inicio + fin) / 2;

    int cand1 = _mdm(arr, inicio, medio);
    int cand2 = _mdm(arr, medio+1, fin);

    size_t cont1 = 0, cont2 = 0;
    for (size_t i = inicio; i < fin; i++) {
        if (arr[i] == cand1) cont1++;
        else if (arr[i] == cand2) cont2++;
    }

    return cont1 > cont2 ? cand1 : cand2;
}

bool mas_de_mitad(int *arr, size_t n) {
    int cand = _mdm(arr, 0, n-1);
    int cont = 0;
    for (size_t i = 0; i < n; i++) {
        if (arr[i] == cand) cont++;
    }
    return cont > n/2;
}

//ej 5 - devolver primeros k elementos de una cola - COMO PRIMITIVA
void **multiprimeros(const cola_t *cola, const size_t k) {  //O(k)
    void **primeros = calloc(k, sizeof(void *));   //O(k)
    if (primeros == NULL) return NULL;
    nodo_t *actual = cola->prim;
    for (int i = 0, i < k && actual != NULL) {  //O(min(n, k))
        primeros[i] = actual->dato;
        actual = actual->sig;
    }
    return primeros;
}
//ej 5 - como FUNCION
void **multiprimeros_pub(const cola_t *cola, const size_t k) {  //O(K + N)
    void **primeros = calloc(k, sizeof(void *));    //O(K)
    if (primeros == NULL) return NULL;
    cola_t *copia = cola_crear();
    if (copia == NULL) {
        free(primeros);
        return NULL;
    }
    for (int i = 0; !cola_esta_vacia(cola); i++) {  //O(n)
        void *dato = cola_desencolar(cola);
        if (i < k) 
            primeros[i] = dato;
        if (!cola_encolar(copia, dato)) {
            cola_destruir(copia);
            free(primeros);
            return NULL;
        }
    }

    while (!cola_esta_vacia(copia)) {   //O(n)
        if (!cola_encolar(cola, cola_desencolar(copia))){
            cola_destruir(copia);
            free(primeros);
            return NULL;
        }
    }

    cola_destruir(copia);
    return primeros;
}

//PILA ES PIRAMIDAL?
//usamos pila auxiliar
bool pila_es_piramidal(pila_t* pila) {      //O(n) n siendo n elementos en la pila.  
    pila_t* aux = pila_crear();
    if (aux == NULL) return NULL;
    bool es_piramidal = true;
    while (!pila_esta_vacia(pila) && es_piramidal) {        //O(n)
        int* tope = (int*) pila_desapilar(pila);
        int* inferior = (int*) pila_ver_tope(pila);
        es_piramidal = inferior ? *tope < *inferior : true;
        pila_apilar(aux, (void*) tope);
    }
    while (!pila_esta_vacia(aux)) {     // O(n)
        pila_apilar(pila, pila_desapilar(aux));
    }
    pila_destruir(aux);
    return es_piramidal;
}

bool pila_es_piramidal_recur(pila_t* pila) {
    if (pila_esta_vacia(pila)){
        return true;
    }

    int* tope = pila_desapilar(pila);
    int* inferior = pila_ver_top(pila);

    bool es_piramidal = inferior ? *tope < *inferior && pila_es_piramidal(pila) : true;

    pila_apilar(pila, (void*) tope);
    return es_piramidal;
}

//div y conquer parte entera de raiz de n, en O(log n)
size_t _raiz_entera(size_t n, size_t inicio, size_t fin) {  //T(n) = T(n/2) + O(1)
    size_t medio = (inicio + fin) / 2;
    size_t cuadrado = medio * medio;
    if (cuadrado <= n && (medio + 1) * (medio + 1) > n)     //O(1)
        return medio;
    if (cuadrado > n)  
        return _raiz_entera(n, inicio, medio);  //O(n/2)
    if (cuadrado < n)
        return _raiz_entera(n, medio, fin);     //O(n/2)
}

