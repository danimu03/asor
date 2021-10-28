#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
//long int sysconf(int nombre);
int main(int argc, char **argv){
       
       printf("Longitud maxima argumentos: %ld \n", sysconf(_SC_ARG_MAX));
       printf("Numero maximo de hijos: %ld \n", sysconf(_SC_CHILD_MAX));
       printf("Numero maximo de ficheros: %ld \n", sysconf(_SC_OPEN_MAX));

       return 0;
}       
