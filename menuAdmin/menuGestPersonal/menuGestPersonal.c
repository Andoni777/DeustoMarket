/*
 * menuGestPersonal.c
 *
 *  Created on: 2 abr 2026
 *      Author: mike
 */

#include "menuGestPersonal.h"
#include "eliminarEmpleado.h"
#include "anadirEmpleado.h"
#include "modificarEmpleado.h"

#include "mostrarListadoEmpleado.h"
#include "../menuAdmin.h"
#include "../menuGestSupermercado/mostrarListadoSuper.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 20

char mostrarMenuGestPersonal() {

	printf("\n =========================================");
	printf("\n       DEUSTOMARKET - GESTIÓN DE PERSONAL  ");
	printf("\n =========================================");
	printf("\n 1. Dar de alta nuevo empleado");
	printf("\n 2. Dar de baja (eliminar) empleado");
	printf("\n 3. Modificar datos de empleado");
	printf("\n 4. Mostrar lista de todos los empleados");
	printf("\n 5. Mostrar lista de empleados de un supermercado específico");
	printf("\n 0. Salir al menú principal");
	printf("\n =========================================");
	printf("\n\nIntroduce el número de tu selección: ");

	fflush(stdout);
	char linea[MAX_INPUT];
	fgets(linea, MAX_INPUT, stdin);
	clearIfNeeded(linea, MAX_INPUT);
	return *linea;


}

void menuGestPersonal(){

	char opcion;


	do{
		opcion = mostrarMenuGestPersonal();
		switch (opcion){
			case '1':
				anadirEmpleado();

				break;
			case '2':
				mostrarListadoEmpleadoId();
				fflush(stdout);
				eliminarEmpleado();
				break;

			case '3':
				mostrarListadoEmpleadoId(); // Para que el admin vea los DNIs
				modificarEmpleado();
				break;

			case '4':
				printf("\nMostrando empleados:\n");
				    mostrarListadoEmpleado();

				    printf("--> Pulsa ENTER para volver al menu...");
				    fflush(stdout);

				    getchar();
				    break;

			case '5':
					mostrarListadoSuper();
				    mostrarListadoEmpleadoSuper();

				    printf("--> Pulsa ENTER para volver al menu...");
				    fflush(stdout);

				    getchar();
				    break;



		}
	}while(opcion != '0');

	menuAdmin(); // Vuelve al menu principal
}


