#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

    // EQUIVALENTES

    char cadena[] = {'h', 'o', 'l', 'a', '\n', '\0'};  

    char cadena_dos[] = "hole\n";

    char *cadena_tres = "holi\n";

    char cadena_cuatro[6];

    cadena_cuatro[0] = 'h';
    cadena_cuatro[1] = 'o';
    cadena_cuatro[2] = 'l';
    cadena_cuatro[3] = 'o';
    cadena_cuatro[4] = '\n';
    cadena_cuatro[5] = '\0';

    char *cadena_cinco = malloc(sizeof(char) * 6);

    cadena_cinco[0] = 'h';
    cadena_cinco[1] = 'o';
    cadena_cinco[2] = 'l';
    cadena_cinco[3] = 'u';
    cadena_cinco[4] = '\n';
    cadena_cinco[5] = '\0';

    printf("%s%s%s%s%s", cadena, cadena_dos, cadena_tres, cadena_cuatro, cadena_cinco);

    free(cadena_cinco);

    return 0;
}