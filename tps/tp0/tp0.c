#include "tp0.h"
#include <stdio.h>
/* *****************************************************************
 *                     FUNCIONES A COMPLETAR                       *
 *         (ver en tp0.h la documentación de cada función)         *
 * *****************************************************************/

void swap(int *x, int *y) {
    int temp = *y;
    *y = *x;
    *x = temp;
}


int maximo(int vector[], int n) {
    if (n == 0) 
        return -1;
    
    int index = 0;

    for (int i = 1; i < n; i++)
        if (vector[index] < vector[i])
            index = i;

    return index;
}

// Esta implementacion creo que me quedo medio rara.
// Supongo que se podria haber implementado de alguna otra forma un poco mas eficaz.
// Pero realmente, no se me ocurrio.
int comparar(int vector1[], int n1, int vector2[], int n2) {
    int min = n2 > n1 ? n1 : n2;
    size_t i;
    for (i = 0; i < min; i++) {
        if (vector1[i] < vector2[i])
            return -1;
        if (vector1[i] > vector2[i])
            return 1;
    }
    if (n1 == i && n2 == i)
        return 0;
    if (n1 == i)
        return -1;
    if (n2 == i)
        return 1;
    return 0;
}


void seleccion(int vector[], int n) { 
    int i, max;
    for (i = n; i > 0; i--) {             
        max = maximo(vector, i);
        swap(vector + i - 1, vector + max);
    }
} 