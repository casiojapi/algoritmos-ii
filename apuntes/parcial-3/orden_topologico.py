def orden_topologico_bfs(grafo): 	# condiciones normales O(v + E)
	grados = {}
	for v in grafo:
		grados[v] = 0
	for v in grafo:
		for w in grafo.adyacentes(v):
			grados[w] += 1
	q = cola_crear()
    for v in grafo:
        if grados[v] == 0:
            q.encolar(v)
    resul = []
    while not q.esta_vacia():
        v = q.desencolar()
        resul.append(v)
        for w in grafo.adyacentes(v):
            grados[w] -= 1	
            if grados[w] == 0:
                q.encolar(w)
    if len(resul) == len(grafo):
        return resul
    else:
        return None # El grafo tiene algun ciclo


#dfs

def orden_topologico(grafo):	# O(v + e)
	visitados = set()
	pila = pila_crear()
	for v in grafo:
		if v not in visitados:
			orden_topologico_rec(grafo, v, pila, visitados)
	return pila_a_lista(pila)

def orden_topologico_rec(grafo, v, pila, visitados):
	visitados.agregar(v)
	for w in grafo.adyacentes(v):
		if w not in visitados:
			orden_topologico_rec(grafo, w, pila, visitados)
	pila.apilar(v)

