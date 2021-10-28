#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// long pathconf(const char *camino, int nombre);
int main(int argc, char **argv){

       printf("Numero maximo de enlaces: %ld \n", pathconf(".", _PC_LINK_MAX));
       printf("Tamaño maximo de ruta: %ld \n", pathconf(".", _PC_PATH_MAX));
       printf("Tamaño maximo de nombre de fichero: %ld \n", pathconf(".", _PC_NAME_MAX));

       return 0;
}