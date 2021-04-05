#include <stdlib.h>
#include "heap.h"

#define CAPACIDAD_INICIAL 47
#define FACTOR_REDIMENSION 2
#define ACHICAR_ARREGLO 4

struct heap {
    void **arreglo;
    size_t cantidad, capacidad;
    cmp_func_t cmp;
};

// Primmitivas auxiliares

bool heap_redimensionar(heap_t* heap, size_t nuevo_tam);
void swap_elem(void* arreglo[], size_t pos1, size_t pos2);
void downheap(void* arreglo[], size_t tam, size_t pos_padre, cmp_func_t cmp);
void upheap(void* arreglo[], size_t tam, size_t pos_hijo, cmp_func_t cmp);
size_t pos_max(void *arreglo[], size_t tam, size_t pos_padre, size_t pos_h_izq, size_t pos_h_der, cmp_func_t cmp);
void heapify(void *arreglo[], size_t tam, cmp_func_t cmp);

// Primitivas Heap

heap_t *heap_crear(cmp_func_t cmp) {
    heap_t* h = malloc(sizeof(heap_t));
    if (!h) return NULL;
    h->arreglo = malloc(sizeof(void*) * CAPACIDAD_INICIAL);
    if (!h->arreglo) {
        free(h);
        return NULL;
    }
    h->cantidad = 0;
    h->capacidad = CAPACIDAD_INICIAL;
    h->cmp = cmp;
    return h;
}

/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
    heap_t* h = heap_crear(cmp);
    if (!h) return NULL;
    if (n >= CAPACIDAD_INICIAL && !heap_redimensionar(h, n)) { //Cambie h->capacidad * FACTOR_REDIMENSION por n, por si n es mas grande que ese producto. BORRAR
        heap_destruir(h, NULL);
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        h->arreglo[i] = arreglo[i];
    }

    h->cantidad = n;

    if(n) heapify(h->arreglo, n, cmp);

    return h;
}

void heap_destruir(heap_t *heap, void (*destruir_elemento)(void *e)) {
    if (destruir_elemento)
        for (size_t i = 0; i < heap->cantidad; i++) {
            destruir_elemento(heap->arreglo[i]);
        }
    free(heap->arreglo);
    free(heap);
    return;
}

size_t heap_cantidad(const heap_t *heap) {
    return heap->cantidad;
}

bool heap_esta_vacio(const heap_t *heap) {
    return heap->cantidad == 0;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem) {
    if (!elem) return false;
    if (heap->cantidad + 1 == heap->capacidad && !heap_redimensionar(heap, heap->capacidad * FACTOR_REDIMENSION))
        return false;

    // agregamos el elemento a la ultima pos.
    size_t pos = heap->cantidad;
    heap->arreglo[pos] = elem;
    heap->cantidad++;

    // llamamos a upheap paa ese elem
    upheap(heap->arreglo, heap->cantidad, pos, heap->cmp);
    return true;
}

void *heap_ver_max(const heap_t *heap) {
    if (heap->cantidad == 0) return NULL;
    return heap->arreglo[0];
}

/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap) {
    if(heap->cantidad == 0) return NULL;
    if (heap->cantidad <= heap->capacidad / ACHICAR_ARREGLO && !heap_redimensionar(heap, heap->capacidad / FACTOR_REDIMENSION))
        return false;

    // eliminamos el primer elemento del arreglo / raiz
    void* dato = heap->arreglo[0];

    // swapeammos ultimo con la pos borrada
    heap->cantidad--;
    swap_elem(heap->arreglo, 0, heap->cantidad);

    // llamamos a downheap para el nuevo primero
    downheap(heap->arreglo, heap->cantidad, 0, heap->cmp);

    return dato;
}

// Funcion auxiliar que rediemensiona el el arreglo del heap a "nuevo_tam".
// Pre: recibe un heap valido, y un tamano positivo.
// Post: devuelve false si fallo el realloc, true si sale todo bien.
bool heap_redimensionar(heap_t* heap, size_t nuevo_tam){
    void* aux = realloc(heap->arreglo, sizeof(void*) * nuevo_tam);
    if (!aux) return false;
    heap->arreglo = aux;
    heap->capacidad = nuevo_tam;
    return true;
}

// Funcion auxiliar que recibe un arreglo, y dos posiciones válidas del mismo. Intercambia los elementos entre ambas posiciones.
void swap_elem(void* arreglo[], size_t pos1, size_t pos2) {
    void *temp = arreglo[pos1];
    arreglo[pos1] = arreglo[pos2];
    arreglo[pos2] = temp;
}

void downheap(void* arreglo[], size_t tam, size_t pos_padre, cmp_func_t cmp) {
    if (tam - 1 == pos_padre) return;    // si llegamos al final, return.
    size_t h_izq = 2 * pos_padre + 1;
    size_t h_der = 2 * pos_padre + 2;
    size_t max = pos_max(arreglo, tam, pos_padre, h_izq, h_der, cmp);
    if(max != pos_padre){
        swap_elem(arreglo, pos_padre, max);
        downheap(arreglo, tam, max, cmp);
    }
}

void upheap(void* arreglo[], size_t tam, size_t pos_hijo, cmp_func_t cmp) {
    if(pos_hijo == 0) return;
    size_t pos_padre = (pos_hijo - 1) / 2;
    if(cmp(arreglo[pos_padre], arreglo[pos_hijo]) < 0){
        swap_elem(arreglo, pos_padre, pos_hijo);
        upheap(arreglo, tam, pos_padre, cmp);
    }
}

// Funcion que recibe un arreglo de elementos genericos, su tamaño (n) y una función de comparación, y modifica in-place el arreglo convirtiéndolo en un Heap en O(n)
void heapify(void *arreglo[], size_t tam, cmp_func_t cmp) {
    for (size_t i = (tam / 2) + 1; i >= 0; i--){
        downheap(arreglo, tam, i, cmp);
        if(i == 0) break; // como i es de tipo size_t no admite valores negativos
    }
}

//Recibe un arreglo, y las posiciones del padre y sus dos hijos. Devuelve la posición del máximo entre los tres.
size_t pos_max(void *arreglo[], size_t tam, size_t pos_padre, size_t pos_h_izq, size_t pos_h_der, cmp_func_t cmp){
    size_t pos_max = pos_padre;
    if(pos_h_izq < tam && cmp(arreglo[pos_max], arreglo[pos_h_izq]) < 0) pos_max = pos_h_izq;
    if(pos_h_der < tam && cmp(arreglo[pos_max], arreglo[pos_h_der]) < 0) pos_max = pos_h_der;
    return pos_max;
}

//HeapSort
//Recibe un arreglo de elementos, su tamaño (n), y una función de comparación
//Ordena el arreglo in-place, con complejidad O(n log n), utilizando las funciones heapify y downheap
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);
    size_t nuevo_tam = cant;
    for(size_t i = 0; i < cant; i++){
        swap_elem(elementos, 0, nuevo_tam - 1);
        nuevo_tam--;
        downheap(elementos, nuevo_tam, 0, cmp);
    }
}

