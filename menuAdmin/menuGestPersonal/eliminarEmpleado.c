/*
 * eliminarEmpleado.c
 *
 *  Created on: 2 abr 2026
 *      Author: ander.iglesias.ruiz
 */


#include "eliminarEmpleado.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"


#define MAX_DNI 20

#include "eliminarEmpleado.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"
#define MAX_DNI 20

int eliminarEmpleado() {
   sqlite3 *db;
   sqlite3_stmt *stmt;
   char dni[MAX_DNI];
   int result;
   result = sqlite3_open("BDD/deustomarket.db", &db);
   if (result != SQLITE_OK) {
       printf("Error opening database: %s\n", sqlite3_errmsg(db));
       return result;
   }
   printf("Database opened\n");
   printf("\n --- DAR DE BAJA EMPLEADO ---\n");
   printf("Introduce el DNI del empleado a dar de baja: ");
   if (fgets(dni, MAX_DNI, stdin) == NULL) {
       printf("Error leyendo el DNI.\n");
       sqlite3_close(db);
       return -1;
   }
   dni[strcspn(dni, "\n")] = '\0';
   char sqlCheck[] = "SELECT NOMBRE_EMPLEADO FROM EMPLEADO WHERE DNI_EMPLEADO = ?";
   result = sqlite3_prepare_v2(db, sqlCheck, -1, &stmt, NULL);
   if (result != SQLITE_OK) {
       printf("Error preparing statement (SELECT): %s\n", sqlite3_errmsg(db));
       sqlite3_close(db);
       return result;
   }
   sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
   if (sqlite3_step(stmt) != SQLITE_ROW) {
       printf("No se encontró ningún empleado con DNI %s.\n", dni);
       sqlite3_finalize(stmt);
       sqlite3_close(db);
       return -1;
   }
   printf("Empleado encontrado: %s\n", (char *)sqlite3_column_text(stmt, 0));
   sqlite3_finalize(stmt);
   printf("¿Estás seguro de que quieres darlo de baja? (s/n): ");
   char confirm;
   scanf(" %c", &confirm);
   while (getchar() != '\n');
   if (confirm != 's' && confirm != 'S') {
       printf("Operación cancelada.\n");
       sqlite3_close(db);
       return 0;
   }
   char sqlDelete[] = "DELETE FROM EMPLEADO WHERE DNI_EMPLEADO = ?";
   if (sqlite3_prepare_v2(db, sqlDelete, -1, &stmt, NULL) == SQLITE_OK) {
       sqlite3_bind_text(stmt, 1, dni, -1, SQLITE_STATIC);
       sqlite3_step(stmt);
       sqlite3_finalize(stmt);
   } else {
       printf("Error ejecutando el DELETE: %s\n", sqlite3_errmsg(db));
       sqlite3_close(db);
       return -1;
   }
   printf("Empleado con DNI %s dado de baja correctamente.\n", dni);
   sqlite3_close(db);
   printf("BD cerrada correctamente\n");

   // Logear operacion
   FILE *archivo;
   archivo = fopen("Configuracion/logs", "a");

   if (archivo != NULL) {
           fprintf(archivo, "Se elimino el empleado con DNI: %s\n", dni);
           fclose(archivo);
       } else {
           // Imprimimos un aviso en consola si falla, pero el programa no se cuelga
           printf("\n[Aviso]: No se pudo guardar el registro en el archivo de logs.\n");
       }


   return SQLITE_OK;
}
