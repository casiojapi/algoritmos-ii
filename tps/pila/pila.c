#include "pila.h"

#include <stdlib.h>
#include <stdio.h>

/* Definición del struct pila proporcionado por la cátedra.
 */

#define TAM_BASE 10
#define CTE_APILAR 2
#define CTE_DESAPILAR 0.5

struct pila
{
    void **datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad; // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

//

static bool _redimension(pila_t *p, float cte)
{
    void *aux = realloc(p->datos, sizeof(void *) * (size_t)((float)p->capacidad * cte));
    if (aux == NULL)
        return false;
    p->datos = aux;
    p->capacidad = (size_t)((float)p->capacidad * cte);
    return true;
}

pila_t *pila_crear(void)
{
    pila_t *p = malloc(sizeof(pila_t));
    if (p == NULL)
        return NULL;
    p->datos = malloc(sizeof(void *) * TAM_BASE);
    if (p->datos == NULL)
    {
        free(p);
        return NULL;
    }
    p->cantidad = 0;
    p->capacidad = TAM_BASE;
    return p;
}

void pila_destruir(pila_t *pila)
{
    free(pila->datos);
    free(pila);
}

bool pila_esta_vacia(const pila_t *pila)
{
    return !pila->cantidad;
}

bool pila_apilar(pila_t *pila, void *valor)
{
    if (pila->cantidad >= pila->capacidad)
    {
        if (!_redimension(pila, CTE_APILAR))
            return NULL;
    }

    pila->datos[pila->cantidad++] = valor;
    return true;
}

void *pila_ver_tope(const pila_t *pila)
{
    if (pila_esta_vacia(pila))
        return NULL;

    return pila->datos[pila->cantidad - 1];
}

void *pila_desapilar(pila_t *pila)
{
    if (pila_esta_vacia(pila))
        return NULL;

    if (pila->cantidad > 10 && pila->cantidad < pila->capacidad / 4)
    {
        if (!_redimension(pila, CTE_DESAPILAR))
            return NULL;
    }
    pila->cantidad--;
    return pila->datos[pila->cantidad];
}
