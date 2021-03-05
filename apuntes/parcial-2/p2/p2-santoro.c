// Maximo Santoro, Padron: 105572.
// Ejercicios a hacer 3 - 5 - 9

// Ej 3
/*
3. Implementar para el ABB una primitiva lista_t* abb_claves_debajo(const abb_t* abb, const char* clave) que
obtenga todas las claves del sub-arbol en el que dicha clave es raíz. Las lista devuelta debe quedar ordenada. En caso de no
encontrarse la clave, devolver una lista vacía. Por simplicidad, suponer que las claves se comparan con strcmp[1]. Indicar y
justificar la complejidad de la primitiva. En el árbol del ejemplo, invocando con clave T, debería devolverse [K, L, T, X,
Y, Z]. A efectos del ejercicio, la estructura del árbol es:
*/
#include "lista.h"

typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
} nodo_abb_t;

typedef struct abb {
    nodo_abb_t* raiz;
    size_t cantidad;
} abb_t;

lista_t* claves_debajo(const abb_t* abb, const char* clave) { // funcion wrapper, con solo operaciones ctes... No afecta la acotacion de la complejidad de la primitiva. 

    lista_t* lista = lista_crear(); // O(1)
    if (lista == NULL) {    // O(1)
        return NULL;
    }
    _abb_debajo(abb->raiz, clave, lista);
    return lista;
}

void _abb_debajo(const nodo_abb_t* nodo, const char* clave, lista_t* lista) {   // esta busqueda seria una busqueda binaria O(log n)
    if (nodo == NULL)   // O(1)
        return;

    if (strcmp(nodo->clave, clave) == 0) {  // O(1)
        _abb_obtener_claves(nodo, lista);
    }
    if (strcmp(nodo->clave, clave) < 0) {
        _abb_debajo(nodo->der, clave, lista);
    }
    if (strcmp(nodo->clave, clave) > 0) {
        _abb_debajo(nodo->izq, clave, lista);
    }
    return;
}

void _abb_obtener_claves(nodo_abb_t* actual, lista_t* lista) {   // agrego a la lista en Pre-Order. (para que funcione tal como lo indica el ejemplo dado)
                                                                 // complejidad de esta funcion: O(n), (tengo que insertar cada elemento en el sub-arbol a la lista)
    if (actual == NULL) return;
    _abb_obtener_claves(actual->izq, lista);
    lista_insertar_ultimo(lista, (void*)actual->clave);
    _abb_obtener_claves(actual->der, lista);
    return;
}

// INDICACION Y JUSTIFICACION DE COMPLEJIDAD DE LA PRIMITIVA- EJ 3:

// La complejidad de la funcion seria O(log n) para la busqueda de la clave, ya que seria practiamente una busqueda binaria.
// y luego la complejidad de agregar todo el sub-arbol a la lista, es de: O(k), k siendo los k elementos en el sub-arbol. 
// Pero como creo que no puedo acotar K a nada, ya que tranquilamente me podrian pasar la clave de la raiz del arbol original, diria que la complejidad es de O(n).
// Teniendo en cuenta todo esto, si juntamos las 3 funciones, la complejidad quedaria de la siguiente forma:
// T(n) = O(1) [varias operaciones constantes, wrapper, comparaciones, strcmp] + O(log n) [busqueda de la clave en el arbol] + O(n) [guardado de todas las claves del sub-arbol con raiz en la clave dada por parametro a la primitiva.]

// RTA
// por lo que el caso mas general la complejidad de la primitiva seria: T(n) = O(n)




// Ej 5
/*
5. Implementar una función que reciba un arreglo de n números enteros y un número K y determine, en tiempo lineal de n, si
existe un par de elementos en el arreglo que sumen exáctamente K. Justificar la complejidad de la función implementada.
*/
#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"


bool par_suma(int arreglo[], size_t n, int k) {
    hash_t* hash = hash_crear(NULL);    // esto creo que deberia contarlo como O(1), pero tengo que inicializar a 0 y NULL toda la tabla asi que lo cuento como O(n), de todas formas, no imfluye en la complejidad final. 


    for (size_t i = 0; i < n; i++) {    // el for seria: n veces el O(1), por ende: O(n)
        hash_guardar(hash, arreglo[i], arreglo[i]);  // O(1) // aca hice que la clave es igual al numero porque dijeron en clase que no era importante pasarlo a string y eso. (en el parcial)
    }                                                


    int valor = 0, sumando = 0;     // O(1)


    for (size_t i = 0; i < n; i++) {    // la complejidad de este for seria de O(n)

        valor = hash_obtener(hash, arreglo[i]);     // O(1)
        sumando = valor - k;        // O(1)
        if (hash_pertenece(hash, sumando)) {    // O(1)
            hash_destruir(hash);        // O(n), pero aunque sea un O(n) dentro del for, no quedaria cuadratico ya que se llamaria una sola vez a hash_destruir, en el caso de que se encuentre el numero. 
            return true;    // O(1)
        }
    }


    hash_destruir(hash);    // O(n)
    return false;       // O(1)
}

// La complejidad de la funcion implementada quedaria asi: todas las operaciones constantes (O(1)) + primer for (O(n)) + segundo for (O(n)) + hash_destruir (O(n))
// Por lo que quedaria: T(n) = O(1) + 3*O(n) = O(n).
// Por lo que quedaria una funcion lineal. 







// Ej 9
/*
9. Definir si las siguientes afirmaciones son verdaderas o falsas, y justificar.

a. Si queremos ordenar por año todos los sucesos importantes ocurridos en el mundo desde el año 0 hasta la actualidad,
CountingSort es una buena alternativa. Consideremos que todos los años hay sucesos importantes, y en este en
particular sólo faltó la invasión zoombie (aúnque todavía queda diciembre. . . ).

RTA 9-A: Falso, CountingSort no seria el indicado ya que hay demasiados anios, por lo que el rango quedaria muy alto y no creo que sea la forma mas eficiente de solucionarlo.
Por eso creo que si realmente nos encontramos en un caso en el que sabemos que TODOS los anios hay sucesos importantes,
desde el anio 0 hasta el actual, podemos usar BucketSort ya que para aplicar este metodo de ordenamiento la distribucion de los datos debe ser conocida y debe ser uniforme tambien. (uniformemente distribuida).
Por lo que creo que un caso perfecto para utilizar BucketSort. En este caso seria un algoritmo mucho mas eficiente, ya que podemos dividir en pequenios buckets de partes iguales, ordenar con cualquier otro metodo de ordenamiento que nos convenga y luego unirlos. 


b. RadixSort logra una complejidad lineal (dadas las condiciones adecuadas) reduciendo la cantidad de comparaciones
que realiza entre los datos.

RTA 9-B: FALSO, RadixSort en si no tiene forma de reducir la cantidad de comparaciones que realiza entre datos, ya que va a comparar L veces, 
L siendo la cantidad de criterios con los que se este ordenando.
La unica forma que se me ocurre que pueda llegar a pasar, es consiguiendo un ordenamiento interno que EN un caso especifico logre tener una complejidad lineal,
por lo que el orden de ese RadixSort seria O(L(n)), n siendo los n elementos a ordenar, y L siendo la cantidad de digitos (o componentes a tener en cuenta al ordenar),
A pesar de esto, creo que la premisa es falsa por este motivo, para que se de esto dependemos del ordenamiento interno (si es que lo encontramos y tenemos las "condiciones adecuadas").


c. Un potencial problema de Hash & Displace es que requerimos de varias funciones de hashing, y ni así podemos estar
seguros que todo funcionará (salvo que sean realmente muchas).

RTA 9-C: yo diria que es FALSO. Si bien puede llegar a representarnos un problema del hecho de conseguir varias funciones de hashing. Segun vimos en clase,
si tenemos masomenos 5 funciones, e independientemente de la cantidad de elementos que tengamos, nos podemos quedar tranquilos, y efectivamente va a fucionar bien el metodo. 

Y tambien notar que si agregamos un algoritmo (que todavia no vimos), que contiene el uso de grafos, deberia funcionar aun mejor y con solo 2 funciones de hashing. 
*/