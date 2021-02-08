from cola import Cola
from ejemplos import actores_lazy as calcular_actores
import sys
sys.setrecursionlimit(10000)


def bfs(grafo, origen):
    visitados = set()
    padres = {}
    orden = {}
    padres[origen] = None
    orden[origen] = 0
    visitados.add(origen)
    q = Cola()  # usar deque de collections, NO QUEUE!!
    q.encolar(origen)
    while not q.esta_vacia():
        v = q.desencolar()
        for w in grafo.adyacentes(v): # E1 + E2 + E3 + ... + Ev = k E
            if w not in visitados:
                padres[w] = v
                orden[w] = orden[v] + 1
                visitados.add(w)
                q.encolar(w)
    # O(V + E)
    return padres, orden


def dfs(grafo, v, visitados, padres, orden):
    for w in grafo.adyacentes(v):
        if w not in visitados:
            visitados.add(w)
            padres[w] = v
            orden[w] = orden[v] + 1
            dfs(grafo, w, visitados, padres, orden)


def recorrido_dfs_completo(grafo):
    visitados = set()
    padres = {}
    orden = {}
    for v in grafo:
        if v not in visitados:
            visitados.add(v)
            padres[v] = None
            orden[v] = 0
            dfs(grafo, v, visitados, padres, orden)
    return padres, orden


def reconstruir_camino(padres, destino):
    recorrido = []
    while destino is not None:
        recorrido.append(destino)
        destino = padres[destino]
    return recorrido[::-1]


if __name__ == "__main__":
    actores = calcular_actores.get()
    padres, orden = recorrido_dfs_completo(actores)
    print(padres)
    print(orden)
    print(" -> ".join(reconstruir_camino(padres, "Williams Robin")))

