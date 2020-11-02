// Autor: Maximo Santoro
// Padron: 105572
// Ejercicios a hacer: 2, 4 y 9.
//ej2

#include <stdio.h>
#include <stdlib.h>

float suma_total(float arr[], size_t n) {
    if (n < 1) return 0;    // O(1) -> es una operacion constante, independiente de la N cantidad de elementos. 
    if (n == 1) return arr[0];  // O(1) -> tambien es otra operacion constante. 
    return suma_total(arr, (n+1)/2) + suma_total(arr + n/2, n/2);   // aqui los dos llamados recursivos, A = 2. y O(1) la suma y el return.
}

/*
Para justificar la complejidad del algoritmo voy a usar el Teorema del Maestro, ya que nos encontramos en un caso de Division y Conquista. 

T(N) = A * T(N/B) + O(N^C)

T(n) = 2 * T(n/2) + O(1)

A -> cantidad de llamados recursivos. En este caso, tenemos 2, en el return. A = 2
B -> Proporcion de tamagno original con el que llamamos recursivamente, es 2, ya que estamos dividiendo por la mitad en cada llamada. B = 2
n^C -> costo de las demas operaciones, (partir, juntar, returnear el resultado) me da todo O(1). Por lo tanto, n^C = 1, C = 0.

Ahora uso el teoroma: log_B(A) == C ?
Y con estos valores me queda: log_2(2) == 0 ? Y me queda, 1 > 0, por lo que T(N) = O(n^log_B(A)) = O(n^1) = O(n)

Por lo que la complejidad de la funcion implementada "suma_total" es igual a O(n)

*/

//PRUEBA EJ 2
int main(void) {
    float test[17] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    printf("%f\n", suma_total(test, 17));
    return 0;
}

//ej 4
#include <stdbool.h>
#include "pila.h"

bool pila_magica(pila_t* pila) {
    pila_t* aux = pila_crear(); // O(1) -> operacion constante
    if (aux == NULL) return false;     // O(1)
    bool es_magica = false;     // O(1)
    int i = 0;      // O(1)
    while (!pila_esta_vacia(pila)){     // el while es O(n), siendo n los n elementos que hay en un principio apilados en la pila. 
        if (!pila_apilar(aux, pila_desapilar(pila))) {  // dentro del while, O(1) + O(1)
            pila_destruir(aux);     // (dentro del while), O(1)
            //aca deverdad deberia arreglar la pila original, pero evito hacer esa parte ya que no creo que sea parte del problema original.
            return false;      // (dentro del while), O(1) 
        }
    }

    while (!pila_esta_vacia(aux)) {     // el while es O(n), siendo n los n elementos apilados en aux (los cuales deberian ser la misma cantidad que el while anterior)
        int* tope = (int*)pila_ver_tope(aux);   // (dentro del while), O(1)
        if (++i == *tope)       // (dentro del while), O(1)
            es_magica = true;       // (dentro del while), O(1)
        if (!pila_apilar(pila, pila_desapilar(aux))) {      // (dentro del while), O(1) + O(1)
            pila_destruir(aux);     // (dentro del while), O(1)
            //digo lo mismo que en el chequeo pasado.
            return false;       // (dentro del while), O(1)
        }
    }
    pila_destruir(aux);     // O(1)
    return es_magica;       // O(1)
}

/*
Entonces, analizando la complejidad de la funcion "pila_es_magica", tengo un par de asignaciones y chequeos, un pila_crear, lo cual es todo O(1),
Y luego tengo un while, el cual es O(n), siendo n la cantidad de elementos que tiene la pila original. 
y luego otro while, el cual tambien es O(n), tambien con el mismo n si no falla nada. 
Y por ultimo el return del bool "es_magico", el cual es O(1).

Por lo que me terminaria quedando algo asi: T(n) = O(1) + O(1) + .... + O(1) + O(n) + O(n) = O(2n) = O(n)

Por lo que podemos acotar esto a O(n), ya que la constante que lo multiplica es "despreciable".
*/


//ej 9
typedef struct nodo_lista {
    struct nodo_lista* prox; 
    void* dato; 
} nodo_lista_t;

typedef struct lista {
    nodo_lista_t* prim;
} lista_t;

bool lista_any(const lista_t* lista, bool (*f)(void*)) {
    nodo_lista_t* actual = lista->prim;     // O(1)
    while (actual) {    // seria O(n), siendo n la cantidad de elementos en la lista. (justifico abajo.) **
        if (f(actual->dato))    // O(1) -> aca puede depender de lo que haya adentro de "f", pero asumo O(1)
            return true;        // O(1)
        actual = actual->prox;      // O(1)
    }
    return false;       // O(1)
}
/* ** el while, si bien podria cortar antes que n, en el peor de los casos tendria que 
recorrer todos los elementos hasta comprobar el ultimo. Por ende es O(n). 
luego dentro del while, solo hay operaciones constantes, asi que el while queda en O(n).
y fuera del while, solo hay operaciones constantes, O(1).
Por lo que me termina quedando: T(n) = O(1) + O(n) + O(1) = O(n)

La complejidad de la funcion "lista_any" queda acotada a O(n).
*/