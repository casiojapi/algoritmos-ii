def mst_prim(grafo):    #O(E * log(V))
    v = grafo.vertice_aleatorio()
    visitados = set()
    visitados.add(v)
    q = Heap()
    for w in grafo.adyacentes(v):
        q.encolar((v, w), grafo.peso(v, w))
    arbol = Grafo(es_dirigido=False, lista_vertices=grafo.obtener_vertices())
    while not q.esta_vacio():
        (v, w), peso = q.desencolar()
        if w in visitados:
            continue
        arbol.agregar_arista(v, w, peso)
        visitados.agregar(w)
        for x in grafo.adyacentes(w):
            if x not in visitados:
                q.encolar((w, x), grafo.peso(w, x))
    return arbol

def obtener_aristas(grafo): #O(V + E)
    aristas = []
    for v in grafo:
        for w in grafo.adyacentes(v):
            aristas.append((v, w, grafo.peso(v, w)))
    return aristas

def mst_kruskal(grafo):
    conjuntos = UnionFind(grafo.obtener_vertices())
    aristas = sorted(obtener_aristas(grafo), key=lambda arista: arista[2])
    arbol = Grafo(False, grafo.obtener_vertices())
    for a in aristas:
        v, w, peso = a
        if conjuntos.find(v) == conjuntos.find(w)
            continue
        arbol.agregar_arista(v, w, peso)
        conjuntos.union(v, w)
    return arbol
