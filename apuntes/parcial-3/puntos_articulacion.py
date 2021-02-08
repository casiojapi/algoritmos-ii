def puntos_articulacion(grafo, v, visitados, es_raiz, orden, mas_bajo, p_art): # O(v+e)
    visitados.add(v)
    hijos = 0
    #no hace falta diccionario de padres
    for w in grafo.adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            hijos += 1
            puntos_articulacion(grafo, w, visitados, False, orden, mas_bajo, p_art)
            if mas_bajo[w] >= orden[v]:
                p_art.add(v)
            mas_bajo[v] = min(mas_bajo[v], mas_bajo[w])
        else:   #hay un ciclo -> arista de retorno
            mas_bajo[v] = min(mas_bajo[v], orden[w])
    if es_raiz and hijos > 1:
        p_art.add(v)
    
def tarjan(grafo, v, visitados, pila, apilados, orden, mas_bajo, cfcs, *indice):    #o(v+e)
    visitados.add(v)
    pila.apilar(v)
    apilados.add(v)
    mas_bajo[v] = orden[v]
    for w in grafo.adyacentes(v):
        if w not in visitados:
            orden[w] = *indice + 1
            *indice += 1
            tarjan(grafo, w, visitados, pila, apilados, orden, mas_bajo, cfcs)
            mas_bajo[v] = min(mas_bajo[v], mas_bajo[w])
        else if w in apilados:
            mas_bajo[v] = min(mas_bajo[v], orden[w])
    if mas_bajo[v] == orden[v]
        nueva_cfc = []
        do:
            w = pila.desapilar()
            apilados.remove(w)
            nueva_cfc.append(w)
        while w != v
        cfcs.append(nueva_cfc)