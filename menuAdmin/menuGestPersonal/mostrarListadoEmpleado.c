/*
 * mostrarListadoEmpleado.c
 *
 *  Created on: 3 abr 2026
 *      Author: andoni.g
 */
#include "mostrarListadoEmpleado.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

void mostrarListadoEmpleado (){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BDD/deustomarket.db", &db);

	/* --- SELECT --- */
	char sql[] = "select e.nombre_empleado from empleado e";

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

void mostrarListadoEmpleadoSuper() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	char nombre_super[100];

	printf("Introduce el nombre del supermercado: ");
	fflush(stdout);
	fgets(nombre_super, sizeof(nombre_super), stdin);


	nombre_super[strcspn(nombre_super, "\n")] = '\0';

	sqlite3_open("BDD/deustomarket.db", &db);

	/* --- SELECT --- */
	char sql[] = "select e.nombre_empleado from empleado e, supermercado s where s.id_super = e.id_super and s.nombre_super = ?";

	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	sqlite3_bind_text(stmt, 1, nombre_super, -1, SQLITE_TRANSIENT);

	printf("\nEmpleados del supermercado '%s':\n", nombre_super);
	printf("--------------------------------------\n");

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			printf("- %s\n", (char*) sqlite3_column_text(stmt, 0));
		}
	} while (result == SQLITE_ROW);
	printf("\n");

	sqlite3_finalize(stmt);
	/* --- SELECT (fin) --- */

	sqlite3_close(db);
}

void mostrarListadoEmpleadoId (){
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;

	sqlite3_open("BDD/deustomarket.db", &db);

	/* --- SELECT --- */
	char sql[] = "select e.dni_empleado, e.nombre_empleado from empleado e";

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
