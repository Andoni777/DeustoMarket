/*
 * modificarDatosSupermercado.c
 *
 *  Created on: 5 abr 2026
 *      Author: mike
 */
#include <stdio.h>
#include "modificarDatosSupermercado.h"

void modificarStockSupermercado() {
    int idSuper, opcion, idProd, cantidad;

    printf("\n--- MODIFICAR STOCK DE SUPERMERCADO ---\n");
    //Mostar supers ///

    // 1. Elegir el supermercado
    printf("Introduce el ID del supermercado: ");
    scanf("%d", &idSuper);
    // Aquí iría una función tipo: buscarSupermercado(idSuper);

    // 2. Elegir acción (Añadir o Quitar)
    printf("\n¿Qué desea hacer?\n");
    printf("1. Añadir stock (Entrada)\n");
    printf("2. Quitar stock (Salida/Venta)\n");
    printf("Seleccione una opción: ");
    scanf("%d", &opcion);

    // 3. Elegir el producto y la cantidad
    // mostrar catalogo //
    printf("Introduce el ID del producto: ");
    scanf("%d", &idProd);
    printf("Introduce la cantidad: ");
    scanf("%d", &cantidad);

    // 4. Aplicar lógica
    if (opcion == 1) {
        printf("\n[OK] Se han añadido %d unidades al producto %d en el super %d.\n", cantidad, idProd, idSuper);
        // actualizarArchivoStock(idSuper, idProd, cantidad);
    } else if (opcion == 2) {
        printf("\n[OK] Se han retirado %d unidades al producto %d en el super %d.\n", cantidad, idProd, idSuper);
        // actualizarArchivoStock(idSuper, idProd, -cantidad);
    } else {
        printf("\n[ERROR] Opción no válida.\n");
    }
    // añdir a la bd
}


