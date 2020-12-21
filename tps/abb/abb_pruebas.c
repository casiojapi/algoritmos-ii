#include "abb.h"
#include "testing.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void prueba_crear_abb_vacio(void){
    printf("\nINICIO PRUEBAS ABB VACIO:\n");
    abb_t *abb = abb_crear(strcmp, NULL);

    print_test("El abb se creó correctamente", abb);
    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("Obtener clave 'clave' devuelve NULL", !abb_obtener(abb, "clave"));
    print_test("abb_pertenece de una clave que no existe devuelve false", !abb_pertenece(abb, "clave"));
    print_test("Borrar una clave que no existe devuelve NULL", !abb_borrar(abb, "clave"));

    abb_destruir(abb);
}

static void prueba_abb_guardar(void){
    printf("\nINICIO PRUEBAS ABB GUARDAR:\n");

    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "clave1", *valor1 = "valor1";
    char *clave2 = "clave2", *valor2 = "valor2";
    char *clave3 = "clave3", *valor3 = "valor3";

    print_test("Guardar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener con clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));
    print_test("Borrar clave1 devuelve valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Cantidad de elementos es 0", abb_cantidad(abb) == 0);

    print_test("Guardar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener con clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Pertenece con clave2 es true", abb_pertenece(abb, clave2));

    print_test("Guardar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener con clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));

    print_test("Guardar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Obtener con clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Pertenece con clave3 es true", abb_pertenece(abb, clave3));

    abb_destruir(abb);
}

static void prueba_abb_borrar(void){
    printf("\nINICIO PRUEBAS ABB BORRAR:\n");

    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "clave1", *valor1 = "valor1";
    char *clave2 = "clave2", *valor2 = "valor2";
    char *clave3 = "clave3", *valor3 = "valor3";

    print_test("Guardar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener con clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Pertenece con clave2 es true", abb_pertenece(abb, clave2));

    print_test("Guardar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener con clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));

    print_test("Guardar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Obtener con clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Pertenece con clave3 es true", abb_pertenece(abb, clave3));

    print_test("Borrar clave2 (2 HIJOS) devuelve valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Pertenece con clave2 es false", !abb_pertenece(abb, clave2));
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));
    print_test("Pertenece con clave3 es true", abb_pertenece(abb, clave3));

    print_test("Borrar clave3 (1 HIJO) devuelve valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Pertenece con clave3 es false", !abb_pertenece(abb, clave3));
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));

    print_test("Borrar clave1 (SIN HIJOS) devuelve valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Pertenece con clave1 es false", !abb_pertenece(abb, clave1));
    print_test("Cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_borrar_drestruir(void){
    printf("\nINICIO PRUEBAS ABB BORRAR CON DESTRUIR_DATO = FREE:\n");

    abb_t *abb = abb_crear(strcmp, free);

    char *clave1 = "clave1", *valor1;
    char *clave2 = "clave2", *valor2;
    char *clave3 = "clave3", *valor3;

    valor1 = malloc(10 * sizeof(char));
    valor2 = malloc(10 * sizeof(char));
    valor3 = malloc(10 * sizeof(char));

    print_test("Guardar clave2", abb_guardar(abb, clave2, valor2));
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener con clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Pertenece con clave2 es true", abb_pertenece(abb, clave2));

    print_test("Guardar clave1", abb_guardar(abb, clave1, valor1));
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Obtener con clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));

    print_test("Guardar clave3", abb_guardar(abb, clave3, valor3));
    print_test("Cantidad de elementos es 3", abb_cantidad(abb) == 3);
    print_test("Obtener con clave3 es valor3", abb_obtener(abb, clave3) == valor3);
    print_test("Pertenece con clave3 es true", abb_pertenece(abb, clave3));

    print_test("Borrar clave2 (2 HIJOS) devuelve valor2", abb_borrar(abb, clave2) == valor2);
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);
    print_test("Pertenece con clave2 es false", !abb_pertenece(abb, clave2));
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));
    print_test("Pertenece con clave3 es true", abb_pertenece(abb, clave3));

    print_test("Borrar clave3 (1 HIJO) devuelve valor3", abb_borrar(abb, clave3) == valor3);
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Pertenece con clave3 es false", !abb_pertenece(abb, clave3));
    print_test("Pertenece con clave1 es true", abb_pertenece(abb, clave1));

    print_test("Borrar clave1 (SIN HIJOS) devuelve valor1", abb_borrar(abb, clave1) == valor1);
    print_test("Pertenece con clave1 es false", !abb_pertenece(abb, clave1));
    print_test("Cantidad de elementos es 0", abb_cantidad(abb) == 0);

    //abb_borrar no deberia destruir el dato, solo devolverlo.
    free(valor1);
    free(valor2);
    free(valor3);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar(void){
    printf("\nINICIO PRUEBAS ABB REEMPLAZAR DATO:\n");

    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave1 = "clave1", *valor1 = "valor1", *valor1b = "valor1b";
    char *clave2 = "clave2", *valor2 = "valor2", *valor2b = "valor2b";

    print_test("Guardar clave1 con valor1", abb_guardar(abb, clave1, valor1));
    print_test("Obtener con clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Guardar clave2 con valor2", abb_guardar(abb, clave2, valor2));
    print_test("Obtener con clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Guardar clave1 con valor1b", abb_guardar(abb, clave1, valor1b));
    print_test("Obtener con clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Guardar clave2 con valor2b", abb_guardar(abb, clave2, valor2b));
    print_test("Obtener con clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_reemplazar_destruir(void){
    printf("\nINICIO PRUEBAS ABB REEMPLAZAR DATO CON DESTRUIR_DATO = FREE:\n");

    abb_t *abb = abb_crear(strcmp, free);

    char *clave1 = "clave1", *valor1, *valor1b;
    char *clave2 = "clave2", *valor2, *valor2b;

    valor1 = malloc(10 * sizeof(char));
    valor1b = malloc(10 * sizeof(char));
    valor2 = malloc(10 * sizeof(char));
    valor2b = malloc(10 * sizeof(char));

    print_test("Guardar clave1 con valor1", abb_guardar(abb, clave1, valor1));
    print_test("Obtener con clave1 es valor1", abb_obtener(abb, clave1) == valor1);
    print_test("Guardar clave2 con valor2", abb_guardar(abb, clave2, valor2));
    print_test("Obtener con clave2 es valor2", abb_obtener(abb, clave2) == valor2);
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);

    print_test("Guardar clave1 con valor1b", abb_guardar(abb, clave1, valor1b));
    print_test("Obtener con clave1 es valor1b", abb_obtener(abb, clave1) == valor1b);
    print_test("Guardar clave2 con valor2b", abb_guardar(abb, clave2, valor2b));
    print_test("Obtener con clave2 es valor2b", abb_obtener(abb, clave2) == valor2b);
    print_test("Cantidad de elementos es 2", abb_cantidad(abb) == 2);

    abb_destruir(abb);
}

static void prueba_abb_clave_vacia(void){
    printf("\nINICIO PRUEBAS ABB CLAVE VACIA:\n");

    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = "";

    print_test("Guardar clave vacia", abb_guardar(abb, clave, valor));
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener con clave vacia es valor", abb_obtener(abb, clave) == valor);
    print_test("Pertenece con clave vacia es true", abb_pertenece(abb, clave));
    print_test("Borrar clave vacia devuelve valor", abb_borrar(abb, clave) == valor);
    print_test("Cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

static void prueba_abb_valor_NULL(void){
    printf("\nINICIO PRUEBAS ABB CLAVE VACIA CON VALOR NULL:\n");

    abb_t *abb = abb_crear(strcmp, NULL);

    char *clave = "", *valor = NULL;

    print_test("Guardar clave vacia con valor NULL", abb_guardar(abb, clave, valor));
    print_test("Cantidad de elementos es 1", abb_cantidad(abb) == 1);
    print_test("Obtener con clave vacia es valor NULL", abb_obtener(abb, clave) == valor);
    print_test("Pertenece con clave vacia es true", abb_pertenece(abb, clave));
    print_test("Borrar clave vacia devuelve valor NULL", abb_borrar(abb, clave) == valor);
    print_test("Cantidad de elementos es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}



static void prueba_abb_volumen(size_t largo)
{
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", rand() / 10);
        *valores[i] = rand();
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    print_test("Prueba abb almacenar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb pertenece y obtener muchos elementos", ok);
    print_test("Prueba abb elementos es correcta", abb_cantidad(abb) == largo);

    /* Verifica que borre y devuelva los valores correctos */
    for (size_t i = 0; i < largo; i++) {
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    print_test("Prueba abb borrar muchos elementos", ok);
    print_test("Prueba abb la cantidad de elementos es 0", abb_cantidad(abb) == 0);

    /* Destruye el abb y crea uno nuevo que sí libera */
    abb_destruir(abb);
    abb = abb_crear(strcmp, free);

    /* Inserta 'largo' parejas en el abb */
    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    free(claves);
    abb_destruir(abb);

}

//Función visitar para el iterador interno
static bool visitar(const char *clave, void *dato, void *contador){
    if(strcmp(clave, "H") == 0){
        printf("-CORTE-");
        return false;
    }
    *(size_t*)contador += 1;
    printf("%s", clave);
    return true;
}

static void prueba_abb_iter_interno_sin_corte(void){
    printf("\nINICIO PRUEBAS ABB ITER INTERNO IN ORDER SIN CORTE:\n");

    abb_t *abb = abb_crear(strcmp, NULL);
    char *claves = "MGRDIQXOBCA";
    size_t valores[strlen(claves)];

    bool ok = true;
    for(size_t i = 0; i < strlen(claves); i++){
        valores[i] = i;
        char clave[2] = {claves[i], '\0'};
        ok &= abb_guardar(abb, clave, &valores[i]);
        ok &= (abb_obtener(abb, clave) == &valores[i]);
    }
    print_test("Se guardaron las claves correctamente", ok);
    print_test("Cantidad de elementos es 11", abb_cantidad(abb) == 11);

    size_t contador = 0;
    printf("Claves en orden de inserción: %s\n", claves);
    printf("Claves in order: ");
    abb_in_order(abb, visitar, &contador);
    printf("\n");

    print_test("Contador igual a cantidad de elementos es 11", contador == 11);

    abb_destruir(abb);
}

static void prueba_abb_iter_interno_con_corte(void){
    printf("\nINICIO PRUEBAS ABB ITER INTERNO IN ORDER CON CORTE:\n");

    abb_t *abb = abb_crear(strcmp, NULL);
    char *claves = "MHRDIQXOBCA";
    size_t valores[strlen(claves)];

    bool ok = true;
    for(size_t i = 0; i < strlen(claves); i++){
        valores[i] = i;
        char clave[2] = {claves[i], '\0'};
        ok &= abb_guardar(abb, clave, &valores[i]);
        ok &= (abb_obtener(abb, clave) == &valores[i]);
    }
    print_test("Se guardaron las claves correctamente", ok);
    print_test("Cantidad de elementos es 11", abb_cantidad(abb) == 11);

    size_t contador = 0;
    printf("Claves en orden de inserción: %s\n", claves);
    printf("Claves in order(hasta corte en H): ");
    abb_in_order(abb, visitar, &contador);
    printf("\n");

    print_test("Contador igual a 4", contador == 4);

    abb_destruir(abb);
}

static void prueba_abb_iter_externo_abb_vacio(void){
    printf("\nINICIO PRUEBAS ITERADOR EXTERNO CON ABB VACIO:\n");
    abb_t *abb = abb_crear(strcmp, NULL);
    abb_iter_t* iter = abb_iter_in_crear(abb);

    print_test("La cantidad de elementos es 0", abb_cantidad(abb) == 0);
    print_test("El iter se creó correctamente", iter);
    print_test("Iter esta al final es true", abb_iter_in_al_final(iter));
    print_test("Iter avanzar es false", !abb_iter_in_avanzar(iter));
    print_test("Iter ver actual es NULL", !abb_iter_in_ver_actual(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


static void prueba_abb_iter_externo(void){
    printf("\nINICIO PRUEBAS ITERADOR EXTERNO (INORDER):\n");
    abb_t *abb = abb_crear(strcmp, NULL);

    char *claves[] = {"clave1", "clave2", "clave3"};
    char *valores[] = {"valor1", "valor2", "valor3"};

    print_test("Guardar clave2", abb_guardar(abb, claves[1], valores[1]));
    print_test("Guardar clave1", abb_guardar(abb, claves[0], valores[0]));
    print_test("Guardar clave3", abb_guardar(abb, claves[2], valores[2]));

    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("El iter se creó correctamente", iter);

    print_test("Iter esta al final es false", !abb_iter_in_al_final(iter));
    printf("Clave: %s\n", abb_iter_in_ver_actual(iter));
    print_test("Iter ver actual es clave2 (raiz)", strcmp(abb_iter_in_ver_actual(iter), claves[0]) == 0);

    print_test("Iter esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter));
    printf("Clave: %s\n", abb_iter_in_ver_actual(iter));
    print_test("Iter ver actual es clave1 (hijo izq)", strcmp(abb_iter_in_ver_actual(iter), claves[1]) == 0);

    print_test("Iter esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter));
    printf("Clave: %s\n", abb_iter_in_ver_actual(iter));
    print_test("Iter ver actual es clave3 (hijo der)", strcmp(abb_iter_in_ver_actual(iter), claves[2]) == 0);

    print_test("Iter esta al final es false", !abb_iter_in_al_final(iter));
    print_test("Iter avanzar es true", abb_iter_in_avanzar(iter));
    print_test("Iter esta al final es true", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

static void prueba_abb_iter_externo_volumen(size_t largo) {
    abb_t* abb = abb_crear(strcmp, NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", rand()/10);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Prueba abb iterador esta al final, es false", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Prueba abb iteración en volumen", ok);
    print_test("Prueba abb iteración en volumen, recorrio todo el largo", i == largo);
    print_test("Prueba abb iterador esta al final, es true", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
        // printf("%d) %zd == %zd\t%s\n", i, valores[i], largo, ok ? "" : "###################");
        // ok = true;
    }
    print_test("Prueba abb iteración en volumen, se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}

void pruebas_abb_estudiante(void){
    //Pruebas primitivas del ABB

    prueba_crear_abb_vacio();
    prueba_abb_guardar();
    prueba_abb_borrar();
    prueba_abb_borrar_drestruir();
    prueba_abb_reemplazar();
    prueba_abb_reemplazar_destruir();
    prueba_abb_clave_vacia();
    prueba_abb_valor_NULL();

    prueba_abb_volumen(10000);

    //Pruebas iterador interno del ABB

    prueba_abb_iter_interno_sin_corte();
    prueba_abb_iter_interno_con_corte();

    //Pruebas iterador externo del ABB

    prueba_abb_iter_externo_abb_vacio();
    prueba_abb_iter_externo();
    prueba_abb_iter_externo_volumen(10000);
}

#ifndef CORRECTOR  // Para que no dé conflicto con el main() del corrector.

int main(void) {
    pruebas_abb_estudiante();
    return failure_count() > 0;  // Indica si falló alguna prueba.
}

#endif
