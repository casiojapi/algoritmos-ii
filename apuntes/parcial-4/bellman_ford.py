def bf(grafo, origen):
    distancia = {}
    padre = {}
    for v in grafo:
        distancia[v] = float("inf")
    distancia[origen] = 0
    padre[origen] = None
    aristas = obtener_aristas(grafo)

    for i in range(len(grafo)):
        for v, w, peso in aristas:
            if distancia[v] + peso < distancia[w]:
                padre[w] = v
                distancia[w] = distancia[v] + peso
    
    for v, w, peso in aristas:
        if distancia[v] + peso < distancia[w]:
            return None #ciclo negativo
    return padre, distancia   
             