#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct
{
    int id;
    char user[50];
    int likes;
    int dislikes;
    int followers;
}eUsuario;

#endif // USUARIO_H_INCLUDED

eUsuario* usuario_NewUsuario();
eUsuario* usuario_NewUsuarioStr(char* id, char* user, char* likes, char* dislikes, char* followers);

//setters
int usuario_SetId(eUsuario* usuario, int id);
int usuario_SetUser(eUsuario* usuario, char* user);
int usuario_SetLikes(eUsuario* usuario, int likes);
int usuario_SetDislikes(eUsuario* usuario, int dislikes);
int usuario_SetFollowers(eUsuario* usuario, int followers);

//getters
int usuario_GetId(eUsuario* usuario, int* id);
int usuario_GetUser(eUsuario* usuario, char* user);
int usuario_GetLikes(eUsuario* usuario, int* likes);
int usuario_GetDislikes(eUsuario* usuario, int* dislikes);
int usuario_GetFollowers(eUsuario* usuario, int* followers);
