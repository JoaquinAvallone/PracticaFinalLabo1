#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usuario.h"
#include "menu.h"
#include "LinkedList.h"
#include "validaciones.h"
#include "controller.h"

int main()
{
    char respuesta = 's';
    char path[20];
    LinkedList* listaUsuarios = ll_newLinkedList();
    LinkedList* listaMejoresPosteos = ll_newLinkedList();
    LinkedList* listaPeoresPosteos = ll_newLinkedList();
    LinkedList* listaAux = ll_newLinkedList();

    int flagEstadisticas = 0;

    do{
        switch(menuPrincipal())
        {
        case 1:
            pedirPath(path);
            if(strcmp(path, "posts.csv") == 0)
            {
                if(controller_cargarPostsDesdeTexto(path, listaUsuarios))
                {
                    printf("Archivo cargado con exito!!!\n");
                }
                else
                {
                    printf("Hubo un problema al cargar el archivo posts.csv\n");
                }
            }
            else
            {
                printf("El path ingresado es invalido. Recomendacion de path: posts.csv\n");
            }
            system("pause");
            break;
        case 2:
            if(ll_isEmpty(listaUsuarios))
            {
                printf("No hay usuarios para mostrar. Ingrese al punto 1.\n");
            }
            else
            {
                controller_listarUsuarios(listaUsuarios);
            }
            system("pause");
            break;
        case 3:
            if(ll_isEmpty(listaUsuarios))
            {
                printf("No hay usuarios para mostrar. Ingrese al punto 1.\n");
            }
            else
            {
                if(controller_asignarLikes(listaUsuarios) && controller_asignarDislikes(listaUsuarios) && controller_asignarFollowers(listaUsuarios))
                {
                    flagEstadisticas = 1;
                    controller_listarUsuarios(listaUsuarios);
                }
                else
                {
                    printf("Hubo un error al asignar las estadisticas.\n");
                }
            }
            system("pause");
            break;
        case 4:
            if(ll_isEmpty(listaUsuarios))
            {
                printf("No hay usuarios para mostrar. Ingrese al punto 1.\n");
            }
            else
            {
                if(!flagEstadisticas)
                {
                    printf("Primero debe infgresar a la asignacion de estadisticas.\n");
                }
                else
                {
                    listaMejoresPosteos = ll_filter(listaUsuarios, filtrarMejoresPost);
                    controller_listarUsuarios(listaMejoresPosteos);
                    printf("           Lista de postesos con mas de 4K likes.\n");
                    controller_guardarUsuariosTexto("mejoresPosts.csv", listaMejoresPosteos);
                }
            }
            system("pause");
            break;
        case 5:
            if(ll_isEmpty(listaUsuarios))
            {
                printf("No hay usuarios para mostrar. Ingrese al punto 1.\n");
            }
            else
            {
                if(!flagEstadisticas)
                {
                    printf("Primero debe infgresar a la asignacion de estadisticas.\n");
                }
                else
                {
                    listaPeoresPosteos = ll_filter(listaUsuarios, filtrarPeoresPost);
                    controller_listarUsuarios(listaPeoresPosteos);
                    printf("           Lista de postesos con mas dislikes que likes.\n");
                    controller_guardarUsuariosTexto("peoresPosts.csv", listaPeoresPosteos);
                }
            }
            system("pause");
            break;
        case 6:
            if(ll_isEmpty(listaUsuarios))
            {
                printf("No hay usuarios para mostrar. Ingrese al punto 1.\n");
            }
            else
            {
                if(!flagEstadisticas)
                {
                    printf("Primero debe infgresar a la asignacion de estadisticas.\n");
                }
                else
                {
                    listaAux = ll_clone(listaUsuarios);
                    ll_sort(listaAux, ordenarUsuariosPorFollowers, 1);
                    controller_listarUsuarios(listaAux);
                }
            }
            system("pause");
            break;
        case 7:
            if(ll_isEmpty(listaUsuarios))
            {
                printf("No hay usuarios para mostrar. Ingrese al punto 1.\n");
            }
            else
            {
                if(!flagEstadisticas)
                {
                    printf("Primero debe infgresar a la asignacion de estadisticas.\n");
                }
                else
                {
                    masPopular(listaUsuarios);
                }
            }
            system("pause");
            break;
        case 8:
            confirmaSalida(&respuesta, 'n', 's');
            system("pause");
            break;
        default:
            printf("La opcion ingresa es incorrecta.\n");
            system("pause");
            break;
        }
    }while(respuesta == 's');

    return 0;
}
