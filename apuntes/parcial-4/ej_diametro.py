from collections import deque as queue

def diametro(grafo):
    max_min_dist = 0
    for v in grafo:
        distancias = caminos_minimos(grafo,v)
        for w in distancias:
            if distancias[w] > max_min_dist:
                max_min_dist = distancias[w]
    return max_min_dist


def caminos_minimos(grafo,origen):
    q = queue()
    visitados = set()
    distancias = {}
    distancias[origen] = 0
    visitados.add(origen)
    q.appendleft(origen)
    while bool(q):
        v = q.pop()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                distancias[w] = distancias[v] + 1
                q.appendleft(w)
                visitados.add(w)
    return distancias