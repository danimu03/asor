#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>

int main (int argc, char **argv){
       struct stat st;
       stat(argv[1],&st);


       //Major, Minor
       printf("Major: %li\n", (long) major(st.st_dev));
       printf("Major: %li\n", (long) major(st.st_dev));

       //I-Nodo
       printf("I-Node: %li\n", st.st_ino);

       //Tipo de fichero
       mode_t mode = st.st_mode;
       printf("Mode: %li. ", mode);

       if(S_ISLNK(mode)) { printf("%s es un enlace simbólico. \n", argv[1]);}
       else if(S_ISREG(mode)) { printf("%s es un fichero ordinario. \n", argv[1]);}
       else if(S_ISDIR(mode)) { printf("%s es un directorio. \n", argv[1]);}
       
       //Hora de acceso M
       printf("Ultimo acceso M: %i\n", ctime(&st.st_mtime));

       //Hora de acceso c
       printf("Ultimo acceso C: %i\n", ctime(&st.st_ctime));

       return 0;
}