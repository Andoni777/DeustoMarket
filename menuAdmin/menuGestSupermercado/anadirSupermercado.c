/*
 * anadirSupermercado.c
 *
 *  Created on: 5 abr 2026
 *      Author: mike
 */

#include "anadirSupermercado.h"
#include <stdio.h>
#include <string.h>-
#include "../../BDD/sqlite3.h"

int anadirSupermercado() {
	sqlite3 *db;
    sqlite3_stmt *stmt;
	sqlite3_open("BDD/deustomarket.db", &db);
    int result;

    char nombre[30];
    char direccion[50];



	sqlite3_open("BDD/deustomarket.db", &db);

    printf("\n --- AÑADIR NUEVO SUPERMERCADO ---");

    do {
            printf("Introduce el NOMBRE del nuevo supermercado: ");
            fgets(nombre, 30, stdin);								//pide el nombre del nuevo supermercado
            nombre[strcspn(nombre, "\n")] = 0;

            if (strlen(nombre) == 0) {
                printf("--> Error: Valor no permitido\n\n");
            }
        } while (strlen(nombre) == 0);								//en caso de recibir un char vacio, vuelve a pedir los datos

    do {
    	printf("\nIntroduce la DIRECCIÓN del nuevo supermercado: ");
    	fgets(direccion, 50, stdin);								//pide la direccion del nuevo supermercado
    	direccion[strcspn(direccion, "\n")] = 0;

    		if (strlen(nombre) == 0) {
    	        printf("--> Error: Valor no permitido\n\n");
    	    }
    	} while (strlen(nombre) == 0);								//en caso de recibir un char vacio, vuelve a pedir los datos

    char SQLInsert[] = "INSERT INTO supermercado (nombre_super, direccion) VALUES (?, ?)";

    result = sqlite3_prepare_v2(db, SQLInsert, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, direccion, -1, SQLITE_TRANSIENT);

    result = sqlite3_step(stmt);
    if (result == SQLITE_DONE) {
		printf("\n Supermercado '%s' añadido correctamente a la base de datos!", nombre);
	} else {
		printf("Error añadiendo el supermercado '%s' a la base de datos: %s", nombre, sqlite3_errmsg(db));
	}

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return SQLITE_OK;

}
