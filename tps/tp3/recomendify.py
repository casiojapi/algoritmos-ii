#!/usr/bin/python3
from biblioteca import *
from comandos import *
from grafo import *
from sys import argv, stdin

def construir_grafo_users(ruta):
    '''
    Dada la ruta de un archivo tsv con los siguientes campos: ID USER_ID	TRACK_NAME  ARTIST	PLAYLIST_ID	PLAYLIST_NAME    GENRES, construye un grafo bipartito no dirigido con los usuarios y canciones como vértices.
    Las aristas unen a un usuario con una canción si el primero tiene una playlist con esa canción. El peso de la arista es una tupla (PLAYLIST_ID, PLAYLIST_NOMBRE).
    Además del grafo devuelve un conjunto con todas las canciones y un dicionario de playlists con el nombre de la playlist como clave y una lista de canciones como valor.
    '''
    grafo_users = Grafo(False)
    canciones = set()
    playlists = {} # {PLAYLIST_NOMBRE : [CANCION1, CANCION2, ..]}
    with open(ruta) as archivo:
        archivo.readline() #Salteo la primer fila (nombre de los campos)
        linea = archivo.readline()
        while linea:
            fila = linea.split('\t')
            user = fila[1]
            cancion_artista = fila[2] + ' - ' + fila[3]
            playlist_id = fila[4]
            playlist_nombre = fila[5]

            grafo_users.agregar_vertice(user)
            grafo_users.agregar_vertice(cancion_artista)
            grafo_users.agregar_arista(user, cancion_artista, (playlist_id, playlist_nombre))

            canciones.add(cancion_artista)

            if playlist_nombre not in playlists:
                playlists[playlist_nombre] = []
            playlists[playlist_nombre].append(cancion_artista)

            linea = archivo.readline()

    return grafo_users, canciones, playlists

def construir_grafo_canciones(playlists):
    '''
    Dado un diccionario de playlists {PLAYLIST_NOMBRE : [CANCION1, CANCION2, ..]}, construye un grafo no dirigido de canciones como vértices. Una canción se une a otra si forman parte por lo menos en una misma playlist.
    Pre: El diccionario de playlists es válido
    Post: Se devolvió el grafo de canciones
    '''
    grafo_canciones = Grafo(False)
    for playlist in playlists:
        for cancion in playlists[playlist]: #Agrego las canciones al grafo
            grafo_canciones.agregar_vertice(cancion)
        for i in range(len(playlists[playlist])):
            for j in range(i + 1, len(playlists[playlist])):
                grafo_canciones.agregar_arista(playlists[playlist][i], playlists[playlist][j])
    return grafo_canciones

def procesar_comandos(grafo_users, canciones, playlists):
    '''
    Dado el grafo bipartito de usuarios y canciones, el conjunto de canciones y el diccionario de playlists se lee el archivo ingresado por entrada estándar y se ejecutan sus comandos.
    '''
    lista_pagerank = []
    grafo_canciones = None
    lineas = stdin.read().splitlines()
    for linea in lineas:
        comando, parametros = parsear_comando(linea)
        if not comando:
            print(linea)
        elif comando == 'camino':
            camino(grafo_users, canciones, parametros[0], parametros[1])
        elif comando == 'mas_importantes':
            mas_importantes(lista_pagerank, grafo_users, canciones, parametros)
        elif comando == 'recomendacion':
            recomendacion(grafo_users, canciones, parametros[0], parametros[1], parametros[2])
        elif comando == 'ciclo':
            if not grafo_canciones:
                grafo_canciones = construir_grafo_canciones(playlists)
            ciclo_n_canciones(grafo_canciones, parametros[0], parametros[1])
        elif comando == 'rango':
            if not grafo_canciones:
                grafo_canciones = construir_grafo_canciones(playlists)
            todas_en_rango(grafo_canciones, parametros[1], parametros[0])
        elif comando == 'clustering':
            if not grafo_canciones:
                grafo_canciones = construir_grafo_canciones(playlists)
            clustering(grafo_canciones, parametros)

def recomendify():
    grafo_users, canciones, playlists = construir_grafo_users(argv[1])
    procesar_comandos(grafo_users, canciones, playlists)

recomendify()
