/*
 * menu.c
 *
 *  Created on: 31 mar 2026
 *      Author: andoni.g
 */
#include "menuAdmin.h"
#include "menuGestSupermercado/menuGestSupermercado.h"
#include "menuGestIyP/menuGestIyP.h"
#include "menuGestPersonal/menuGestPersonal.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 20
void clearIfNeeded(char *str, int max_line) {
	// Limpia los caracteres de m�s introducidos
	if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n'))
		while (getchar() != '\n');
}

char mostrarMenu () {
	printf ("\n ==========================================");
	printf ("\n       DEUSTOMARKET - PANEL DE CONTROL     ");
	printf ("\n ==========================================");
	printf ("\n1. Gestión de Supermercados");
	printf ("\n2. Gestión de Inventario y Productos");
	printf ("\n3. Gestión de Empleados");
	printf ("\n4. Ver Logs del Sistema");
	printf ("\n0. Salir");
	printf("\n\nIntroduce el numero de tu selección: ");

	fflush(stdout);
	char linea[MAX_INPUT];
	fgets(linea, MAX_INPUT, stdin);
	clearIfNeeded(linea, MAX_INPUT);
	return *linea;

}

void mostrarLogs(){
	FILE *archivo;
	char linea[200];

	printf("\n ==========================================");
	printf("\n          LOGS DEL SISTEMA                 ");
	printf("\n ==========================================\n\n");

	archivo = fopen("Configuracion/logs", "r");

	if (archivo == NULL) {
        printf("Todavía no hay ninguna operación registrada en los logs.\n");
        printf("\n ==========================================\n");
        return;
    }

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }

		printf("\n ==========================================\n");
	    fclose(archivo);
	}



void menuAdmin (){

	char opcion;

	do{
		opcion = mostrarMenu();
		switch (opcion){
			case '1':
				menuGestSupermercado();
				break;
			case '2':
				menuGestIyP();
				break;

			case '3':
				menuGestPersonal();
				break;

			case '4':
				printf("\nMostrando acciones registradas:\n");
				    mostrarLogs();

				    printf("--> Pulsa ENTER para volver al menu...");
				    fflush(stdout);

				    getchar();
				    break;

		}
	}while(opcion != '0');

	exit (0); // El programa ha finalizado correctamente
}

