# Maximo santoro padron: 105572
# Ej a hacer: 2 4 9

# respuesta ej 2:
# el seguimiento esta hecho en el pdf "seguimiento_2.pdf"

# EN un caso general, el arbol de tendido minimo podria dar uno distinto, ya que puede ocurrir que si tenemos bastantes aristas con el mismo peso, se elija arbitrariamente en distinto orden(ya que no hay un criterio determinado de "discriminacion" en el caso de aristas con pesos iguales) Por lo que existe la posibilidad de que quede un arbol de tendido minimo distinto al encontrado por este algoritmo.



# ej 4. Implementar una función que reciba un grafo (no pesado), un vértice v y otro w y, por bactracking, obtenga el largo delcamino mínimo desde v hacia w.

# funcion wrapper

def _camino_minimo_backt(grafo, a, b, nuevo_largo, largo, visitados):
    if a == b:
        nuevo_largo = min(largo, nuevo_largo)
        return 

    visitados.add(a)
    largo += 1
    for v in grafo.adyacentes(a):
        _camino_minimo_backt(grafo, v, b, nuevo_largo, largo, visitados)
    visitados.remove(a)
    largo -= 1

# no estoy muy seguro del funcionamiento de las variables que estoy usando por python. Capaz que lo ideal huiera sido usar globales, o algo parecido a un puntero, ya que tengo un poco de miedo de que se me pisen. Pero nada. . Pero la idea de la funcion seria esa. 

# funcion final - rta

def camino_minimo_backt(grafo, v, w):
    visitados = set()
    nuevo_largo = float("inf")
    largo = float("inf")
    _camino_minimo_backt(grafo, v, w, nuevo_largo, largo, visitados)
    return nuevo_largo




# ej 9:

# A) En esta no estoy muy seguro, pero diria que es Falsa. Yo creo que se puede agregar una arista al grafo original pero no necesariamente se disminuye el flujo original. Ya que podria depender de del peso de la arista que se agregue. 
#  
# B) Falso, no todo grafo dirigido con vertice de grado de entrada 0, y un vertice de salida 0 es red de flujo. 
# Porque puede pasar que el flujo de algun vertice interno de la red el flujo saliente no sea igual al flujo entrante. Por lo que ahi, dejariamos de tener una red de flujo, ya que rompe con la definicion del mismo. Adjunto una foto con un contraejemplo al final del pdf.

# C) Falso, diria que no siempre ya que existe la posibilidad de encontrar un ciclo negativo, y esto hace que no exista un camino minimo ya que podemos quedarnos a ciclar ahi infinitamente. Habia pensado en Bellman-Ford, y justamente al final de ejecutar este algoritmo, una vez recorrido todo el grafo, chequeamos que no siga bajando el peso, ya que si pasa esto, nos damos cuenta que hay un ciclo negativo y por ende, no hay camino minimo. 

