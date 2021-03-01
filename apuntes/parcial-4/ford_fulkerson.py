def flujo(grafo, s, t):
    flujo = {}
    for v in grafo:
        for w in grafo.adyacentes(v):
            flujo[(v, w)] = 0
    grafo_residual = copiar(grafo)
    while (camino = obtener_camino(grafo_residual, s, t)) is not None:
        capacidad_residual_camino = min_peso(grafo, camino)
        for i in range(1, len(camino)):
            if camino[i] in grafo.adyacentes(camino[i-1]):
                flujo[(camino[i-1], camino[i])] += capacidad_residual_camino
                actualizar_grafo_residual(grafo_residual, camino[i-1], camino[i], capacidad_residual_camino)
            else:
                flujo[(camino[i], camino[i-1])] -= capacidad_residual_camino
                actualizar_grafo_residual(grafo_residual, camino[i], camino[i-1], capacidad_residual_camino)
    return flujo