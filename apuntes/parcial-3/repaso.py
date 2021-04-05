def distancia_n(v, n, grafo):
    orden = {}
    cola = cola_crear()
    cola.encolar(v)
    orden[v] = 0
    lista = []
    while not cola.esta_vacia():
        v = cola_desencolar()
        for w in grafo.adyacentes(v):
            if w in orden:
                continue
            orden[w] = orden[v] + 1
            if orden[w] == n:
                lista.append(w)
            cola.encolar(w)
    return lista

def lista_cc(grafo):
    visitados = {}
    comps = []
    v = grafo.obtener_vertice_random()
    for v in grafo.vertices():
        if v in visitados:
            continue
        comps.append(dfs_conexas(grafo, v, visitados))
    return comps


def dfs_conexas(grafo, v, visitados) -> list:
    visitados[v] = True
    lista = []
    lista.append(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            lista_nueva = dfs_conexas(grafo, w, visitados)
            lista.extend(lista_nueva)
    return lista

def cant_edges(grafo):
    v = len(grafo.vertices())
    e = 0
    for v in grafo.vertices():
        for w in grafo.adyacentes(v):
            e += 1
    e = e / 2
    return e == v - 1

def es_conexo(g):
    return len(lista_cc(g)) == 1

def compra_venta_bipartito(grafo): #bipartito - coloreo
    q = cola_crear()
    origen = grafo.obtener_vertice_random()
    q.encolar(origen)
    a_b = {}
    a_b[origen] = True
    while not q.esta_vacia():
        v = grafo.desencolar()
        for w in grafo.get_adyacentes(origen):
            if w in a_b:
                if a_b[w] == a_b[v]:
                    return False
            else:
                a_b[w] = not (a_b[v])
                q.encolar(w)
    return true


def instagram_recomendaciones(grafo, origen, distancia):    #append a n distancia
    orden = {}
    recomendaciones = []
    q = cola_crear()

    orden[origen] = 0
    q.encolar(origen)

    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v):
            if w not in orden:
                orden[w] = orden[v] + 1
                if (orden[w] == distancia):
                    recomendaciones.append(w)
                else:
                    q.encolar(w)
    return recomendaciones