/*
 * menuGestSupermercado.c
 *
 *  Created on: 1 abr 2026
 *      Author: mike
 */

#include "menuGestSupermercado.h"
#include "../menuAdmin.h"
#include "../../BDD/sqlite3.h"

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

void mostrarListadoSuper (){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BDD/deustomarket.db", &db);

	/* --- SELECT --- */
	char sql[] = "select s.nombre_super from supermercado s";

	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL) ;

	printf("\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			printf("%s\n", (char*) sqlite3_column_text(stmt, 0));
		}
	} while (result == SQLITE_ROW);
	printf("\n");

	sqlite3_finalize(stmt);

	/* --- SELECT (fin) --- */

	sqlite3_close(db);

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
				printf("\nMostrando supermercados:\n");
				    mostrarListadoSuper();

				    printf("--> Pulsa ENTER para volver al menu...");
				    fflush(stdout);

				    getchar();
				    break;

		}
	}while(opcion != '0');
	menuAdmin(); // Vuelve al menu principal
}


