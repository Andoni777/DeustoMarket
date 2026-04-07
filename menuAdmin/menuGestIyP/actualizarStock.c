#include "actualizarStock.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

void actualizarStock() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int idProd, idSuper, nuevoStock;

    if (sqlite3_open("BDD/deustomarket.db", &db) != SQLITE_OK) {
        printf("\n[ERROR] No se pudo abrir la base de datos.\n");
        return;
    }

    printf("\n--- GESTIÓN DE STOCK EN INVENTARIO ---");
    printf("\nID del Producto: "); scanf("%d", &idProd);
    printf("ID del Supermercado: "); scanf("%d", &idSuper);
    printf("Nuevo Stock: "); scanf("%d", &nuevoStock);
    getchar();

    // 1. Intentamos primero el UPDATE
    const char *sqlUpdate = "UPDATE inventario SET stock = ? WHERE id_producto = ? AND id_super = ?;";

    sqlite3_prepare_v2(db, sqlUpdate, -1, &stmt, NULL);
    sqlite3_bind_int(stmt, 1, nuevoStock);
    sqlite3_bind_int(stmt, 2, idProd);
    sqlite3_bind_int(stmt, 3, idSuper);

    sqlite3_step(stmt);
    int filasCambiadas = sqlite3_changes(db);
    sqlite3_finalize(stmt);

    // 2. Si no se cambió nada, NO EXISTE ->  INSERT
    if (filasCambiadas == 0) {
        printf("[INFO] El producto no estaba registrado en este super. Creando entrada...\n");

        const char *sqlInsert = "INSERT INTO inventario (id_super, id_producto, stock) VALUES (?, ?, ?);";

        if (sqlite3_prepare_v2(db, sqlInsert, -1, &stmt, NULL) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, idSuper);
            sqlite3_bind_int(stmt, 2, idProd);
            sqlite3_bind_int(stmt, 3, nuevoStock);

            if (sqlite3_step(stmt) == SQLITE_DONE) {
                printf("[OK] Nuevo registro de stock creado con éxito.\n");
            } else {
                printf("[ERROR] No se pudo crear el registro: %s\n", sqlite3_errmsg(db));
            }
            sqlite3_finalize(stmt);
        }
    } else {
        printf("[OK] Stock actualizado correctamente (UPDATE).\n");
    }

    sqlite3_close(db);
}
