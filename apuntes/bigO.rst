Notacion big O - Teoria de complejidad

En orden creciente (complejidad)

O(cte)
O(log(n)) + logaritmico
O(n) + lineal
O(n log(n)) + lineal-logaritmico
O(n^2) + cuadratico
O(n^3) + cubico
O(2^n) + exponencial

+ operaciones ctes (tipo -> condiciones)
O(1)    - o sea, no importante... Despreciable.

Al sumar dos Os gana la mas grande. (Hace tender n a INF)

//ej 1

def sumar(arreglo, n)
    suma = 0    // O(1)
    for i in range(1, n):   
        suma += arreglo[i];     // O(n)
    return suma     // O(1)

complejidad = O(1) + O(n) + O(1) = O(n) // el mas grande se come a todos. 

//ej 2

def restar(arreglo, n):
    for i in range:
        arreglo[i] += 3     // O(n)
    for i in range: 
        arreglo[i] += .14   // O(n)
    return void

complejidad = O(n) + O(n) = 2O(n) = O(n)

//ej 3

def multar(arreglo, n):
    for i in range:     // O(n)
        suma    
        for j in range:     // O(n)
            suma + 2;
    return void

T(n) = complejidad = O(n) * O(n) = O(n^2)

//ej 3 - Ecuaciones de recurrencia
def maximo_recursivo(arreglo, n)
    if (n == 1) return arreglo[o];
    return max(maximo_recursivo(arreglo+1, n-1), arreglo)
T(n)

