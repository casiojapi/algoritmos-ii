import random

class Vertice:
    def __init__(self):
        self.adyacentes = {}

class Grafo:
    def __init__(self, es_dirigido = False):
        self.dirigido = es_dirigido
        self.cantidad_vertices = 0
        self.cantidad_aristas = 0
        self.vertices = {}
    
    def agregar_vertice(self, vertice):
        '''
        Agrega el vertice dado por parametro al grafo.
        '''
        if vertice in self.vertices:
            return

        v = Vertice()
        self.vertices[vertice] = v
        self.cantidad_vertices += 1

    def borrar_vertice(self, vertice):
        '''
        Borra un vertice del grafo.
        Pre: recibe un vertice valido
        '''
        if vertice not in self.vertices:
            raise ValueError("no existe el vertice dado")
        del self.vertices[vertice]
        for v in self.vertices:
            del v.adyacentes[vertice]
        self.cantidad_vertices -= 1

    def agregar_arista(self, v1, v2, peso = 1):
        '''
        Agrega un arista al grafo, conectando los 2 vertices dados por parametro
        Pre: recibe 2 vertices validos, pertenecientes al grafo.
        '''
        if v1 not in self.vertices:
            raise ValueError("vertice 1 invalido")
        if v2 not in self.vertices:
            raise ValueError("vertice 2 invalido")
        self.vertices[v1].adyacentes[v2] = peso
        if not self.dirigido:
            self.vertices[v2].adyacentes[v1] = peso
        self.cantidad_aristas += 1

    def borrar_arista(self, v1, v2):
        '''
        Borra la arista que conecta los dos vertices dados por parametro de un grafo.
        Pre: los dos vertices son validos y pertenecen al grafo.
        '''
        if v1 not in self.vertices:
            raise ValueError("vertice 1 invalido")
        if v2 not in self.vertices:
            raise ValueError("vertice 2 invalido")
        del self.vertices[v1].adyacentes[v2]
        if not self.dirigido:
            del self.vertices[v2].adyacentes[v1]
        self.cantidad_aristas -= 1

    def obtener_peso(self, v1, v2):
        '''
        Devuelve el peso entre 2 vertices dados.
        '''
        if v1 not in self.vertices:
            raise ValueError("vertice 1 invalido")
        if v2 not in self.vertices:
            raise ValueError("vertice 2 invalido")
        if v1 in self.vertices[v2].adyacentes:
            return self.vertices[v1].adyacentes[v2]
        else: raise ValueError("los vertices no son adyacentes")

    def vertice_random(self):
        '''
        Devuelve un vertice aleatorio del grafo
        '''
        return random.choice(self.vertices)

    def obtener_vertices(self):
        '''
        Devuelve una lista con todos los vertices, pertenecientes al grafo dado.
        '''
        return self.vertices

    def es_adyacente(self, a, b):
        '''
        Devuelve un booleano, dando true si A y B son adyacentes.
        Pre: ambos vertices deben ser validos, y pertences al grafo dado.
        '''
        for v in self.obtener_adyacentes(a):
            if b == v:
                return True
        return False

    def obtener_adyacentes(self, v):
        '''
        Devuelve una lista con los adyacentes al vertice dado por parametro.
        Pre: el vertice dado debe ser valido y pertenecer al grafo.
        '''
        if v not in self.vertices:
            return None
        return self.vertices[v].adyacentes

    def obtener_cant_adyacentes(self, v):
        '''
        Devuelve la cantidad de adyacentes a un vertice.
        Pre: el vertice dado debe ser valido y pertenecer al grafo.
        '''
        if v not in self.vertices:
            return None
        return len(self.vertices[v].adyacentes)

    def obtener_cantidad_aristas(self):
        '''
        Devuelve la cantidad de aristas del grafo dado.
        '''
        return self.cantidad_aristas

    def obtener_cantidad_vertices(self):
        '''
        Devuelve la cantidad de vertices en el grafo dado.
        '''
        return self.cantidad_vertices
