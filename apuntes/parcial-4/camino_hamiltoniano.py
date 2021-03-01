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

def coloreo(mapa, pais, coloreados, colores):
    if len(coloreados) == len(mapa):
        return True
    p = pais + 1    #avanzo al siguiente pais
    for c in colores:
        coloreados[p] = c
        if not color_es_valido(mapa, p, coloreados):
            coloreados.remove(p)    #si no es valido retrocedo
            continue
        if coloreo(mapa, p, coloreados, colores):
            return True
    coloreados.remove(p)
    return False

def color_es_valido(mapa, pais, coloreados):
    for p in mapa.adyacentes(pais):
        if p in coloreados and coloreados[p] == coloreados[pais]:
            return False
    return True