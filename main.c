/*
 * main.c
 *
 *  Created on: 26 mar 2026
 *      Author: andoni.g, eneko, miguel y ander
 */
#include <stdio.h>
#include <string.h>
#define MAX_LONGITUD 40
#include "menuAdmin/menuAdmin.h"

int iniciarSesion() {
    char inputUsuario[MAX_LONGITUD];
    char inputContrasena[MAX_LONGITUD];

    char archivoUsuario[MAX_LONGITUD];
    char archivoContrasena[MAX_LONGITUD];

    FILE *archivo;
    int autenticado = 0;


    printf("\n--- LOGIN ---\n");
    printf("Usuario: ");	// admin
    scanf("%39s", inputUsuario);

    printf("Contraseña: "); // 1234
    scanf("%39s", inputContrasena);

    while (getchar() != '\n'); // Para que no salga el menu 2 veces seguidas

    archivo = fopen("Configuracion/credenciales", "r");
    if (archivo == NULL) {
        printf("Error: No se pudo encontrar el archivo de credenciales.\n");
        return 0;
    }


    while (fscanf(archivo, "%39s %39s", archivoUsuario, archivoContrasena) == 2) {
        if (strcmp(inputUsuario, archivoUsuario) == 0 &&
            strcmp(inputContrasena, archivoContrasena) == 0) {

            autenticado = 1;
            break;
        }
    }

    fclose(archivo);

    return autenticado;
}

int main (){
	setvbuf(stdout, NULL, _IONBF, 0); // Para que los printf salgan sin problema
	if (iniciarSesion() == 1) {
	    	menuAdmin();
	    } else {
	        printf("\nError: Usuario o contraseña incorrectos.\n");
	    }

	return 0;
}
