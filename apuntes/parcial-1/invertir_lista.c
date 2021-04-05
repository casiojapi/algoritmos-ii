void lista_invertir(lista_t *lista)
{
    nodo_t *actual = lista->prim;
    nodo_t *anterior = NULL;
    nodo_t *siguiente = actual ? actual->sig : NULL;
    lista->ult = lista->prim;
    while (actual)
    {
        actual->sig = anterior;
        anterior = actual;
        actual = siguiente;
        siguiente = actual ? actual->sig : NULL;
    }
    lista->prim = anterior;
}

#include <stdlib.h>


void* lista_ante_k_ultimo(lista_t* lista, size_t k) {
    nodo_t* n1 = lista->prim;
    nodo_t* n2 = lista->prim;
    for (size_t i = 0; i < k; i++)
        n1 = n1->sig;
    while (n1) {
        n1 = n1->sig;
        n2 = n2->sig;
    }
    return n2->dato;
}