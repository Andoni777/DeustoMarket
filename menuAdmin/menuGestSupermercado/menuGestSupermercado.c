/*
 * menuGestSupermercado.c
 *
 *  Created on: 1 abr 2026
 *      Author: mike
 */

#include "menuGestSupermercado.h"
#include "../menuAdmin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 20



char mostrarMenuGestSuper() {

	printf("\n =================================================");
	printf("\n       DEUSTOMARKET - GESTIÓN DE SUPERMERCADOS     ");
	printf("\n =================================================");
	printf("\n 1. Añadir nuevo supermercado");
	printf("\n 2. Modificar supermercado existente");
	printf("\n 3. Eliminar supermercado");
	printf("\n 4. Mostrar lista de supermercados");
	printf("\n 0. Salir al menú principal");
	printf("\n =================================================");
	printf("\n\nIntroduce el número de tu selección: ");

	fflush(stdout);
	char linea[MAX_INPUT];
	fgets(linea, MAX_INPUT, stdin);
	clearIfNeeded(linea, MAX_INPUT);
	return *linea;


}

void menuGestSupermercado() {

	char opcion;


	do{
		opcion = mostrarMenuGestSuper();
		switch (opcion){
			case '1':
				printf("opcion 1");

				break;
			case '2':
				printf("opcion 2");
				break;

			case '3':
				printf("opcion 3");
				break;

			case '4':
				printf("opcion 4");
				break;

		}
	}while(opcion != '0');
	menuAdmin();
}
