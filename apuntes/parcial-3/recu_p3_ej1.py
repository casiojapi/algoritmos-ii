# Maximo Santoro. Padron: 105572. Recuperatorio parcialito 3. Ejercicio 1 (lo hago separado porque lo implemente en python)

# // !. Contamos con un grafo dirigido que modela un ecosistema. En dicho grafo, cada vértice es una especie, y cada arista (v, w)
# // indica que v es depredador natural de w. Considerando la horrible tendencia del ser humano por llevar a la extinción especies,
# // algo que nos puede interesar es saber si existe alguna especie que, si llegara a desaparecer, rompería todo el ecosistema:
# // quienes la depredan no tienen un sustituto (y, por ende, pueden desaparecer también) y/o quienes eran depredados por
# // esta ya no tienen amenazas, por lo que crecerán descontroladamente. Implementar un algoritmo que reciba un grafo de
# // dichas características y devuelva una lista de todas las especies que cumplan lo antes mencionado. Indicar y justificar la
# // complejidad del algoritmo implementado.



# La idea es pasar el grafo a un no dirigido para poder buscar los puntos de articulacion, y encima me da lo mismo para que lado va la flecha o sea la direccion de la arista. Y de ahi saco los puntos de articulacion. 
# Por lo que la complejidad de la funcion sera O(2 (v + e)) = O (v + e)

def dirigido_a_no_dirigido(grafo):  #O(v + e)
    no_dirigido = Grafo(dirigido = False)
    for v in grafo.vertices():
        no_dirigido.agregar_vertice(v)
        for w in grafo.adyacentes(v):
            no_dirigido.agregar_vertice(v, w) # asumo que al haber declarado cuando cree el grafo que es dirigido = False, cuando agrego un vertice, este va de v a w y de w a v. De no ser asi, habria que agregar no_dirigido.agregar_vertice(w, v) tambien
    return no_dirigido
            

def puntos_articulacion(grafo, v, visitados, es_raiz, orden, mas_bajo, especies): # O(v+e)
    visitados.add(v)
    hijos = 0
    #no hace falta diccionario de padres
    for w in grafo.adyacentes(v):
        if w not in visitados:
            orden[w] = orden[v] + 1
            hijos += 1
            puntos_articulacion(grafo, w, visitados, False, orden, mas_bajo, especies)
            if mas_bajo[w] >= orden[v]:
                especies.append(v)
            mas_bajo[v] = min(mas_bajo[v], mas_bajo[w])
        else:   #hay un ciclo -> arista de retorno
            mas_bajo[v] = min(mas_bajo[v], orden[w])
    if es_raiz and hijos > 1:
        especies.append(v)

# y el wrapper de la funcion final seria asi:

def busqueda_de_especies(grafo):
    v = grafo.obtener_vertice_random()
    especies_importantes = []
    visitados = set()
    # apilados = set()
    # pila = Pila()
    orden = {}
    # indice = 0
    mas_bajo = {}   # del principio hasta aqui es O(1)
    # _busqueda_de_especies(grafo, v, visitados, pila, apilados, orden, mas_bajo, especies_importantes, indice) # O(v+e)
    no_dirigido = dirigido_a_no_dirigido(grafo)
    puntos_articulacion(no_dirigido, v, visitados, True, orden, mas_bajo, especies_importantes)

    return especies_importantes

# la complejidad de la fucion final sera de O(v + e), ya que recorro todos los vertices y todas las aristas. ( lo hago 2 veces, pero eso no afecta la cota de complejidad total)