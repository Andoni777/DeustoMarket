/*
 * eliminarEmpleado.c
 *
 *  Created on: 2 abr 2026
 *      Author: ander.iglesias.ruiz
 */


#include "eliminarEmpleado.h"
#include <stdio.h>
#include <string.h>

#define MAX_DNI 20

int eliminarEmpleado(sqlite3 *db) {
    sqlite3_stmt *stmt;
    char dni[MAX_DNI];

    printf("\n --- DAR DE BAJA EMPLEADO ---");
    printf("\nIntroduce el DNI del empleado a dar de baja: ");
    if (fgets(dni, MAX_DNI, stdin) == NULL) {
        printf("Error leyendo el DNI.\n");
        return -1;
    }

    dni[strcspn(dni, "\n")] = '\0';


    char sqlCheck[] = "SELECT DNI_EMPLEADO, NOMBRE_EMPLEADO FROM EMPLEADO WHERE DNI_EMPLEADO = ?";
    int result = sqlite3_prepare_v2(db, sqlCheck, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(db));
        return result;
    }
    sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result != SQLITE_ROW) {
        printf("No se encontró ningún empleado con DNI %s.\n", dni);
        sqlite3_finalize(stmt);
        return -1;
    }
    printf("Empleado encontrado: %s\n", (char *)sqlite3_column_text(stmt, 1));
    sqlite3_finalize(stmt);


    printf("¿Estás seguro de que quieres darlo de baja? (s/n): ");
    char confirm;
    scanf(" %c", &confirm);
    while (getchar() != '\n');
    if (confirm != 's' && confirm != 'S') {
        printf("Operación cancelada.\n");
        return 0;
    }


    char sqlDelete[] = "DELETE FROM EMPLEADO WHERE DNI_EMPLEADO = ?";
    result = sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando DELETE: %s\n", sqlite3_errmsg(db));
        return result;
    }
    sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al dar de baja al empleado: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }
    sqlite3_finalize(stmt);

    printf("Empleado con DNI %s dado de baja correctamente.\n", dni);
    return SQLITE_OK;
}
