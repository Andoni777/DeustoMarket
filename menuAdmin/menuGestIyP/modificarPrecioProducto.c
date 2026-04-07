#include "modificarPrecioProducto.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

void modificarPrecioProducto() {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int idProd;
    float nuevoPrecio;

    // 1. Abrir la base de datos
    int rc = sqlite3_open("BDD/deustomarket.db", &db);
    if (rc != SQLITE_OK) {
        printf("\n[ERROR] No se pudo abrir la base de datos: %s\n", sqlite3_errmsg(db));
        return;
    }

    printf("\n--- MODIFICAR PRECIO DE PRODUCTO ---");
    printf("\nIntroduce el ID del producto: ");
    if (scanf("%d", &idProd) != 1) {
        printf("ID no válido.\n");
        sqlite3_close(db);
        return;
    }
    getchar(); // Limpiar el buffer

    printf("Introduce el nuevo precio: ");
    if (scanf("%f", &nuevoPrecio) != 1) {
        printf("Precio no válido.\n");
        sqlite3_close(db);
        return;
    }
    getchar(); // Limpiar el buffer

    // 2. Sentencia SQL con los nombres de tu esquema
    const char *sql = "UPDATE producto SET precio_producto = ? WHERE id_producto = ?;";

    // 3. Preparar la consulta
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("\n[ERROR] Error de SQL: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    // 4. Vincular los datos
    // El precio es double/float (parámetro 1), el ID es entero (parámetro 2)
    sqlite3_bind_double(stmt, 1, (double)nuevoPrecio);
    sqlite3_bind_int(stmt, 2, idProd);

    // 5. Ejecutar
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        // Comprobar si realmente se encontró el ID y se cambió algo
        if (sqlite3_changes(db) > 0) {
            printf("\n[OK] Precio actualizado con éxito para el producto ID %d.\n", idProd);
        } else {
            printf("\n[AVISO] No existe ningún producto con el ID %d.\n", idProd);
        }
    } else {
        printf("\n[ERROR] No se pudo ejecutar la actualización: %s\n", sqlite3_errmsg(db));
    }

    // 6. Limpiar y cerrar
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
