/*
 * mostrarInventario.c
 *
 *  Created on: 3 abr 2026
 *      Author: andoni.g
 */
#include "mostrarInventario.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

void mostrarInventario() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char supermercado_actual[100] = "";
	const char *supermercado_fila;

	sqlite3_open("BDD/deustomarket.db", &db);

	/* --- SELECT --- */
	char sql[] = "select s.nombre_super, p.nombre_producto, i.stock from producto p, supermercado s, inventario i "
			"where p.id_producto = i.id_producto and s.id_super = i.id_super";

	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	do {
	result = sqlite3_step(stmt);
			if (result == SQLITE_ROW) {
				supermercado_fila = (const char*) sqlite3_column_text(stmt, 0);
				if (strcmp(supermercado_actual, supermercado_fila) != 0) {
					printf("\n=== Supermercado: %s ===\n", supermercado_fila);
					strcpy(supermercado_actual, supermercado_fila);
				}


				printf("    - %s (Stock: %i)\n",
				sqlite3_column_text(stmt, 1),
				sqlite3_column_int(stmt, 2));
			}
	} while (result == SQLITE_ROW);
	printf("\n");

	sqlite3_finalize(stmt);
	/* --- SELECT (fin) --- */

	sqlite3_close(db);

	// Logear operacion
	FILE *archivo;
	archivo = fopen("Configuracion/logs", "a");

	if (archivo != NULL) {
		fprintf(archivo, "Se consulto el inventario de los supermercados\n");
		fclose(archivo);
	} else {
	    printf("\n[Aviso]: No se pudo guardar el registro en el archivo de logs.\n");
      }

}

void mostrarProductoId (){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BDD/deustomarket.db", &db);

	/* --- SELECT --- */
	char sql[] = "select p.id_producto, p.nombre_producto from producto p";

	sqlite3_prepare_v2(db, sql, strlen(sql), &stmt, NULL) ;

	printf("\n");
	do {
		result = sqlite3_step(stmt) ;
		if (result == SQLITE_ROW) {
			printf("%s %s\n",  (char*) sqlite3_column_text(stmt, 0), (char*) sqlite3_column_text(stmt, 1));
		}
	} while (result == SQLITE_ROW);
	printf("\n");

	sqlite3_finalize(stmt);

	/* --- SELECT (fin) --- */

	sqlite3_close(db);

}

