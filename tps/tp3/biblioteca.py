from grafo import *
from collections import deque
from random import choice
DAMPING_FACTOR = 0.85 #Damping factor del Page Rank
PAGERANKS_ITERACIONES = 50 #Cantidad de iteraciones del Page Rank y Page Rank personalizado
LARGO_RANDOMWALK = 100 #Largo del RandomWalk del Page Rank personalizado

def camino_minimo_bfs(grafo, origen, destino):
    '''
    Dado un grafo no pesado, vértice origen y un vértice destino válidos, devuelve un diccionario de padres si encuentra un camino mínimo entre ambos vértices. En caso de no encontrar un camino devuelve None.
    Pre: El grafo fue creado y es no pesado, los vértices origen y destino pertenecen al grafo.
    Post: Se devolvió el diccionario de padres {Vértice : Padre} en el caso de encontrar el camino mínimo entre los vértices dados. En caso contrario, se devolvió None.
    '''
    visitados = set()
    padres = {}
    padres[origen] = None
    visitados.add(origen)
    q = deque()
    q.append(origen)
    while len(q) != 0:
        v = q.popleft()
        for w in grafo.obtener_adyacentes(v):
            if w not in visitados:
                padres[w] = v
                if w == destino:
                    return padres
                visitados.add(w)
                q.append(w)
    #No se encontro el destino
    return None

def reconstruir_camino(padres, destino):
    '''
    Dado un diccionario de padres y el vértice destino, devuelve una lista de vértices en orden (origen-destino).
    Pre: El diccionario de padres y el vértice destino son válidos. El vértice destino está incluido en el diccionario padres.
    Post: Se devolvió la lista del recorrido desde el origen hasta el destino.
    '''
    recorrido = []
    if not padres:
        return None
    while destino is not None:
        recorrido.append(destino)
        destino = padres[destino]
    return recorrido[::-1]

def pagerank(grafo):
    '''
    Dado un grafo devuelve un diccionario de los Page Rank de los vértices del mismo.
    Pre: El grafo fue creado.
    Post: Se devolvió el diccionario de Page Ranks con los vértices como claves y los Page Rank de cada uno como valor {VERTICE : PR(VERTICE)}
    '''
    pr_iter_anterior = {}
    cant_vertices = grafo.obtener_cantidad_vertices()
    #Inicializo los PR de los vertices en 1/V
    for v in grafo.obtener_vertices():
        pr_iter_anterior[v] = 1 / cant_vertices
    for i in range (PAGERANKS_ITERACIONES):
        pagerank = {}
        for v in grafo.obtener_vertices():
            suma_pr_ady = 0
            for w in grafo.obtener_adyacentes(v):
                suma_pr_ady += pr_iter_anterior[w] / len(grafo.obtener_adyacentes(w))
            pagerank[v] = (1 - DAMPING_FACTOR) / cant_vertices + DAMPING_FACTOR * suma_pr_ady
        pr_iter_anterior = pagerank
    return pagerank

def pagerank_personalizado(grafo, origen):
    '''
    Dado un grafo y un vértice origen devuelve un diccionario de los Page Ranks de los vértices cercanos al vértice origen.
    Pre: El grafo fue creado y el vértice origen es parte del mismo.
    Post: Se devolvió un diccionario con los vértices cercanos al origen como clave y sus Page Ranks como valores.
    '''
    pagerank_pers = {}
    for i in range(PAGERANKS_ITERACIONES):
        valor_actual = 1
        v = origen
        for j in range(LARGO_RANDOMWALK):
            w = choice(list(grafo.obtener_adyacentes(v).keys()))
            pagerank_pers[w] = pagerank_pers.get(w, 0) + valor_actual / len(grafo.obtener_adyacentes(v))
            valor_actual = pagerank_pers[w]
            v = w
    return pagerank_pers

# CICLO N

def camino_hamil(grafo, v, visitados, n, camino):
    if len(visitados) > n:
        return False
    if len(visitados) == n:
        for x in grafo.obtener_adyacentes(camino[-1]):
            if x == v:
                return True
        return False
    if grafo.obtener_adyacentes(v) == None:
        return False
    visitados.add(v)
    camino.append(v)
    for w in grafo.obtener_adyacentes(v):
        if w not in visitados:
            if camino_hamil(grafo, w, visitados, n, camino):
                return True
    # if v in visitados:
    visitados.remove(v)
    camino.pop()
    return False

def ciclo_n(grafo, n, vertice):
    visitados = set()
    lista = []
    visitados.add(vertice)
    ok = camino_hamil(grafo, vertice, visitados, n, lista)
    if not ok:
        return None
    return lista

# def _ciclo_n(grafo, visitados, avanzado, n, inicial, final):
#     if avanzado > n:
#         return False, None
#     if avanzado == n:
#         return True, []

#     for v in grafo.obtener_adyacentes(inicial):
#         if v == final and avanzado != n:
#             return False, None
#         if v not in visitados:
#             visitados.add(v)
#             ok, lista = _ciclo_n(grafo, visitados, avanzado + 1, n, v, final)
#             if ok:
#                 lista.append(inicial)
#                 return ok, lista
#             else:
#                 visitados.remove(v)
#     return False, None

# def ciclo_n(grafo, n, vertice):
#     visitados = set()
#     ok, lista = _ciclo_n(grafo, visitados, 0, n, vertice, vertice)
#     if ok:
#         lista.reverse()
#     return lista


# TODAS EN RANGO 

def rango_n(grafo, v, n):
    contador = 0
    orden = {}
    orden[v] = 0
    q = deque()
    q.appendleft(v)
    while len(q) != 0:
        v = q.pop()
        for w in grafo.obtener_adyacentes(v):
            if w not in orden:
                orden[w] = orden[v] + 1
                if orden[w] == n:
                    contador += 1
                q.appendleft(w)
    return contador

# COEFICIENTE DE CLUSTERING
def clustering_v(grafo, vertice):
    grado_de_salida = len(grafo.obtener_adyacentes(vertice))
    if grado_de_salida < 2:
        return 0
    aristas_entre_adyacentes = 0

    for v in grafo.obtener_adyacentes(vertice):
        for w in grafo.obtener_adyacentes(vertice):
            if grafo.es_adyacente(v, w):
                aristas_entre_adyacentes += 1 # en grafo no dirigido terminamos sumando 2 ya que pasaria 2 veces por la misma relacion en este doble for.

    return round(aristas_entre_adyacentes / (grado_de_salida * (grado_de_salida - 1)), 3) # aca casi seguro que no habria que multiplicarlo por 2.
