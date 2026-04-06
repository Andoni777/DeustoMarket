/*
 * anadirEmpleado.c
 *
 *  Created on: 6 abr 2026
 *      Author: mike
 */

#include "anadirEmpleado.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"
#include "../menuGestSupermercado/mostrarListadoSuper.h"

int anadirEmpleado() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	sqlite3_open("BDD/deustomarket.db", &db);
	char buffer[30];
	int result;
	char nombre[30];
	char dni[10];
	char puesto[20];
	int id_super = -1;

	sqlite3_open("BDD/deustomarket.db", &db);

    printf("\n --- DAR DE ALTA NUEVO EMPLEADO ---");

    do {
    	printf("Introduce el NOMBRE del nuevo empleado: ");
        fgets(nombre, 30, stdin);								//pide el nombre del nuevo supermercado
        nombre[strcspn(nombre, "\n")] = 0;

        if (strlen(nombre) == 0) {
        	printf("--> Error: Valor no permitido\n\n");
            }
    } while (strlen(nombre) == 0);

    do {
    	printf("Introduce el DNI del nuevo empleado: ");
        fgets(dni, 9, stdin);								//pide el nombre del nuevo supermercado
        dni[strcspn(dni, "\n")] = 0;

        if (strlen(dni) == 0) {
        	printf("--> Error: Valor no permitido\n\n");
                }
    } while (strlen(dni) == 0);

    do {
    	printf("Introduce el PUESTO del nuevo empleado: ");
        fgets(puesto, 20, stdin);								//pide el nombre del nuevo supermercado
        puesto[strcspn(puesto, "\n")] = 0;

        if (strlen(puesto) == 0) {
        	printf("--> Error: Valor no permitido\n\n");
                    }
    } while (strlen(puesto) == 0);

    do {
    	printf("\n--- Supermercados disponibles ---\n");
    	mostrarListadoSuperId();

        printf("\nIntroduce el SUPERMERCADO asignado al nuevo empleado: ");
        fgets(buffer, sizeof(buffer), stdin);
        if (sscanf(buffer, "%i", &id_super) != 1 || id_super<= 0) {
        	printf("\n--> Error: Valor no permitido\n\n");
        }

    } while (id_super < 0);



    char SQLInsert[] = "INSERT INTO empleado (dni_empleado, nombre_empleado, puesto, id_super) VALUES (?, ?, ?, ?)";
    result = sqlite3_prepare_v2(db, SQLInsert, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, nombre, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, puesto, -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, id_super);

    result = sqlite3_step(stmt);
    if (result == SQLITE_DONE) {
    	printf("\n Empleado '%s' añadido correctamente a la base de datos!", nombre);
    } else {
    	printf("--> Error añadiendo el empleado '%s' a la base de datos: %s", nombre, sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Logear operacion
    FILE *archivo;
    archivo = fopen("Configuracion/logs", "a");

    if (archivo != NULL) {
            fprintf(archivo, "Se añadio el empleado con DNI: %s NOMBRE: %s PUESTO: %s en el super de ID: %d\n", dni, nombre, puesto, id_super);
            fclose(archivo);
        } else {
            printf("\n[Aviso]: No se pudo guardar el registro en el archivo de logs.\n");
        }


    return SQLITE_OK;
}
