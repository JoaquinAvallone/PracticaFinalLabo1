#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "usuario.h"

eUsuario* usuario_NewUsuario()
{
    eUsuario* u = (eUsuario*) malloc(sizeof(eUsuario));

    if(u != NULL)
    {
        u->id = 0;
        strcpy(u->user, "");
        u->likes = 0;
        u->dislikes = 0;
        u->followers = 0;
    }
    return u;
}
eUsuario* usuario_NewUsuarioStr(char* id, char* user, char* likes, char* dislikes, char* followers)
{
    eUsuario* u = usuario_NewUsuario();

    if(u != NULL && id != NULL && user != NULL && likes != NULL && dislikes != NULL && followers != NULL)
    {
        if(!(usuario_SetId(u, atoi(id)) && usuario_SetUser(u, user) && usuario_SetLikes(u, atoi(likes)) && usuario_SetDislikes(u, atoi(dislikes)) && usuario_SetDislikes(u, atoi(dislikes))))
        {
            free(u);
            u = NULL;
        }
    }
    return u;
}

//setters
int usuario_SetId(eUsuario* usuario, int id)
{
    int retorno = 0;

    if(usuario != NULL && id > 0)
    {
        usuario->id = id;
        retorno = 1;
    }
    return retorno;
}
int usuario_SetUser(eUsuario* usuario, char* user)
{
    int retorno = 0;

    if(usuario != NULL && user != NULL && strlen(user) >= 3 && strlen(user) < 50)
    {
        strcpy(usuario->user, user);
        retorno = 1;
    }
    return retorno;
}
int usuario_SetLikes(eUsuario* usuario, int likes)
{
    int retorno = 0;

    if(usuario != NULL && likes >= 0 && likes <= 5000)
    {
        usuario->likes = likes;
        retorno = 1;
    }
    return retorno;
}
int usuario_SetDislikes(eUsuario* usuario, int dislikes)
{
    int retorno = 0;

    if(usuario != NULL && dislikes >= 0)
    {
        usuario->dislikes = dislikes;
        retorno = 1;
    }
    return retorno;
}
int usuario_SetFollowers(eUsuario* usuario, int followers)
{
    int retorno = 0;

    if(usuario != NULL && followers >= 0)
    {
        usuario->followers = followers;
        retorno = 1;
    }
    return retorno;
}

//getters
int usuario_GetId(eUsuario* usuario, int* id)
{
    int retorno = 0;

    if(usuario != NULL && id != NULL)
    {
        *id = usuario->id;
        retorno = 1;
    }
    return retorno;
}
int usuario_GetUser(eUsuario* usuario, char* user)
{
    int retorno = 0;

    if(usuario != NULL && user != NULL)
    {
        strcpy(user, usuario->user);
        retorno = 1;
    }
    return retorno;
}
int usuario_GetLikes(eUsuario* usuario, int* likes)
{
    int retorno = 0;

    if(usuario != NULL && likes != NULL)
    {
        *likes = usuario->likes;
        retorno = 1;
    }
    return retorno;
}
int usuario_GetDislikes(eUsuario* usuario, int* dislikes)
{
    int retorno = 0;

    if(usuario != NULL && dislikes != NULL)
    {
        *dislikes = usuario->dislikes;
        retorno = 1;
    }
    return retorno;
}
int usuario_GetFollowers(eUsuario* usuario, int* followers)
{
    int retorno = 0;

    if(usuario != NULL && followers != NULL)
    {
        *followers = usuario->followers;
        retorno = 1;
    }
    return retorno;
}
