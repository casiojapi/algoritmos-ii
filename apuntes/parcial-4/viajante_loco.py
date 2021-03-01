def peso_camino(grafo, camino):
    peso = 0
    for i in range(0, len(camino)-1):
        peso += grafo.peso_arista(camino[i], camino[i+1])
    peso += grafo.peso_arista(camino[-1], camino[0])
    return peso

def camino_hamiltoniano(grafo, v, visitados, camino, caminos):
    visitados.add(v)
    camino.append(v)

    if len(visitados) == len(grafo):
        caminos.add(tuple(camino))

    for w in grafo.adyacentes.(v):
        if w not in visitados:
            camino_hamiltoniano(grafo, w, visitados, camino, caminos)
            continue

    visitados.remove(v)
    caminio.pop()
    return

def viajante(grafo):
    visitados = set()
    caminos = set()
    camino = []
    resultado = float("inf")
    for v in grafo:
        camino_hamiltoniano(grafo, v, visitados, camino, caminos)
    for camino in caminos:
        peso = peso_camino(grafo, camino)
        if resultado > peso:
            resultado = peso
    return resultado