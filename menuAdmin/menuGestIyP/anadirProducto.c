/*
 * anadirProducto.c
 *
 *  Created on: 5 abr 2026
 *      Author: mike
 */

#include "anadirProducto.h"
#include <stdio.h>
#include <string.h>
#include "../../BDD/sqlite3.h"

int anadirProducto() {
	sqlite3 *db;
    sqlite3_stmt *stmt;
	sqlite3_open("BDD/deustomarket.db", &db);
	char buffer[30];

    int result;

    char nombre[15];
    float precio = -1.0;
    int id_categoria = -1;



	sqlite3_open("BDD/deustomarket.db", &db);

    printf("\n --- AÑADIR NUEVO PRODUCTO ---\n");

    do {
            printf("\nIntroduce el NOMBRE del nuevo producto: ");
            fgets(nombre, 15, stdin);
            nombre[strcspn(nombre, "\n")] = 0;

            if (strlen(nombre) == 0) {
                printf("\n--> Error: Valor no permitido\n\n");
            }
        } while (strlen(nombre) == 0);

    do {
    	printf("\nIntroduce el PRECIO del nuevo producto: ");
    	fgets(buffer, sizeof(buffer), stdin);
    		if (sscanf(buffer, "%f", &precio) != 1 || precio < 0) {
    			printf("--> Error: Valor no permitido (debe ser un número positivo)\n\n");
    		}

    	} while (precio < 0);

    do {
    	printf("\n--- Categorias Disponibles ---\n");
    	char sqlCategorias[] = "SELECT id_categoria, nombre_categoria FROM categoria";
    	sqlite3_prepare_v2(db, sqlCategorias, -1, &stmt, NULL);

    	while ((result = sqlite3_step(stmt)) == SQLITE_ROW) {
    		printf("ID: %d - %s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
    	}
    	sqlite3_finalize(stmt);

    	printf("\nIntroduce la CATEGORIA del nuevo producto: ");
    	fgets(buffer, sizeof(buffer), stdin);
    		if (sscanf(buffer, "%i", &id_categoria) != 1 || id_categoria <= 0) {
    			printf("\n--> Error: Valor no permitido\n\n");
    		}

       	} while (id_categoria < 0);




    char SQLInsert[] = "INSERT INTO producto (nombre_producto, precio_producto, id_categoria) VALUES (?, ?, ?)";

    result = sqlite3_prepare_v2(db, SQLInsert, -1, &stmt, NULL);
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 2, (double)precio);
    sqlite3_bind_int(stmt, 3, id_categoria);

    result = sqlite3_step(stmt);
    if (result == SQLITE_DONE) {
		printf("\n Producto '%s' añadido correctamente a la base de datos!", nombre);
	} else {
		printf("\n--> Error añadiendo el producto '%s' a la base de datos: %s", nombre, sqlite3_errmsg(db));
	}

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    // Logear operacion
    FILE *archivo;
    archivo = fopen("Configuracion/logs", "a");

    if (archivo != NULL) {
            fprintf(archivo, "Se añadio el producto %s con precio de %f € a la categoria de ID: %d\n", nombre, precio, id_categoria);
            fclose(archivo);
        } else {
            // Imprimimos un aviso en consola si falla, pero el programa no se cuelga
            printf("\n[Aviso]: No se pudo guardar el registro en el archivo de logs.\n");
        }

    return SQLITE_OK;

}
