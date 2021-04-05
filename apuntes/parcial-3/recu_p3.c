// Maximo Santoro, Padron: 105572. Recuperatorio del parcialito 3.

// EJ 3 - Verdadero y Falso. 

// a. En un grafo bipartito no pueden haber ciclos con cantidad impar de vértices que lo compongan.

// a) Verdadero, seria imposible que en un grafo bipartito exista un ciclo impar de vertices. Ya que de esa forma siempre va a haber un caso en el que un vertice adyancente a otro va a ser del mismo "color". Ya que un grafo es bipartito si se pueden separar todos los nodos de un grafo en 2 subconjuntos, y no existen aristas que conecten 2 mismos vertices del mismo subconjunto.

// b. En un árbol (grafo no dirigido, conexo y sin ciclos) todos los vértices con al menos dos adyacentes son puntos de
// articulación.

// b) Verdadero. Lo que pienso es que si estamos teniendo en cuenta solo vertices con al menos 2 adyacentes, en un arbol cada nodo tiene solo 1 padre, por ende, si o si va a tener que contar con por lo menos un hijo. Entonces, si fuesemos a eliminar un nodo con un padre y por lo menos un hijo, siempre estariamos separando al grafo en 2 componentes conexas distintas. Y la definicion de un punto de articulacion es un vertice dentro de un grafo no dirigido, que al eliminarlo, implica una desconexion es el mismo (grafo)

// c. En un grafo dirigido, no existe camino de un vértice v de una componente fuertemente conexa hacia un vértice w de
// otra componente fuertemente conexa.

// C) Falso, si puede existir un camino de un vertice "V" de una componente fuertemente conexa (A), hacia un vertice "W" de otra componente fuertemente conexa (B). Y justifico con un contraejemplo en un grafico que adjunto en el zip. "justificacion_3_c.png"



// 2 - ¡Se acaba la vida en la Tierra! La NASA construyó una nave espacial para continuar viviendo en Marte, el problema es que
// la capacidad de la misma (M) es reducida. El presidente de la NASA, “Ja Mao”, decidió que solo entrarán en la nave las
// M personas con el nombre más corto. Implementar en C una función que reciba un arreglo con el nombre de todas las
// personas del Planeta Tierra, y su largo, N; y que devuelva una lista con los pasajeros habilitados, en O(N + M log N).
// Justificar el orden del algoritmo.

#include "lista.h"
#include "heap.h"
#include "hash.h"
#include <stdlib.h>
#include <string.h>

int cmp_largo(const void *a, const void *b) {
    size_t a_n = strlen((char*)a);
    size_t b_n = strlen((char*)b);
    if (a_n == b_n)
        return 0;
    return a_n < b_n ? 1 : -1;
}

lista_t* pasajeros_habilitados(char** total_personas, size_t n_total, size_t m_reduc) {
    lista_t* lista = lista_crear();
    if (lista == NULL) return NULL;

    heap_t* heap = heap_crear_arr(total_personas, n_total, cmp_largo);
    for (size_t i = 0; i < m_reduc; i++) {
        char* nombre = heap_desencolar(heap);
        lista_insertar_primero(lista, nombre);
    }
    heap_destruir(heap, NULL);
    return lista;
}

// la idea de mi implementacion es la siguiente. Primero se recibe la totalidad de nombres a procesar, en este caso el de todos los humanos, y llamo a "heap_crear_arr()" con este arreglo de datos genericos, a ordenarse con mi nueva funcion de comparacion "cmp_largo", la cual compara cual de los dos nombres dados es el mas corto. Entonces, una vez llamado a heap_crear_arr que dentro llama a heapify (que es O(n), n siendo la cantidad de nombres a procesar y meter en el nuevo arreglo), recibo un heap con todos los nombres (N), y ya estoy listo para desencolar y armar la lista con los nuevos pasajeros seleccionados. 

// Una vez creado el heap, hago un for (que iterara M veces, siendo M el numero reducido de humanos a entrar a la nave), y voy desencolando (O(log N) N siendo la cantidad de nombres en el heap) uno a uno e insertando cada uno en la lista (O(1)). 

// por lo que la complejidad del for me quedaria: O(M * log N * 1), o sea O(M log N).
// Por ende la primer parte es todo O(1), despues heap_crear_arr() -> O(N), y luego el for que seria O(M log N). Por lo que la complejidad de la funcion entera me quedaria O(N + (M log N)) como fue pedido en el enunciado.




