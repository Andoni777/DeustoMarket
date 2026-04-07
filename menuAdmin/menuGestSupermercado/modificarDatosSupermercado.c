#include "modificarDatosSupermercado.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

#define MAX_STR 50

void modificarDatosSupermercado() {
    sqlite3 *db;

    // 1. Abrimos la base de datos (OJO: en tu imagen el archivo es 'deustomarket.db' en minúsculas)
    int rc = sqlite3_open("BDD/deustomarket.db", &db);

    if (rc != SQLITE_OK) {
        printf("No se pudo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    int idSuper, opcion;
    char nuevoValor[MAX_STR];
    sqlite3_stmt *stmt;
    const char *sql = NULL; // Usamos const char* para evitar warnings

    printf("\n--- MODIFICAR DATOS DE SUPERMERCADO ---\n");
    printf("Introduce el ID (id_super) del supermercado: ");
    scanf("%d", &idSuper);
    getchar();

    printf("\n¿Qué desea modificar?");
    printf("\n1. Nombre (nombre_super)");
    printf("\n2. Dirección (direccion)");
    printf("\nSelección: ");
    scanf("%d", &opcion);
    getchar();

    printf("Introduce el nuevo valor: ");
    fgets(nuevoValor, MAX_STR, stdin);
    nuevoValor[strcspn(nuevoValor, "\n")] = 0;

    // 2. SQL ajustado a tus imágenes: tabla 'supermercado', columnas 'nombre_super', 'direccion' e 'id_super'
    if (opcion == 1) {
        sql = "UPDATE supermercado SET nombre_super = ? WHERE id_super = ?;";
    } else {
        sql = "UPDATE supermercado SET direccion = ? WHERE id_super = ?;";
    }

    // 3. Preparar y ejecutar
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        // Vinculamos el texto nuevo (parámetro 1)
        sqlite3_bind_text(stmt, 1, nuevoValor, -1, SQLITE_TRANSIENT);
        // Vinculamos el ID (parámetro 2)
        sqlite3_bind_int(stmt, 2, idSuper);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            // Verificamos si realmente se cambió algo (si el ID existía)
            if (sqlite3_changes(db) > 0) {
                printf("\n[OK] Supermercado actualizado correctamente.\n");
            } else {
                printf("\n[AVISO] No se encontró ningún supermercado con ID %d.\n", idSuper);
            }
        } else {
            printf("\n[ERROR] Fallo al ejecutar: %s\n", sqlite3_errmsg(db));
        }
    } else {
        printf("\n[ERROR] Error de SQL: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
