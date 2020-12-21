def distancia_exacta_bfs(grafo, orgien, n): # O(v + e)
    q = Cola()
    q.encolar(orgien)
    distancia = {}
    distancia[orgien] = 0
    lista = []
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.obtener_adyacentes(v):
            if w not in distancia:
                # si es distancia <= va todo append
                distancia[w] = distancia[v] + 1
                q.encolar(w)
                if distancia[w] == n:
                    lista.append(w)
                if distancia[w] > n:
                    return lista
    return lista


def vertices_x_componente(grafo):
    visitados = {}
    lista = []
    for v in grafo:
        if v not in visitados:
            lista_conexa = []
            _vertice_x_componente_dfs(grafo, v, lista_conexa, visitados)
            lista.append(lista_conexa)
    return lista

def _vertices_x_componente_dfs(grafo, v, lista, visitados):
    visitados[v] = True
    lista.append(v)
    for w in grafo.adyacentes(v):
        if w not in visitados: 
            _vertices_x_componente_dfs(grafo, w, lista, visitados)
# def lista_cc(grafo): #armar una lista con listas de todas las componentes conexas 
#     lista_de_listas = [] 
#     visitados = {}
#     for v in grafo.vertices():
#         lista.append


# def dfs(v, g, visitados):
#     visitados[v] = True
#     lista_devolver = []
#     lista_devolver.append(v)
#     for w in g.adyacentes(v):
#         if w not in visitados:
#             l_dfs = dfs(w, g, visitados)
#             lista_devolver.extend(l_dfs)
#     return lista_devolver


def compra_venta_bfs(grafo):    # es_bipartito
    q = Cola()
    origen = grafo.obtener_vertice_random()
    q.encolar(origen)
    usuario_producto = {}
    usuario_producto[origen] = True
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w in usuario_producto:
                if usuario_producto[w] == usuario_producto[v]:
                    return False
            else:
                usuario_producto[w] = not(usuario_producto[v])
                q.encolar(w)
    return True

def instagram_recomendados(grafo, origen):  #recomienda los que sigue mis seguidos y nada mas. o sea, tercer layer. 
    # O (v + e)
    visitados = set()   
    orden = {}
    recomendaciones = []
    q = Cola()

    visitados.add(origen)
    orden[origen] = 0
    q.encolar(origen)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                orden[w] = orden[v] + 1
                visitados.add(w)
                if orden[w] == 2:
                    recomendaciones.append(w)
                else:
                    q.encolar(w)
    return recomendaciones


#ejercicio de orden topologico
def grafo_desde_palabras(palabras):

    grafo = Grafo(es_dirigido=True)
    for i in range(len(palabras) - 1):
        p1 = palabras[i] 
        p2 = palabras[i + 1]

        for letra in p1: 
            grafo.agregar_vertices(letra)

        for j in range(len(p1)):
            grafo.agregar_vertices(p2[j])
            grafo.agregar_arista(pi[j], p2[j], 1)
            break
    return grafo

def idioma_alien(palabras):
    grafo = grafo_desde_palabras(palabras)  # O(n) siendo n la sumatoria de letras en cada palabra
    grados = {}

    for v in grafo:
        for w in grafo.adyacentes(v):
            grados[w] = grados.get(w, 0) + 1

    cola = deque()

    for v in grafo:
        if v not in grados:
            cola.append(v)
    
    result = []

    while len(cola) > 0:
        v = cola.popleft()
        result.append(v)
        for w in grafo.adyacentes(v):
            grados[w] = grados[w] - 1
            if grados[w] == 0:
                cola.append(w)

    return result       # todo lo demas es O (v + e)    #e cantidad de palabras y v letras distintas

# O (n + (v + e))

# ejercicio de k merge
# escribir en C una funcion k_merge que reciba k arreglos ordenados y devuelva uno nuevo con todos los elementos ordenados entre si. 

typedef struct minimo {
    size_t valor_pos;
    size_t arr_pos;
    
}