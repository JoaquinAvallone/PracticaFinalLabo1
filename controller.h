#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED



#endif // CONTROLLER_H_INCLUDED

int pedirPath(char* path);
int parser_PostsFromText(FILE* pFile , LinkedList* pLista);
int controller_cargarPostsDesdeTexto(char* path , LinkedList* pLista);
int controller_listarUsuario(eUsuario* usuario);
int controller_listarUsuarios(LinkedList* pLista);
int controller_asignarLikes(LinkedList* lista);
void* controller_asignarLikesAleatorio(void* elemento);
int controller_asignarDislikes(LinkedList* lista);
void* controller_asignarDislikesAleatorio(void* elemento);
int controller_asignarFollowers(LinkedList* lista);
void* controller_asignarFollowersAleatorio(void* elemento);
int filtrarMejoresPost(void* user);
int filtrarPeoresPost(void* user);
int controller_guardarUsuariosTexto(char* path , LinkedList* lista);
int ordenarUsuariosPorFollowers(void* UserI, void* userJ);
int ordenarUsuariosPorLikes(void* UserI, void* userJ);
int masPopular(LinkedList* lista);
