def ord_inter(arr, n):
    return _ord_intern(arr, 0, n-1)

def _ord_intern(arr, ini, fin):
    if ini == fin: return
    med = (ini + fin) // 2
    pos_sh = med + 1
    m_fh = (ini + med) // 2

    for pos_fh in range(m_fh + 1, med + 1):
        aux = arr[pos_fh]
        arr[pos_fh] = arr[pos_sh]
        arr[pos_sh] = aux
        pos_sh += 1

    _ord_intern(arr, ini, med)
    _ord_intern(arr, med + 1, fin)


#mariposas bipartitas

def es_bipartito(grafo):
    if (len(grafo.obtener_vertices())==0): return True
    colores={}
    cola=Cola()
    
    inicial=grafo.vertice_aleatorio()
    cola.encolar(inicial)

    colores[inicial]=0

    while(not cola.esta_vacia()):
        v=cola.desencolar()
        for w in grafo.adyacentes(v):
            if w in colores:
                if(colores[w]==colores[v]): return False
            else:
                colores[w]=1-colores[v]
                cola.encolar(w)

    return True

def hay_clique(grafo, clique):
    for v in clique:
        for w in grafo:
            if v != w and w not in grafo.adyacentes(v):
                return False
    return True

def existe_clique_bt(grafo, v, clique, k):
    if len(clique) == k:
        if hay_clique(grafo, clique):
            return True
        else: return False
    clique.add(v)
    for w in grafo.adyacentes(v):
        if hay_clique(grafo, clique):
            return existe_clique_bt(grafo, w, clique, k)
    clique.remove(v)
    return False

def existe_clique(grafo, k):
    v = grafo.obtener_vertice_random()
    clique = set()
    return existe_clique_bt(grafo, v, clique, k)
            



def camino_hamil(grafo, v, visitados, camino):
    visitados.add(v)
    camino.append(v)
    if len(visitados) == len(grafo):
        return True
    for w in grafo.adyacentes(v):
        if w not in visitados:
            if camino_hamil(grafo, w, visitados, camino):
                return True
    visitados.remove(v)
    camino.pop(v)
    return False
