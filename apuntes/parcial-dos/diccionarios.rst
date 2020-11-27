Diccionarios

clave -> valor

guardar, borrar, pertenece, obtener.


con una funcion de Hash, agarra una cadena y la transforma en un numero. 

Funcion de hashing tiene
+ deterministica 
+ distribuir uniformemente 

(hacerla pija - operadores de bits y mierdas)
(entender el trasfondo matematico)

(algunas funciones de hashing chidas)[http://www.cse.yorku.ca/~oz/hash.html]

HASH CERRADO - tabla finita

cuando una funcion de hash te devuelve un valor antes asignado, existe una colision, y hay que tener eso cubierto.

para guardar en la tabla, necesitamos 3 estados - enum estado = {VACIO, OCUPADO, BORRADO};

factor de carga = n (asignados) / M (tamagno de tabla)
redimensionar cuando llega a aprox = 0.710

en la redimension, directamente se crea una table de M * 2 elementos, y vuelvo a asignar todo. O sea, o(n) asignando cada cadena de nuevo a un nuevo posicion en la tabla de hash.

HASH ABIERTO - tabla infinita - (implementada con lista enlazada)
