#include "modificarEmpleado.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

#define MAX_STR 50

void modificarEmpleado() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char dni[15];
    int opcion;
    char nuevoValor[MAX_STR];
    int nuevoIdSuper;

    if (sqlite3_open("BDD/deustomarket.db", &db) != SQLITE_OK) return;

    printf("\n--- MODIFICAR DATOS DE EMPLEADO ---");
    printf("\nIntroduce el DNI del empleado: ");
    fgets(dni, 15, stdin);
    dni[strcspn(dni, "\n")] = 0;

    printf("\n¿Qué desea modificar?");
    printf("\n1. Nombre");
    printf("\n2. Puesto");
    printf("\n3. ID de Supermercado");
    printf("\nSelección: ");
    scanf("%d", &opcion);
    getchar(); // Limpiar buffer

    const char *sql = NULL;

    if (opcion == 1) {
        sql = "UPDATE empleado SET nombre_empleado = ? WHERE dni_empleado = ?;";
    } else if (opcion == 2) {
        sql = "UPDATE empleado SET puesto = ? WHERE dni_empleado = ?;";
    } else if (opcion == 3) {
        sql = "UPDATE empleado SET id_super = ? WHERE dni_empleado = ?;";
    } else {
        printf("Opción no válida.\n");
        sqlite3_close(db);
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        if (opcion == 1 || opcion == 2) {
            printf("Introduce el nuevo valor: ");
            fgets(nuevoValor, MAX_STR, stdin);
            nuevoValor[strcspn(nuevoValor, "\n")] = 0;

            sqlite3_bind_text(stmt, 1, nuevoValor, -1, SQLITE_TRANSIENT);
            sqlite3_bind_text(stmt, 2, dni, -1, SQLITE_TRANSIENT);
        } else {
            printf("Introduce el nuevo ID de Supermercado: ");
            scanf("%d", &nuevoIdSuper); getchar();

            sqlite3_bind_int(stmt, 1, nuevoIdSuper);
            sqlite3_bind_text(stmt, 2, dni, -1, SQLITE_TRANSIENT);
        }

        if (sqlite3_step(stmt) == SQLITE_DONE && sqlite3_changes(db) > 0) {
            printf("\n[OK] Datos actualizados correctamente.\n");
        } else {
            printf("\n[ERROR] No se encontró el empleado con DNI: %s\n", dni);
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
