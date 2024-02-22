#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usuario.h"
#include "LinkedList.h"
#include "validaciones.h"
#include "controller.h"

int pedirPath(char* path)
{
    int retorno = 0;
    char auxPath[30];

    if(path != NULL)
    {
        system("cls");
        printf("         ***INGRESE PATH DEL ARCHIVO***\n\n");
        printf("Ingrese path(posts.csv): ");
        fflush(stdin);
        gets(auxPath);
        while(strlen(auxPath) <= 0 || strlen(auxPath) >= 20)
        {
            printf("Path demasiado largo/corto. Vuelva a ingresar path: ");
            fflush(stdin);
            gets(auxPath);
        }
        strcpy(path, auxPath);
        retorno = 1;
    }
    return retorno;
}


int parser_PostsFromText(FILE* pFile , LinkedList* pLista)
{
	int retorno = 0;
	char buffer[5][100];
	eUsuario* auxUser = NULL;

	if(pFile!=NULL && pLista!=NULL)
	{
		fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

		while(!feof(pFile))
		{
			fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^\n]", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);
			auxUser = usuario_NewUsuarioStr(buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);

			if(auxUser != NULL)
			{
				ll_add(pLista, auxUser);
			}
		}
		retorno = 1;
	}
    return retorno;
}

/** \brief Carga los datos de los paises desde el archivo vacunas.csv (modo texto).
 *
 * \param path char*
 * \param pLista LinkedList*
 * \return int
 *
 */
int controller_cargarPostsDesdeTexto(char* path , LinkedList* pLista)
{
	int retorno=0;
	FILE* file = NULL;

	if(pLista!=NULL && path!=NULL)
	{
		file=fopen(path,"r");

		if(file!=NULL)
		{
			parser_PostsFromText(file, pLista);
			retorno=1;
		}
		fclose(file);
	}
    return retorno;
}

int controller_listarUsuario(eUsuario* usuario)
{
	int retorno = 0;
	int id;
	char user[100];
	int likes;
	int dislikes;
	int followers;

	if(usuario!=NULL)
	{
		if(usuario_GetId(usuario, &id) && usuario_GetUser(usuario, user) && usuario_GetLikes(usuario, &likes) && usuario_GetDislikes(usuario, &dislikes) &&
		   usuario_GetFollowers(usuario, &followers))
		{
			printf("| %-3d |  %-26s  |   %-5d   |    %-5d     |    %-5d     |\n", id, user, likes, dislikes, followers);
		}
	}


	return retorno;
}


int controller_listarUsuarios(LinkedList* pLista)
{
	int retorno = 0;
	int largo = ll_len(pLista);

	if(pLista != NULL && largo > 0)
	{
		system("cls");
		printf( "================================================================================\n"
				"|                            ***LISTA USUARIOS***                              |\n"
				"================================================================================\n"
				"| ID  |            USER              |  LIKES    |   DISLIKES  |  FOLLOWERS    |\n"
			    "--------------------------------------------------------------------------------\n");

		for(int i=0; i < largo; i++)
		{
			controller_listarUsuario((eUsuario*) ll_get(pLista, i));
		}
		printf( "================================================================================\n");
		retorno=1;
	}
    return retorno;
}

int controller_asignarLikes(LinkedList* lista)
{
	int retorno = 0;
	if(lista!=NULL)
	{
		ll_map(lista, controller_asignarLikesAleatorio);
		retorno = 1;
	}
	return retorno;
}

void* controller_asignarLikesAleatorio(void* elemento)
{
	int likes;
	eUsuario* auxUser = NULL;

	if(elemento!=NULL)
	{
		auxUser = (eUsuario*)elemento;
		likes = (rand() % (5000 - 600 + 1)) + 600;
		usuario_SetLikes(auxUser, likes);
	}

	return auxUser;
}

int controller_asignarDislikes(LinkedList* lista)
{
	int retorno = 0;
	if(lista!=NULL)
	{
		ll_map(lista, controller_asignarDislikesAleatorio);
		retorno = 1;
	}
	return retorno;
}

void* controller_asignarDislikesAleatorio(void* elemento)
{
	int dislikes;
	eUsuario* auxUser = NULL;

	if(elemento!=NULL)
	{
		auxUser = (eUsuario*)elemento;
		dislikes = (rand() % (3500 - 300 + 1)) + 300;
		usuario_SetDislikes(auxUser, dislikes);
	}

	return auxUser;
}

int controller_asignarFollowers(LinkedList* lista)
{
	int retorno = 0;
	if(lista!=NULL)
	{
		ll_map(lista, controller_asignarFollowersAleatorio);
		retorno = 1;
	}
	return retorno;
}

void* controller_asignarFollowersAleatorio(void* elemento)
{
	int followers;
	eUsuario* auxUser = NULL;

	if(elemento!=NULL)
	{
		auxUser = (eUsuario*)elemento;
		followers = (rand() % (20000 - 10000 + 1)) + 10000;
		usuario_SetFollowers(auxUser, followers);
	}

	return auxUser;
}

int filtrarMejoresPost(void* user)
{

	int retorno=0;
	eUsuario* auxUser = NULL;
	int likes;

	if(user!=NULL)
	{
		auxUser=(eUsuario*)user;
		usuario_GetLikes(auxUser,&likes);

		if(likes > 4000)
		{
			retorno=1;
		}
	}
    return retorno;
}

int filtrarPeoresPost(void* user)
{

	int retorno=0;
	eUsuario* auxUser = NULL;
	int likes;
	int dislikes;

	if(user!=NULL)
	{
		auxUser=(eUsuario*)user;
		usuario_GetLikes(auxUser,&likes);
		usuario_GetDislikes(auxUser,&dislikes);

		if(likes - dislikes < 0)
		{
			retorno=1;
		}
	}
    return retorno;
}

int controller_guardarUsuariosTexto(char* path , LinkedList* lista)
{
	int retorno = 0;
	eUsuario* auxUser = NULL;
	int id;
	char user[100];
	int likes;
	int dislikes;
	int followers;
	int tam;
	FILE* f=fopen(path,"w");

	tam=ll_len(lista);

	if(path!=NULL && lista!=NULL && f!=NULL)
	{
		fprintf(f,"id,user,likes,dislikes,followers\n");

		for(int i=0;i<tam;i++)
		{
			auxUser=(eUsuario*)ll_get(lista, i);
			usuario_GetId(auxUser, &id);
			usuario_GetUser(auxUser, user);
			usuario_GetLikes(auxUser, &likes);
			usuario_GetDislikes(auxUser, &dislikes);
			usuario_GetFollowers(auxUser, &followers);
			fprintf(f,"%d,%s,%d,%d,%d\n",id,user,likes,dislikes,followers);
			retorno = 1;
		}
	}
	fclose(f);

    return retorno;
}

int ordenarUsuariosPorFollowers(void* UserI, void* userJ)
{
    int returnAux=0;
    eUsuario* userIndiceI;
    eUsuario* userIndicej;
    int auxFollowersI;
    int auxFollowersJ;

    if(UserI != NULL && userJ != NULL)
    {
    	userIndiceI = (eUsuario*)UserI;
    	userIndicej = (eUsuario*)userJ;

    	usuario_GetFollowers(userIndiceI,&auxFollowersI);
    	usuario_GetFollowers(userIndicej,&auxFollowersJ);

        if(auxFollowersI < auxFollowersJ)
        {
            returnAux=1;
        }

    }
    return returnAux;
}

int ordenarUsuariosPorLikes(void* UserI, void* userJ)
{
    int returnAux=0;
    eUsuario* userIndiceI;
    eUsuario* userIndicej;
    int auxLikesI;
    int auxLikesJ;

    if(UserI != NULL && userJ != NULL)
    {
    	userIndiceI = (eUsuario*)UserI;
    	userIndicej = (eUsuario*)userJ;

    	usuario_GetLikes(userIndiceI,&auxLikesI);
    	usuario_GetLikes(userIndicej,&auxLikesJ);

        if(auxLikesI < auxLikesJ)
        {
            returnAux=1;
        }

    }
    return returnAux;
}

int masPopular(LinkedList* lista)
{
	int retorno = 0;
	int tam;
	eUsuario* aux = NULL;
	int mayor;
	LinkedList* listaOrdenada = ll_newLinkedList();

	if(lista != NULL && listaOrdenada != NULL)
	{
		system("cls");
		listaOrdenada = ll_clone(lista);
		ll_sort(listaOrdenada, ordenarUsuariosPorLikes, 1);
		tam = ll_len(listaOrdenada);
		printf( "================================================================================\n"
				"|                          ***POSTEO MAS LIKEADO***                            |\n"
				"================================================================================\n"
				"| ID  |            USER              |  LIKES    |   DISLIKES  |  FOLLOWERS    |\n"
			    "--------------------------------------------------------------------------------\n");
        aux = (eUsuario*) ll_get(listaOrdenada, 0);
        usuario_GetLikes(aux, &mayor);
		for(int i=0; i<tam; i++)
		{
		    aux = (eUsuario*) ll_get(listaOrdenada, i);
		    if(aux->likes == mayor)
            {
                controller_listarUsuario(aux);
            }
		}
		printf("================================================================================\n");
		retorno = 1;
	}

	return retorno;
}
