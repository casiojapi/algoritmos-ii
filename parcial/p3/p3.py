# Maximo Santoro. Padron: 105572
# Parcial N3
# Ejercicios a hacer: 2 - 5 - 7



# Ejercicio 5 - G^2
def grafo_cuadrado(grafo_viejo):
    grafo_nuevo = Grafo()
    for v in grafo_viejo:
        grafo_nuevo.agregar_vertices(v) #aca ya tenemos todos los vertices de G^2
    for v in grafo_viejo:   #ahora me pongo a copiar las aristas de distancia <= a 2
        q = Cola()
        q.encolar(v)
        distancia = {}
        distancia{v} = 0
        while not q.esta_vacia():
            u = q.desencolar()      # aca le puse otro nombre para que no se me pise con el v del for anterior
            for w in grafo_viejo.obtener_adyacentes(u):
                if w not in distancia:
                    distancia[w] = distancia[u] + 1
                    if distancia[w] <= 2:
                        grafo_nuevo.agregar_arista(v, w)
                        q.encolar(w)
                    else:
                        continue
                else:
                    distancia[w] += 1
                    if distancia[w] <= 2:
                        grafo_nuevo.agregar_arista(v, w) #esta parte la puse muy por si acaso.
                    else:
                        continue
    return grafo_nuevo
    
# el codigo creo que quedo medio hecho un lio, pero la idea es, primero copiar uno a uno, con el primer for, todos los vertices del grafo viejo al grafo nuevo. (asumo que la primitiva no duplica si ya existe un vertice en el grafo). Esta parte seria O(v), ya que lo unico que hago es recorrer todos los vertices del grafo dado por parametro, y los agrego al nuevo que es O(1)
#por lo tanto el primer for es O(v)

# Y luego viene la parte compicada, que hice una especie bfs para cada vertice del grafo viejo, buscando para cada vertice cada adyacente que esta a 1 y 2 de distancia, y una vez encontrandolos, haciendo esa misma arista en el grafo nuevo. 

# La complejidad de la segunda parte me parece un poco complicada ya que seria un bfs acotado, V veces. El bfs que estoy haciendo deberia diria que es O(V + E), tomandolo como si no lo cortara una vez que llega a los adyacentes a distancia 2, terminaria recorriendo todos los vertices conexos a V y pasando por todas las aristas una vez terminado el while.

# Atencion: no estoy diciendo que el bfs, recorre todos los vertices en cada iteracion, si no que unicamente los adyacentes de v en cada iteracion... Por lo que terminariamos iterando sobre todos los vertices 2 veces en el caso de un no dirigido, pero no mas que eso. Asi que en la iteracion entera del while, como mucho podemos llegar a O(v + 2e), o sea O(v + e).

#Por lo que me termina quedando T(n) = O(v) (primer for) + O(v * (v + e)) (segundo for) = por lo que me queda = O(v * (v + e))

# Aclaracion: estoy teniendo en cuenta que ver adyacentes, agregar_arista, y agregar_vertice son O(1). (y todas las operacions de cola y diccionarios tambien)







# Ejercicio 7 - adjunto como pdf

# 7. Para ayudar a personas con problemas visuales (por ejemplo, daltonismo) el gobierno de Toruń decidió que en una misma
# parada de colectivo nunca pararán dos colectivos que usen colores similares. El problema es que ya saben que eso está
# sucediendo hoy en día, así que van a repintar todos los colectivos. Por problemas de presupuesto, sólo pueden pintar los
# colectivos de color Rojo o Azul. Como no quieren parecer un grupo de improvisados que malgasta los fondos públicos,
# quieren hacer un análisis para saber si es posible cumplir con lo pedido (pintar cada línea Azul o Roja, de tal forma que
# no hayan dos de mismo color coincidiendo en la misma parada). Considerando que se tiene la información de todas las
# paradas de colectivo y qué líneas paran allí, modelar el problema utilizando grafos y explicar un algoritmo que determine si
# es posible resolver el problema. Explicar cuál sería la complejidad de realizar esta validación. Hacer un breve seguimiento de
# algún ejemplo que propongas.