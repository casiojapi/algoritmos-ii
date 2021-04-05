from grafo import *
from biblioteca import *
from heapq import *
from collections import deque

def parsear_comando(linea):
    '''
    Dada una línea, parsea los comandos y parámetros correspondientes. Devuelve una tupla (comando, parametros). En el caso de que el comando no exista devuelve (None, None)
    '''
    linea_separada = linea.split()
    comando = linea_separada[0]
    if comando == 'camino':
        parametros = linea[7::].split(' >>>> ')
    elif comando == 'mas_importantes':
        parametros = int(linea_separada[1])
    elif comando == 'recomendacion':
        canciones = ' '.join(linea_separada[3::])
        parametros = (linea_separada[1], int(linea_separada[2]), canciones.split(' >>>> '))
    elif comando == 'ciclo' or comando == 'rango':
        cancion = ' '.join(linea_separada[2::])
        parametros = (int(linea_separada[1]), cancion)
    elif comando == 'clustering':
        parametros = ' '.join(linea_separada[1::])
    else:
        return None, None
    return comando, parametros

def camino(grafo_users, canciones, cancion_origen, cancion_destino):
    '''
    Dados el grafo bipartito de ususarios y canciones, el conjunto de canciones, una canción origen y una canción destino, imprime una lista con la cual se conecta (en la menor cantidad de pasos posibles) una canción con otra, considerando los usuarios intermedios y las listas de reproducción en las que aparecen.
    Se imprime un error en el caso de no ser canciones válidas o no haber encontrado un recorrido.
    '''
    if cancion_origen not in canciones or cancion_destino not in canciones:
        print('Tanto el origen como el destino deben ser canciones')
        return
    recorrido = reconstruir_camino(camino_minimo_bfs(grafo_users, cancion_origen, cancion_destino), cancion_destino)
    if not recorrido:
        print('No se encontro recorrido')
        return
    resultado = ''
    for i in range(len(recorrido)):
        if recorrido[i] == cancion_destino:
            resultado += recorrido[i]
            break
        _, playlist = grafo_users.obtener_peso(recorrido[i], recorrido[i + 1])
        if recorrido[i] in canciones:
            resultado += recorrido[i] + ' --> aparece en playlist --> ' + playlist + ' --> de --> '
        else: #Es un usuario
            resultado += recorrido[i] + ' --> tiene una playlist --> ' + playlist + ' --> donde aparece --> '
    print(resultado)

def mas_importantes(lista_pagerank, grafo_users, canciones, n):
    '''
    Dados una lista de los Page Rank de las canciones ordenada [(PR_CANCION1, CANCION1), (PR_CANCION2, CANCION2), ...], el grafo bipartito de usuarios y canciones, el conjunto de canciones y un entero n, imprime una lista de las n canciones más importantes (mayor Page Rank).
    '''
    if (len(lista_pagerank) == 0):
        pr = pagerank(grafo_users)
        for v in pr:
            if v in canciones:
                lista_pagerank.append((pr[v], v))
        lista_pagerank.sort(reverse = True)
    resultado = []
    for i in range(n):
        resultado.append(lista_pagerank[i][1])
    print('; '.join(resultado))

def recomendacion(grafo_users, canciones, que_recomendar, n, lista_canciones):
    '''
    Dados el grafo bipartito de ususarios y canciones, el conjunto de canciones, una cadena indicando que se quiere recomendar ('usuarios' o 'canciones'), un entero n y una lista de canciones, imprime una lista de n canciones o usuarios para recomendar en base a la lista de canciones dada.
    '''
    heap_pr_pers = []
    heapify(heap_pr_pers)
    for cancion in lista_canciones:
        pr_pers = pagerank_personalizado(grafo_users, cancion)
        for v in pr_pers:
            heappush(heap_pr_pers, (- pr_pers[v], v)) #Como heapq es un heap de minimos, tengo que invertir los valores para hacerlo de maximos
    resultado = []
    i = 0
    while i < n:
        _, v = heappop(heap_pr_pers)
        if que_recomendar == 'canciones' and v in canciones and v not in lista_canciones and v not in resultado:
            resultado.append(v)
            i += 1
        elif que_recomendar == 'usuarios' and v not in canciones and v not in resultado:
            resultado.append(v)
            i += 1
    print('; '.join(resultado))

def ciclo_n_canciones(grafo, n, vertice):
    '''
    Devuelve un ciclo de largo n (dentro de la red de canciones) que comienza en la canción indicada.
    Pre: la cancion debe ser valida y pertenecer al grafo
    '''
  
    recorrido = ciclo_n(grafo, n, vertice)
    if not recorrido:
        print("no hay camino")
        return
    resultado = ""
    for i in range(len(recorrido)):
        resultado += recorrido[i] + ' --> '
    resultado += vertice
    print(resultado)


def todas_en_rango(grafo, cancion, n):
    '''
    Devuelve la cantidad de canciones que se encuenten a exactamente n saltos de la cancion pasada por parámetro.
    Pre: la cancion debe ser valida y pertenecer al grafo
    '''
    print(rango_n(grafo, cancion, n))

def clustering(grafo, vertice):
    '''
    Devuelve el coeficiente de clustering de la canción indicada. En caso de no indicar canción, devuelve el clustering promedio de la red.
    Pre: en caso de especificar cancion, esta debe ser valida y pertenecer al grafo
    '''
    if vertice == "":
        total = 0
        n = grafo.obtener_cantidad_vertices()
        for v in grafo.obtener_vertices():
            total += clustering_v(grafo, v)
        print('{:.3f}'.format(round(total / n, 3)))
        return
    print('{:.3f}'.format(round(clustering_v(grafo, vertice), 3)))
