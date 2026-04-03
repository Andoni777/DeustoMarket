/*
 * mostrarListadoSuper.c
 *
 *  Created on: 3 abr 2026
 *      Author: andoni.g
 */
#include "mostrarListadoSuper.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

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
