# Maximo Santoro. Padron: 105572. DNI: 42822674
# Final - Algoritmos y Programacion II - 5/4/2021


# # ej 3

# Se tiene un programa que, una vez iniciado, lee números enteros desde entrada estándar (para realizar operaciones que
# son irrelevantes para esta consigna). Una vez que la entrada estándar termina, se desea que el programa informe de los
# K valores más grandes de todos los que se han leído de entrada estándar (supongamos que han sido n números). Es
# importante notar que n podría ser una cantidad que no entre en memoria (e.g.se redirecciona la entrada estándar a
# un archivo de 10 Terabytes). Explicar cómo diseñarías un mecanismo/algoritmo para obtener estos K máximos valores,
# qué estructuras de datos utilizarías para esto, y cuál es la complejidad temporal y espacial de dicho mecanismo/algoritmo.
# Considerar que K (un valor pasado por parámetro al programa) es una cantidad que sí entra en memoria. La complejidad
# (en términos de n y K) debe ser la menor posible, considerando la restricción en memoria. Indicar y justificar dicha
# complejidad.

# La estructura que usaria seria un heap de minimos de tamagno K.
# mi idea es a medida que entran los ints por stdin, ir metiendolos en un Heap de minimos e ir llevando la cuenta de los numeros que entran al Heap. 
# Al principio entrarian los primeros K numeros al heap directo.
# Una vez pasados los primeros K, cada vez que se lea un nuevo numero, me fijo que este sea mas grande que el minimo del heap. 
   # Si es mas grande, saco el minimo del heap, libero su memoria, e ingreso el nuevo numero recien leido al heap. 
   # Si es mas chico o igual al minimo del heap, directamente descarto el numero, y libero su memoria. 

# Una ve hecho este ciclo con los N numeros a leer por entrada standard, tengo mi heap de minimos de tamgno K con los K valores mas GRANDES leidos por stdin. 
# Posteriormente, creo una lista y desencolo del heap K veces appendeando uno por uno a la lista, para que me queden los K numeros ordenados. 
# y finalmente liberaria la memoria de la estructura del heap (no de los datos) y devolveria esta lista como resultado.


# la complejidad de memoria de este programa seria O(K), ya que siempre libero los numeros cuando quedan fuera del heap. Y la lista y las otras cosas que tenga que usar como detalles de implementacion, serian constantes (y despreciables) en terminos de memoria. (la lista usaria la mismos nodos que estan en el heap, asi que su memoria adicional seria cte)

# la complejidad temporal de la lectura e ingreso de numeros quedaria en O(N * log(k)), ya que encolo en el heap (log K), N veces. Y luego una vez leido todo, tendria que desencolar K veces e ingresar esos datos desencolados a una lista. Lo que costaria O(k log K) ya que seria K veces desencolar (O(log K)), y appendear a una lista (O(1))
# Por lo que la complejidad temporal se podria acotar a T(N) = O(N * log(k) + k log (k))



# # ej 2

# Dado un grafo no dirigido y pesado (todos pesos positivos), se desea averiguar el camino mínimo de un vértice v hacia
# todos los demás vértices del grafo. Ahora bien, entre dos pares de vértices v y w podría existir más de un camino
# mínimo posible (por supuesto, todos de mismo costo/peso total). Se desea que ante igualdad de costo, se defina que el
# camino a tomar sea el más corto en cantidad de aristas. Explicar (en texto y/o implementando) cómo modificarías
# el algoritmo de Dijkstra para cumplir lo pedido. La complejidad del algoritmo debería quedar tal cual el algoritmo
# original. Indicar y justificar cuál es dicha complejidad, además de por qué no se modifica con la solución planteada.

# Ejemplo: Para el siguiente grafo, se puede llegar desde A hacia D con 3 caminos posibles (detallados debajo). Todos de
# costo 10. Se debe asegurar que el camino elegido sea el primero (el más corto). Lo mismo para los demás vértices destino.

# RTA

# la complejidad de dijkstra es O(E * log V), siendo E la cantidad de aristas, y V la cantidad de vertices

# lo que yo agregaria al algoritmo seria un diccionario de orden, y cuando se encuentra un camino de igual peso, me fijo que el orden sea menor. La complejidad del algoritmo no deberia variar.
# No deberia variar ya que seria unicamente agregar operaciones constantes, o sea, comparaciones (un if), y la creacion y agregar datos al diccionario de orden




# # ej 5
# En clase se ha demostrado que ningún algoritmo de ordenamiento comparativo puede ser mejor que O(n log n), siendo n
# la cantidad de elementos del arreglo a ordenar. Al mismo tiempo, hemos visto algoritmos para obtener un ordenamiento
# topológico de un conjunto de datos que, modelando el problema con grafos (dirigidos), termina resolviéndose en tiempo
# lineal a la cantidad de vértices y aristas del mismo. Explicar por qué en problemas de ordenamientos (e.g.arreglo de
# números de los que no se tiene información) no modelamos siempre a estos con grafos y luego resolvemos utilizando
# alguno de los algoritmos antes mencionados.
# Recomendación: pensar bien este ejercicio, hacerse dibujos, etc. . . antes de ponerse a escribir la respuesta. No responder
# “no se puede resolver de esta forma”, porque sí se puede. Por el contrario, para plantear la respuesta conviene plantearse
# cómo se haría para resolver un problema de ordenamiento usando una resolución de orden topológico. Esta consigna no
# va sobre la posibilidad, sino por qué no es la mejor opción para hacerlo, a pesar de parecer una idea tentadora.

# RTA:
# yo creo que el gran problema a la hora de encarar un problema de ordenamiento de esta forma, seria la complejidad temporal de modelar el grafo. teniendo en cuenta que deberiamos recorrer todo el arreglo de numeros e ir armando el grafo.
# 
# #primero tendria que recorrer todo el arreglo y agregar cada elemento al grafo -> O(n) 
# Y luego tendria que armar las aristas.
# Esto lo haria buscando el minimo vertice en todo el grafo, y una vez obtenido V, iria yendo vertice por vertice indicando cuando hay una arista desde ese vertice hacia otro. (lo cual yo lo haria buscando el proximo numero inmediato ordenado en el grafo, o sea si tengo [1, 3, 4, 8, 9, 2]. arranco por el 1, recorreria todos los vertices hasta encontrar el minimo numero mayor o igual a 1 para conectarlo.)
# Mantendria un diccionario de visitados, y continuaria haciendo lo mismo con el numero al cual conecte el vertice anterior. En el ejemplo dado, conectaria 1->2 ... luego con el 2, busco el proximo minimo mayor o igual a 2. Y asi iria conectando. 
# asi sucesivamente hasta completar todas las conecciones del grafo, y me terminaria dando algo similar a O(N^2) ya que recorro N N veces. y luego, quedaria la parte del orden topologico, o sea, O(n + e). Por lo que creo que no convendria usar este metodo. Ya que me quedaria O N^2. El problema reside en la modelacion del grafo. Supongo que hay una forma mejor de modelarlo de lo que presente, pero estoy seguro que sin informacion previa del arreglo y sus elementos es imposible lograr hacer un modelado que termine siendo mejor que O(n log n). Por lo que seguramente se pueda hacer, pero no valdria la pena nunca (siempre y cuando NO tengamos informacion adicional del arreglo a ordenar o sus elementos. )