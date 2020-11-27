// Arbol binario normal. 

// Raiz: el padre del arbol. el hijo izq de la raiz, es la raiz del sub-arbol izquierdo. 
// Hoja: nodo sin hijos
// Nodo interno: nodo con al menos un hijo

// Busqueda -> O(n)
struct ab {
    struct ab* izq;
    struct ab* der;
    void* dato;
};
size_t altura(const ab_t* ab) {
    if (!ab)
        return 0;
    return max(altura(ab->izq), altura(ab->der)) + 1;
}
// O(n)


// Preorder: mi -> izq -> der

// Inorder: izq -> mi -> der
// Postorder: izq -> der -> mi
// Por Niveles (encolando) por niveles de izq a derre

// ABB: es un AB que cumple con que: 
// + el hijo izquierdo, y todos sus hijos, son menores que la raiz.
// + el hijo derecho, y todos sus hijos, son mayores que la raiz. (propiedades que se cumplen recursivamente)

// Cuando se recorre un ABB in-order, queda ORDENADO.

// Por lo que la busqueda en ABBs es como una busqueda binaria, o sea que O(log n)

// y se inserta como en quicksort. O(log n)

// si el arbol esta balanceado, obtener, guardar, pertenece y borrar son O(log n)

// LA VENTAJA QUE TIENE FRENTE AL HASH, ES QUE SI USO UN INORDER, ME QUEDA TODO EN ORDEN... COSA QUE EN HASH NO EXISTE. 

// el caso patologico cuando se va insertando A, B, C, D, E, F, G ... o sea, que degrada en una lista enlazada. 


////////////////////////////////////////

typedef struct nodo_abb {
    struct nodo_abb* izq;
    struct nodo_abb* der;
    char* clave;
    void* dato;
} nodo_abb_t;

struct abb {
    nodo_abb_t* raiz;
    size_t cant;
    abb_destruir_dato_t destruir;
    abb_comparar_clave_t comparar;
};
// Borrado en ABBs.

// si es una hoja, la matas y listo, nodo anterior ahora apunta a NULL y listo.
// si tiene un solo hijo, matas al middleman, y el ese hijo ahora apunta al abuelo. (o al reves)
// si tiene 2 hijos, buscamos un reemplazante.

// ----------------

// Funciones de comparacion.
// devuelve > 0 si el el primero es mator, devuelve < 0 si es menor o == 0 si son iguales.
// podemos comparar lo que se nos cante. 
// o sea, ordenar segun el criterio que se te cante. 

typedef int (*abb_comparar_clave_t)(const char*, const char*);
// y entra en el abb