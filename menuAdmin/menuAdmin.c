/*
 * menu.c
 *
 *  Created on: 31 mar 2026
 *      Author: andoni.g
 */
#include "menuAdmin.h"
#include "menuGestSupermercado/menuGestSupermercado.h"
#include "menuGestIyP/menuGestIyP.h"

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



void menuAdmin (){

	char opcion;


	do{
		opcion = mostrarMenu();
		switch (opcion){
			case '1':
				printf("opcion 1");
				menuGestSupermercado();
				break;
			case '2':
				printf("opcion 2");
				menuGestIyP();
				break;

			case '3':
				printf("opcion 3");
				break;

			case '4':
				printf("opcion 4");
				break;

		}
	}while(opcion != '0');

	exit (0); // El programa ha finalizado correctamente
}

