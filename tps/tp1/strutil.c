#include "strutil.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_IND 100000

size_t obtener_memoria_y_strs(size_t* lens, char** strv, size_t* strs);

char *substr(const char *str, size_t n) {
    char* c = strndup(str, n);
    return c ? c : NULL;
}

char **split(const char *str, char sep) {
    if (!str)
        return NULL;
    size_t n = strlen(str);
    size_t cadenas = 0;
    char** cc = NULL;
    size_t indices[MAX_IND];
    indices[0] = 0;
    for (size_t i = 0; i < n; i++) {
        if (str[i] == sep) {
            cadenas++;
            indices[cadenas] = i + 1;
        }
    }
    indices[++cadenas] = n + 1;
    cc = malloc(sizeof(char*) * (cadenas + 1));
    if (!cc) return NULL;

    for (size_t i = 0; i < cadenas; i++) {
        cc[i] = substr(str + indices[i], indices[i + 1] - indices[i] - 1);
    }
    cc[cadenas] = NULL;
    return cc;
}

char *join(char **strv, char sep) {
    size_t strs = 0, mem = 0;
    if (!strv) return strdup("");

    char no_null = 1;
    if (sep == '\0')
        no_null = 0;

    size_t* lens = calloc(MAX_IND, sizeof(size_t));
    if (!lens) return NULL;

    mem = obtener_memoria_y_strs(lens, strv, &strs);
    if (!mem) {
        free(lens);
        return strdup("");
    }
    
    char* c = calloc(mem, sizeof(char));
    if (!c) {
        free(lens);
        return NULL;
    }
    size_t index = 0;
    for (size_t i = 0; i < strs; i++) {
        strncpy(c + index, strv[i], lens[i]);
        index += lens[i] - 1;
        if (no_null)
            strncpy(c + index++, &sep, 1);
    }
    c[index - no_null] = '\0';
    free(lens);
    return c;
}

void free_strv(char *strv[]) {
    for (size_t i = 0; strv[i]; i++)
        free(strv[i]);
    free(strv);
}

size_t obtener_memoria_y_strs(size_t* lens, char** strv, size_t* strs) {
    size_t mem = 0;
    for (size_t i = 0; strv[i]; i++) {
        lens[*strs] = strlen(strv[i]) + 1;
        mem += lens[(*strs)++];
    }
    return mem;
}
/*
int main(void) {
    char** strv = split("aaa, sss, aaa, sd, ,s, s,a,aaaa,a,,a,a,aaaa,a", ',');
    for (size_t i = 0; i < 14; i++)
        printf("%s\n", strv[i]);
    char* joineado = join(strv, '+');
        printf("%s\n", joineado);
    free_strv(strv);
    free(joineado);
    return 0;
}*/