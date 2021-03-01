def camino_minimo_dijkstra(grafo, origen):
    dist = {}
    padre = {}
    for v in grafo:
        dist[v] = float("inf")
    dist[origen] = 0
    padre[origen] = None
    q = Heap()
    q.encolar((0, origen))
    while not q.esta_vacio():
        _, v = q.desencolar()
        for w in grafo.adyacentes(v):
            if dist[v] + grafo.peso(v, w) < dist[w]:
                dist[w] = dist[v] + grafo.peso(v, w)
                padre[w] = v
                q.encolar((dist[w], w))
    return padre, dist

