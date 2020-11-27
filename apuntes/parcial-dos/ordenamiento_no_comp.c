// Ordenamientos no comp *(necesitamos informacion adicional (( precondicion fuerte )) )*

// algo menos de O(log n)

// Counting sort - > ordena datos enumarables, discretos ( en un rando acotado y conocido (o facilmente obtenible))
// ES ESTABLE
// in-place? ordena en el mismo arreglo? NO. NO ES IN-PLACE
// COMPLEJIDAD -> O(n) + O(k) + O(n) = O(n + k) con k siendo el rango de opciones, siendo constante y despreciable. 

// ejemplo -> ordenar un arreglo con numeros del 0 al 9. Usamos un contador y despues ponemos cada en un nuevo vector siguiendo el vector. 

// Proceso
/*

paso 1 -> contar frecuencias. 
paso 2 -> arreglo de sumas acumuladas.
paso 3 -> posicionar las cartas. 

*/


// RADIX SORT

// Radix sort -> trabaja con elementos que tengan varios digitos o componentes. 
// utiliza un ordenamiento auxiliar que debe ser estable. Idealmente lineal. 
// cada elemento tiene que tener la misma cantidad o digitos o componentes ( o al menos muy similar)
// Ordena de la cifra menos significativa a la mas significativa

// ES ESTABLE
// Complejidad -> O(L(n+k))
// (n + k) seria el algoritmo de ordenamiento que se usa adentro de Radix. En este caso counting sort (o sea O(n+k))
// L siendo la cantidad de digitos (o componentes a tener en cuenta al ordenar)

// Proceso
/*

// paso 1 ordena segun la cifra menos significativa (ordena segun la tercer cifra usando nomeros de 3 digitos)
// paso 2 ordena segun la siguiente cifra menos significativa. 
// paso 3 ordena segun la ultima cifra. 

// MUY IMPORTANTE EN EL INTERMEDIO DE CADA PASO QUE SE USE EL ORDENAMIENTO ESTABLE. PORQUE SI SE MUERE TODO.
*/


// Bucket sort
// ES ESTABLE
// Puede no tener un range enumarable 
// debe ser conocida la distribucion de los datos
// debe ser uniforme la distribucion tambien. 
// util si no podemos usar los otros dos metodos. (como por ejemplo con numeros decimales)

// complejidad -> O(n) + O(n+b) = O(n + b), b siendo la cantidad de baldes. 
// Proceso
/*

separar por baldes.

ordenar cada balde con otro ordenamiento x.

vamos balde por balde juntando los resultados.

*/
