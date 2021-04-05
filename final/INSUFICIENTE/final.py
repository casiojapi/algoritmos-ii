# Maximo Santoro. Padron: 105572. DNI: 42822674
# Final - Algoritmos y Programacion II - 26/3/2021

# ej 1
# como tenemos que buscar a k o el numero mas cercano a k en O(log n), lo primero que pense es en una busqueda binaria medio modificada, agregando al algortimo original algunas operaciones O(1) para lograr lo pedido especificamente en este ejercicio, manteniendo la complejidad. 

def busqueda_k(a, k, n):
    if k > a[-1]:
        return a[-1]
    elif k < a[0]:
        return a[0]
    else:
        res = _busqueda_k(a, k, 0, n - 1)
        return a[res]

def _busqueda_k(arr, k, inicio, fin):
    if inicio ==  fin:
        if not arr[inicio] == k:
            if arr[inicio] > k:
                return _closer(arr, inicio, inicio -1, k)
            return _closer(arr, inicio, inicio + 1, k)
        return inicio

    if inicio <= fin:  #no me hace falta chequear esto, ya que ya me fije que este dentro del rango de los numeros en el arreglo en la funcion final (busqueda_k)
        medio = (inicio + fin) // 2
        if arr[medio] == k:
            return medio
        elif k > arr[medio]:
            return _busqueda_k(arr, k, medio + 1, fin)
        else:
            return _busqueda_k(arr, k, inicio, medio - 1)
    else:
        print("error")
        return None
# la idea del algoritmo es que itere hasta
def _closer(arr, a, b, k):
    # if len(arr) 
    if abs(arr[a] - k) < abs(arr[b] - k):
        return a
    return b

#la complejidad es O(log n), porque es la misma que la de busqueda bnnaria, ya que es practicamente el mismo algoritmo, pero tien un par mas de operaciones que son despreciables. 
# igualmente justifico con el teorema del maestro
# T(n) = A * T(n/B) + O(n^C)
# T(n) = 2 * T(n/2) + O(N^0)
# A = 2 -> 2 llamados recursivos
# B = 2 -> proporcion del tamanio original
# C = 0 -> porque las operaciones extra son O(1), o sea n^C = 1 ==> C = 0

# por ende, log base B (A) == C
# log2(2) = 0, por ende la complejidad es O(1 * log n) = O(log n), n siendo la cantidad de elementos en el arreglo. 




#ej 2

# Se tiene el siguiente problema:

# Se quiere implementar una función que reciba un arreglo de n números enteros y un número entero k, y determine si
# hay dos elementos dentro del arreglo que se encuentren como máximo a distancia k.
# Para resolverlo, se implementó un algoritmo que guarda los números en una lista enlazada y, luego, por cada valor m de
# la lista se fija si dentro de la misma se encuentra algún número en el rango [m - k; m + k], solo considerando a m si es
# que apareció al menos dos veces en el arreglo. Dada esta solución, responder, justificando, las siguientes preguntas:
# a. ¿Cuál es la complejidad de dicho algoritmo en términos de n y k?
# b. ¿Cuál estructura de datos se podría haber utilizado para mejorar la complejidad (y cómo), suponiendo que el valor
# de n es significativamente mayor al de k? (sin necesidad de despreciarlo) ¿Cuál sería la complejidad en dicho caso,
# en términos de n y k?
# c. Supongamos que el valor de k crece mucho: proponer un algoritmo que sea una mejor alternativa al punto (b) en
# este escenario.
# d. ¿A partir de qué valor de k ya no conviene utilizar lo indicado en el punto (b), y convendría utilizar lo indicado en
# el punto (c)?

# a)  la lista enlazada va a tener N elementos, y en el peor de los casos se va a iterar toda la lista (O(n)), y en cada iteracion, se iterarara toda la lista en busca de algun numero en rango <= k, (o sea O(n)) de nuevo. Por ende la complejidad de la funcion seria O(N^2), siendo N la cantidad de elementos en el arreglo inicial

# b) Yo usaria un Hash, ya que si N es significativamente mas grande que K, podriamos meter a todos los numeros en el hash, O(n) (y cuando lo creamos, chequeamos que pertenezca antes de guardarlo. Si en algun momento pertenece antes de guardarlo ya podemos devolver true ya que estara a distancia 0). 
# # Y una vez con el hash ahi, podemos ir iterando el hash y en cada valor del hash fijarnos si pertenece algún número en el rango [m - k; m + k]. Entonces, quedaria siendo una funcion con complejidad O(N * 2k) == O(n*k), siendo k mucho mas chico que N. Ya que haremos hash_pertenece 2*k veces en cada elemento del hash. 

# C) Usaria el algoritmo del a, ya que aunque no sea recontra eficiente O(n^2), no depende de K. Por el mismo propuesto por el enunciado.

# D) Ya deja de convenir usar el algoritmo dado en B cuando K es mayor a N (o la mitad de N ya que es 2*k en el algoritmo B). Ya que si K es mas grande que N, termina siendo peor que el cuadratico. O(N * k) vs O(N * N), si k es mas grande que n claramente es peor el N*K.





# ejercicio 3
# Un clique de tamaño K de un grafo es un subgrafo de K vértices (con las aristas que los unen en el grafo original) en el
# que todos se conectan con todos. Es decir, que si sólo consideramos esos K vértices y las aristas entre sí, el (sub)grafo
# sería completo.
# Implementar un algoritmo que reciba un grafo (no dirigido) y un valor K y, por Backtracking, determine si existe en
# dicho grafo un clique de tamaño K.

def _clique(grafo, v, visitados, k):
    visitados.add(v)
    if len(visitados) == k:
        return True
    for w in grafo.adyacentes(v):
        if w not in visitados:
            if _clique(grafo, w, visitados, k):
                return True
    visitados.remove(v)
    return False

def _hay_clique(grafo, v, k):
    visitados = set()
    pertenecientes = set()
    for w in grafo.adyacentes(v):
        if w not in pertenecientes:
            pertenecientes.add(w)
    if _clique(grafo, v, visitados, k):
        return True
    return False

def hay_clique(grafo, k):
    for v in grafo:
        if _hay_clique(grafo, v, k):
            return True
    return False
    
                
# ej 4 en "final.c"


# ejercicio 5)

# Implementar un algoritmo que dado un diccionario, determine si se trata (o puede tratarse) de un diccionario de padres
# de un recorrido BFS sobre un grafo que tenga como vértices las claves de dicho diccionario, que haya comenzado en el
# vértice v (recibido por parámetro). El algoritmo debe ejecutar en tiempo lineal a la cantidad de elementos del diccionario.
# Justificar la complejidad del algoritmo. Aclaración: No se recibe ningún grafo por parámetro. Se pide analizar si el
# formato de los datos del diccionario tienen sentido. Por ejemplo:
# ej1 = {'A': None, 'B': 'A', 'C': 'A'}
# ej2 = {'A': None, 'B': None, 'C': 'A'}
# ej3 = {'A': None, 'B': 'A', 'C': 'A', 'D': 'C', 'E': 'B', 'X': 'C'}
# ej4 = {'A': None, 'B': 'D', 'C': 'B', 'D': 'C'}
# ej5 = {'A': None, 'B': 'A', 'C': 'W'}
# es_diccionario_padres_bfs(ej1, 'A') --> true
# es_diccionario_padres_bfs(ej1, 'B') --> false
# es_diccionario_padres_bfs(ej2, 'A') --> false
# es_diccionario_padres_bfs(ej3, 'A') --> true
# es_diccionario_padres_bfs(ej4, 'A') --> false
# es_diccionario_padres_bfs(ej5, 'A') --> false

def es_diccionario_padres_bfs(dicc, v):
    #sigo en pseudocodigo porque no estoy seguro de como hacer esto en python
    if el padre de v is not None:   #el padre del primer vertice debe ser None si o si.
        return False
    visitados = set()   #la idea aca es armar un set de visitados para ir marcando los vertices visitados.
    visitados.add(v)
    itero cada vertice en el dicc: #for w in dicc:?  # O(n)
        agrego el vertice a visitados
        me fijo si el padre esta en visitados. # para que sea padre debo haberlo visitado antes. Se ve en la implementacion interna de BFS, la dejo abajo por si acaso.
        if padre not in visitados:
            return False
    return True

    # complejidad: O(n), siendo n la cantidad de vertices en el diccionario de padres.
    # Esto porque ya que solo hago operciones O(1), hasta el for, cuando itero cada vertice en el diccionario, y dentro de este for es todo O(1). Por lo que la complejidad termina siendo lineal a la cantidad de vertices en el diccionario.

    # DEJO UN PAR DE ACLARACIONES EN EL BFS PARA JUSTIFICAR LAS DECISIONES DE IMPLEMENTACION EL FUNCION.

def bfs(grafo, origen): 
    visitados = set()
    padres = {}
    orden = {}
    q = Cola()
    visitados.add(origen) 
    padres[origen] = None   # EL ORIGEN SIEMPRE TIENE PADRE NONE
    orden[origen] = 0
    q.encolar(origen)
    while not q.esta_vacia():
        v = q.desencolar    # V ES DESENCOLADO, O SEA QUE O ES EL ORIGEN O SE LE ASIGNO UN PADRE EN EL IF NOT IN VISITADOS.
        for w in grafo.adyacentes(v):
            if w not in visitados:
                padres[w] = v   # PARA PODER ENCOLARLO PRIMERO LE ASIGNO UN PADRE EL CUAL ES UN VERTICE YA VISITADO
                orden[w] = orden[v] + 1
                q.encolar(w)    # RECIEN DESPUES DE ESO LO ENCOLO
    return padres, orden
        




        
        
    