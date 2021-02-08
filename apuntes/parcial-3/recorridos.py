def bfs(grafo, origen): 
    visitados = set()
    padres = {}
    orden = {}
    q = Cola()
    visitados.add(origen)
    padres[origen] = None
    orden[origen] = 0
    q.encolar(origen)
    # hasta aca todo O(1)
    while not q.esta_vacia():   # O(v + e) teniendo en cuenta que ver los adyacentes es O(1), esto depende de la implementacion del grafo. Por default seria esa.
        v = q.desencolar
        for w in grafo.adyacentes(v):
            if w not in visitados:  # esto no recorre todos los vertices en cada iteracion, si no que unicamente los adyacentes... Por lo que terminariamos iterando sobre todos los vertices 2 veces en el caso de un no dirigido por ejemplo, pero no mas que eso. Asi que en la iteracion entera del while, como mucho podemos llegar a O(v + 2e) pero no mas que eso. Por lo que no quedan multiplicando.
                padres[w] = v
                orden[w] = orden[v] + 1
                q.encolar(w)
    return padres, orden
# Os -> PARA CADA VERTICE VOY A RECORRER TODOS SUS ADYACENTES. O(V + E)

# dfs

def dfs(grafo, v, visitados, padre, orden):
    visitados.add(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            padre[w] = v
            orden[w] = orden[v] + 1
            dfs(grafo, w, visitados, padre, orden)

def recorrido_dfs(grafo, origen):
    visitados = set()
    padre = {}
    orden = {}
    padre[origen] = None
    orden[origen] = 0
    dfs(grafo, origen, visitados, padre, orden)
    return padre, orden

def recorrido_dfs_completo(grafo, origen):  # aplica para no dirigidos con mas de una componente conexa o dirigidos con posibles no visitados.
    visitados = set()
    padre = {}
    orden = {}
    for v in grafo:
        if v not in visitados:
            padre[v] = None
            orden[v] = 0
            dfs(grafo, v, visitados, padre, orden)
    return padre, orden