from grafo import Grafo
from lazy import LazyValue

def _fuerza_bruta():
    g1 = Grafo(False, range(8))
    g1.arista(0, 1)
    g1.arista(1, 2)
    g1.arista(1, 5)
    g1.arista(2, 3)
    g1.arista(3, 5)
    g1.arista(3, 4)
    g1.arista(5, 4)
    g1.arista(7,4)
    g1.arista(5, 6)
    g1.arista(7, 6)
    return g1


def _n_reinas(n):
    casillero = lambda i, j: str(i + 1) + chr(ord('a') + j)
    g = Grafo()
    for i in range(n):
        for j in range(n):
            g.agregar_vertice(casillero(i, j))

    # Agrego adyacencia por fila
    for i in range(n):
        for j in range(n):
            for k in range(j, n):
                g.arista(casillero(i, j), casillero(i, k))
    # Agrego por columnas
    for j in range(n):
        for i in range(n):
            for k in range(i, n):
                g.arista(casillero(i, j), casillero(k, j))

    # agrego por diagonales
    for i in range(n):
        for j in range(n):
            for k in range(n - max((i, j))):
                g.arista(casillero(i, j), casillero(i + k, j + k))
            for k in range(min(n-i, j)):

                g.arista(casillero(i, j), casillero(i + k, j - k))
    return g


def _fronteras():
    PAISES = ["ARG", "BRA", "URU", "CHI", "PER", "PAR", "BOL", "ECU", "VEN", "COL", "SUR", "GUY", "GUF"]
    g = Grafo(False, PAISES)
    g.arista("ARG", "URU")
    g.arista("ARG", "CHI")
    g.arista("ARG", "BOL")
    g.arista("ARG", "BRA")
    g.arista("ARG", "PAR")
    g.arista("BRA", "URU")
    g.arista("BRA", "PAR")
    g.arista("BRA", "BOL")
    g.arista("BRA", "SUR")
    g.arista("BRA", "GUF")
    g.arista("BRA", "GUY")
    g.arista("BRA", "VEN")
    g.arista("BRA", "COL")
    g.arista("BRA", "PER")
    g.arista("CHI", "BOL")
    g.arista("CHI", "PER")
    g.arista("PAR", "BOL")
    g.arista("PER", "BOL")
    g.arista("ECU", "PER")
    g.arista("ECU", "COL")
    g.arista("COL", "PER")
    g.arista("COL", "VEN")
    g.arista("VEN", "GUY")
    g.arista("SUR", "GUY")
    g.arista("SUR", "GUF")
    return g


def _actores():
    actores_por_pelicula = {}
    actores = set()
    with open("actores_test.csv") as f:
        for l in f:
            splitted = l.strip().split(",")
            actor = splitted[0]
            actores.add(actor)
            peliculas = splitted[1:]
            for peli in peliculas:
                if peli not in actores_por_pelicula:
                    actores_por_pelicula[peli] = []
                actores_por_pelicula[peli].append(actor)

    g = Grafo()
    for peli in actores_por_pelicula:
        if len(actores_por_pelicula[peli]) < 2:
            continue
        for i in range(len(actores_por_pelicula[peli])):
           for j in range(i + 1, len(actores_por_pelicula[peli])):
                if actores_por_pelicula[peli][i] not in g:
                    g.agregar_vertice(actores_por_pelicula[peli][i])
                if actores_por_pelicula[peli][j] not in g:
                    g.agregar_vertice(actores_por_pelicula[peli][j])
                g.arista(actores_por_pelicula[peli][i], actores_por_pelicula[peli][j])
    return g


def _ej_topologico():
    MATERIAS = ["Física I", "Física II", "Física III", "Algoritmos y Programación I", "Algoritmos y Programación II", "Algoritmos y Programación III", "Análisis Matemático II", 'Álgebra II', "Análisis Matemático III", "Probabilidad y Estadística", "Matemática Discreta", "Teoría de Algoritmos I", "Teoría de Algoritmos II", "Química", "Laboratorio", "Estructura del Computador", "Análisis Numérico I", "Organización de Computadoras", "Taller de Programación I", "Organización de Datos", "Taller de Programación II", "Estructura de las Organizaciones", "Modelos y Optimización I", "Sistemas Operativos", "Análisis de la Información", "Técnicas de Diseño", "Base de Datos", "Introducción a los Sistemas Distribuidos"]
    g = Grafo(True, MATERIAS)
    g.arista("Física I", "Física II")
    g.arista("Análisis Matemático II", "Física II")
    g.arista("Algoritmos y Programación I", "Algoritmos y Programación II")
    g.arista("Algoritmos y Programación II", "Algoritmos y Programación III")
    g.arista("Algoritmos y Programación II", "Teoría de Algoritmos I")
    g.arista("Teoría de Algoritmos I", "Teoría de Algoritmos II")
    g.arista("Matemática Discreta", "Teoría de Algoritmos I")
    g.arista("Álgebra II", "Física III")
    g.arista("Física II", "Física III")
    g.arista("Química", "Física III")
    g.arista("Física II", "Laboratorio")
    g.arista("Física II", "Estructura del Computador")
    g.arista("Algoritmos y Programación II", "Estructura del Computador")
    g.arista("Álgebra II", "Estructura del Computador")
    g.arista("Algoritmos y Programación II", "Análisis Numérico I")
    g.arista("Álgebra II", "Análisis Numérico I")
    g.arista("Análisis Matemático II", "Análisis Numérico I")
    g.arista("Álgebra II", "Probabilidad y Estadística")
    g.arista("Análisis Matemático II", "Probabilidad y Estadística")
    g.arista("Álgebra II", "Análisis Matemático III")
    g.arista("Análisis Matemático II", "Análisis Matemático III")
    g.arista("Estructura del Computador", "Organización de Computadoras")
    g.arista("Estructura del Computador", "Organización de Datos")
    g.arista("Algoritmos y Programación II", "Organización de Datos")
    g.arista("Laboratorio", "Organización de Computadoras")
    g.arista("Estructura del Computador", "Taller de Programación I")
    g.arista("Análisis Numérico I", "Taller de Programación I")
    g.arista("Algoritmos y Programación II", "Taller de Programación I")
    g.arista("Organización de Datos", "Estructura de las Organizaciones")
    g.arista("Análisis Matemático III", "Modelos y Optimización I")
    g.arista("Física II", "Modelos y Optimización I")
    g.arista("Química", "Modelos y Optimización I")
    g.arista("Taller de Programación I", "Modelos y Optimización I")
    g.arista("Organización de Datos", "Sistemas Operativos")
    g.arista("Taller de Programación I", "Análisis de la Información")
    g.arista("Algoritmos y Programación III", "Análisis de la Información")
    g.arista("Análisis de la Información", "Técnicas de Diseño")
    g.arista("Sistemas Operativos", "Técnicas de Diseño")
    g.arista("Organización de Datos", "Base de Datos")
    g.arista("Análisis de la Información", "Base de Datos")
    g.arista("Organización de Computadoras", "Introducción a los Sistemas Distribuidos")
    g.arista("Física III", "Introducción a los Sistemas Distribuidos")
    g.arista("Sistemas Operativos", "Introducción a los Sistemas Distribuidos")
    g.arista("Taller de Programación I", "Taller de Programación II")
    g.arista("Modelos y Optimización I", "Taller de Programación II")
    g.arista("Algoritmos y Programación III", "Taller de Programación II")
    return g



ejemplo_bt = _fuerza_bruta()
reinas_lazy = LazyValue(lambda: _n_reinas(12))
fronteras = _fronteras()
actores_lazy = LazyValue(lambda: _actores())
correlativas = _ej_topologico()