/*
 * menuGestIyP.c
 *
 *  Created on: 1 abr 2026
 *      Author: mike
 */


#include "menuGestIyP.h"
#include "../menuAdmin.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 20

char mostrarMenuGestIyP() {

	printf("\n =====================================================");
	printf("\n       DEUSTOMARKET - GESTIÓN DE INVENTARIO/PRODUCTOS ");
	printf("\n =====================================================");
	printf("\n 1. Añadir nuevo producto al catálogo");
	printf("\n 2. Eliminar producto");
	printf("\n 3. Modificar precio de producto");
	printf("\n 4. Actualizar stock de un supermercado");
	printf("\n 0. Salir al menú principal");
	printf("\n =====================================================");
	printf("\n\nIntroduce el número de tu selección: ");

	fflush(stdout);
	char linea[MAX_INPUT];
	fgets(linea, MAX_INPUT, stdin);
	clearIfNeeded(linea, MAX_INPUT);
	return *linea;


}

void menuGestIyP() {

	char opcion;


	do{
		opcion = mostrarMenuGestIyP();
		switch (opcion){
			case '1':
				printf("opcion 1");

				break;
			case '2':
				eliminarProducto();
				break;

			case '3':
				printf("opcion 3");
				break;

			case '4':
				printf("opcion 4");
				break;

		}
	}while(opcion != '0');

	menuAdmin(); // Vuelve al menu principal
}

