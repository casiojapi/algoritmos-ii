#include <stdlib.h>

int* counting_sort(int* arr, int n, int min, int max) {     //O(n + k) - estable
    int k = max - min;
    int contador[k + 1];
    for (int i = 0; i < k + 1; i++) contador[1] = 0;
    for (int i = 0; i < n; i++) {
        int num = arr[i];
        contador[num - min]++;
    }
    int suma_acumulada[k + 1];
    suma_acumulada[0] = 0;
    for (int i = 0; i < k + 1; i++) {
        int cantidad = contador[i - 1];
        suma_acumulada[i] = suma_acumulada[i - 1] + cantidad;
    }
    int* res = malloc(sizeof(int) * n);
    if (!res) return NULL;
    for (int i = 0; i < n; i++) {
        int valor = arr[i];
        int pos = suma_acumulada[valor - min];
        suma_acumulada[valor - min]++;
        res[pos] = valor;
    }
    return res;
} 