#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE 1
#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// #include "funciones_tp2.h"
#include "pacientes.h"
#include "doctores.h"
#include "strutil.h"
#include "mensajes.h"
#include "comandos.h"

#define COMANDO_PEDIR_TURNO "PEDIR_TURNO"
#define COMANDO_ATENDER "ATENDER_SIGUIENTE"
#define COMANDO_INFORME "INFORME"

void eliminar_fin_linea(char* linea) {
		size_t len = strlen(linea);
		if (linea[len - 1] == '\n') {
				linea[len - 1] = '\0';
		}
}

bool cant_param_validos(char* comando, char** params, size_t cant_param){
		size_t cant = 0;
		for(size_t i = 0; params[i]; i++)
				cant++;
		if (cant == cant_param)
				return true;
		printf(ENOENT_PARAMS, comando);
		return false;
}

void procesar_comando(char* comando, char** params, pacientes_t* pacientes, doctores_t* doctores, especialidades_t* especialidades) {
		if (!strcmp(COMANDO_PEDIR_TURNO, comando)) {
				if (cant_param_validos(comando, params, 3))
					pedir_turno(pacientes, doctores, especialidades, params[0], params[1], params[2]);
		}
		else if (!strcmp(COMANDO_ATENDER, comando)) {
				if (cant_param_validos(comando, params, 1))
						atender_siguiente(doctores, params[0]);
		}
		else if (!strcmp(COMANDO_INFORME, comando)) {
				if (cant_param_validos(comando, params, 2))
						informe_doctores(doctores, params[0], params[1]);
		}
		else {
				printf(ENOENT_CMD, comando);
		}
}

void procesar_entrada(pacientes_t* pacientes, doctores_t* doctores, especialidades_t* especialidades) {
		char* linea = NULL;
		size_t c = 0;
		while (getline(&linea, &c, stdin) > 0) {
				eliminar_fin_linea(linea);
				char** campos = split(linea, ':');
				if (campos[1] == NULL) {
						printf(ENOENT_FORMATO, linea);
						free_strv(campos);
						continue;
				}
				char** parametros = split(campos[1], ',');
				size_t cant_campos = 0;
				for(size_t i = 0; campos[i]; i++)
						cant_campos++;
				if (cant_campos != 2)
						printf(ENOENT_FORMATO, linea);
				else
						procesar_comando(campos[0], parametros, pacientes, doctores, especialidades);
				free_strv(parametros);
				free_strv(campos);
		}
		free(linea);
}

int main(int argc, char** argv) {
		if(argc != 3){
				printf(ENOENT_CANT_PARAMS);
				return 1;
		}

		pacientes_t *pacientes = pacientes_crear(argv[2]);
		if(!pacientes){
				printf(ENOENT_ARCHIVO, argv[2]);
				return 1;
		}

		especialidades_t* especialidades = especialidades_crear();

		doctores_t *doctores = doctores_crear(argv[1], especialidades);
		if(!doctores){
			printf(ENOENT_ARCHIVO, argv[1]);
			return 1;
		}

		procesar_entrada(pacientes, doctores, especialidades);

		especialidades_destruir(especialidades);
		doctores_destruir(doctores);
		pacientes_destruir(pacientes);

		return 0;
}
