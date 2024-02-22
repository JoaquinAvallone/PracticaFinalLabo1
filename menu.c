#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"
#include "validaciones.h"

int menuPrincipal()
{
    int opcion;
    system("cls");
    printf("          ***MENU PRINCIPAL*** \n\n");
    printf("1.Cargar archivos\n"
           "2.Imprimir lista\n"
           "3.Asignar estadisticas\n"
           "4.Filtrar por mejores posteos\n"
           "5.Filtrar por haters\n"
           "6.Ordenar por nivel de cantidad de followers\n"
           "7:Mostrar mas popular\n"
           "8.Salir\n");

           utn_getNumeroInt(&opcion, "Ingrese opcion: ", "Error\n", 1, 8, 4);

    return opcion;
}
