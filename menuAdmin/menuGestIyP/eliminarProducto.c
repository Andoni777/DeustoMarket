/*
 * eliminarProducto.c
 *
 *  Created on: 2 abr 2026
 *      Author: ander.iglesias.ruiz
 */
#include "eliminarProducto.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

int eliminarProducto() {
   sqlite3 *db;
   sqlite3_stmt *stmt;
   int result;
   int id;
   result = sqlite3_open("BDD/deustomarket.db", &db);
   if (result != SQLITE_OK) {
       printf("Error opening database: %s\n", sqlite3_errmsg(db));
       return result;
   }
   printf("Database opened\n");
   printf("\n --- ELIMINAR PRODUCTO ---\n");
   printf("Introduce el ID del producto a eliminar: ");
   if (scanf("%d", &id) != 1) {
       printf("Error: Entrada no válida.\n");
       while (getchar() != '\n');
       sqlite3_close(db);
       return -1;
   }
   while (getchar() != '\n');
   char sqlCheck[] = "SELECT NOMBRE_PRODUCTO FROM PRODUCTO WHERE ID_PRODUCTO = ?";
   result = sqlite3_prepare_v2(db, sqlCheck, -1, &stmt, NULL);
   if (result != SQLITE_OK) {
       printf("Error preparing statement (SELECT): %s\n", sqlite3_errmsg(db));
       sqlite3_close(db);
       return result;
   }
   sqlite3_bind_int(stmt, 1, id);
   if (sqlite3_step(stmt) != SQLITE_ROW) {
       printf("No se encontró ningún producto con ID %d.\n", id);
       sqlite3_finalize(stmt);
       sqlite3_close(db);
       return -1;
   }
   printf("Producto encontrado: %s\n", (char *)sqlite3_column_text(stmt, 0));
   sqlite3_finalize(stmt);
   printf("¿Estás seguro de que quieres eliminarlo? (s/n): ");
   char confirm;
   scanf(" %c", &confirm);
   while (getchar() != '\n');
   if (confirm != 's' && confirm != 'S') {
       printf("Operación cancelada.\n");
       sqlite3_close(db);
       return 0;
   }
   char *sqlsFK[] = {
       "DELETE FROM DETALLE_PEDIDO WHERE ID_PRODUCTO = ?",
       "DELETE FROM INVENTARIO WHERE ID_PRODUCTO = ?",
       "DELETE FROM PRODUCTO WHERE ID_PRODUCTO = ?"
   };
   for (int i = 0; i < 3; i++) {
       if (sqlite3_prepare_v2(db, sqlsFK[i], -1, &stmt, NULL) == SQLITE_OK) {
           sqlite3_bind_int(stmt, 1, id);
           sqlite3_step(stmt);
           sqlite3_finalize(stmt);
       } else {
           printf("Error ejecutando el DELETE %d: %s\n", i, sqlite3_errmsg(db));
           sqlite3_close(db);
           return -1;
       }
   }
   printf("Producto con ID %d eliminado correctamente.\n", id);
   sqlite3_close(db);
   printf("BD cerrada correctamente\n");

   // Logear operacion
   FILE *archivo;
   archivo = fopen("Configuracion/logs", "a");

   if (archivo != NULL) {
           fprintf(archivo, "Se elimino el producto con ID: %d\n", id);
           fclose(archivo);
       } else {
           printf("\n[Aviso]: No se pudo guardar el registro en el archivo de logs.\n");
       }


   return SQLITE_OK;
}
