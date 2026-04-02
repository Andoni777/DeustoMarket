/*
 * eliminarSupermercado.c
 *
 *  Created on: 2 abr 2026
 *      Author: ander.iglesias.ruiz
 */

#include "eliminarSupermercado.h"
#include <stdio.h>
#include <string.h>

int eliminarSupermercado(sqlite3 *db) {
    sqlite3_stmt *stmt;
    int id;

    printf("\n --- ELIMINAR SUPERMERCADO ---");
    printf("\nIntroduce el ID del supermercado a eliminar: ");
    if (scanf("%d", &id) != 1) {
        printf("Error: entrada no válida.\n");
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');


    char sqlCheck[] = "SELECT ID_SUPER, NOMBRE_SUPER FROM SUPERMERCADO WHERE ID_SUPER = ?";
    int result = sqlite3_prepare_v2(db, sqlCheck, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando consulta: %s\n", sqlite3_errmsg(db));
        return result;
    }
    sqlite3_bind_int(stmt, 1, id);
    result = sqlite3_step(stmt);
    if (result != SQLITE_ROW) {
        printf("No se encontró ningún supermercado con ID %d.\n", id);
        sqlite3_finalize(stmt);
        return -1;
    }
    printf("Supermercado encontrado: %s\n", (char *)sqlite3_column_text(stmt, 1));
    sqlite3_finalize(stmt);


    printf("¿Estás seguro de que quieres eliminarlo? (s/n): ");
    char confirm;
    scanf(" %c", &confirm);
    while (getchar() != '\n');
    if (confirm != 's' && confirm != 'S') {
        printf("Operación cancelada.\n");
        return 0;
    }


    char sqlDelete[] = "DELETE FROM SUPERMERCADO WHERE ID_SUPER = ?";
    result = sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparando DELETE: %s\n", sqlite3_errmsg(db));
        return result;
    }
    sqlite3_bind_int(stmt, 1, id);
    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        printf("Error al eliminar supermercado: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return result;
    }
    sqlite3_finalize(stmt);

    printf("Supermercado con ID %d eliminado correctamente.\n", id);
    return SQLITE_OK;
}
