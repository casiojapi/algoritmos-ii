#igual es pseudocodigo
estado[]
DFS(grafo G, vertice_inicial Vi){
	estado[Vi]=VISITADO
	Para cada vecino V de Vi{
		if(estado[V]==NO_VISITADO){
			dfs(G,V)
		}
	}
}

bfs(grafo) {
    cola_t* cola=cola_crear();
	cola_encolar(cola,Vi);
	while(!cola_esta_vacia(cola)){
		v=cola_desencolar(cola);
		Para cada adyacente A de V{
			if estado[A]==NO_VISITADO{
			estado[A]=VISITADO
			distancia[A]=distancia[V]+1
			padre[A]=V
			cola_encolar(cola, A);
			}
		}
	}
}

def es_bipartito (grafo, vertice_inicial):
	colores = { }, cola = cola_crear()
	cola.encolar(vertice_inicial)
	colores[vertice_inicial] = 0 # definimos colores 0 y 1
        
	while not cola.esta_vacia():
		v = cola.desencolar()
		for w in grafo.adyacentes(v):
			if w in colores:
				if colores[w] == colores[v]: return False
			else:
				colores[w] = 1 - colores[v]
				cola.encolar(w)
	return true

def es_bipartito_recursivo (grafo, v, colores):
	for w in grafo.adyacentes(v):
		if w in colores: 
			if colores[w] == colores[v]:
				return False
		else:
			Colores[w] = 1 - colores[v]
			if not es_bipartito(grafo, w, colores):
				return False
	return True

#recorridos de musero dfs

def _dfs(grafo, visitados, vertice):
    visitados[vertice] = True
    mati_disfruta_esta_sala(vertice)
    for ady in vertice.obtener_adyacentes():
        if(!visitados[ady]):
            _dfs(grafo, visitados, ady)


def dfs_generalizado(grafo):
    visitados = set()
    for vertice in grafo.obtener_vertices():
        if(!visitados[vertice]):
            _dfs(grafo, visitados, vertice)
