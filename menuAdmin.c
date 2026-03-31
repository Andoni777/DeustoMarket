/*
 * menu.c
 *
 *  Created on: 31 mar 2026
 *      Author: andoni.g
 */
#include "menuAdmin.h"

#include <stdio.h>
#include <stdlib.h>

void mostrarMenu (){
	printf ("\n ==========================================");
	printf ("\n       DEUSTOMARKET - PANEL DE CONTROL     ");
	printf ("\n ==========================================");
	printf ("\n1. Gestión de Supermercados");
	printf ("\n2. Gestión de Inventario y Productos");
	printf ("\n3. Gestión de Empleados");
	printf ("\n4. Ver Logs del Sistema");
	printf ("\n0. Salir");

	char linea[100];
	int opcion;

	printf("\nIntroduce el numero de tu selección: ");
	fgets(linea, sizeof(linea), stdin);

	 if (sscanf(linea, "%d", &opcion) == 1) {

		 switch (opcion){
			case 1:
				//gestionarSuper();
				break;
			case 2:
				//gestionarInvProd();
				break;
			case 3:
				//gestionarEmpleado();
				break;
			case 4:
				//verLogs();
				break;
			case 0:
				printf("Cerrando el programa . . .");
				break;
			default:
				printf ("Seleccione una opcion valida por favor");
				mostrarMenu();
		};

	   } else {
		   printf("\nError: no es un numero valido\n");
	   }





}

