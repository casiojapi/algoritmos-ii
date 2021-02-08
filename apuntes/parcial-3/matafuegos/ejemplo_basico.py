from ejemplos import fronteras


def obtener_aristas(grafo):
    aristas = []
    visitados = set()
    for v in grafo:
        visitados.add(v)
        for w in grafo.adyacentes(v):
            if w not in visitados:
                aristas.append((v, w))
    return aristas


def _dfs_conexo(grafo, v, visitados):
    visitados.add(v)
    for w in grafo.adyacentes(v):
        if w not in visitados:
            _dfs_conexo(grafo, w, visitados)


def es_conexo(grafo):
    visitados = set()
    _dfs_conexo(grafo, grafo.random(), visitados)
    return len(visitados) == len(grafo)


def main():
    print(es_conexo(fronteras))


if __name__ == "__main__":
    main()