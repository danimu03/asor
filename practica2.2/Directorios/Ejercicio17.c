#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

int main (int argc, char **argv) {
	if(argc < 2) {
		printf("Numero de argumentos erroneo. \n");
		return -1;
	}

	DIR *dir = opendir(argv[1]);

	if(dir == NULL) {
		printf("No existe el directorio. \n");
		return -1;
	}

	struct dirent *cur;
	struct stat st;

	size_t size = strlen(argv[1]);
	cur = readdir(dir);
	unsigned long int ts= 0;

	while(cur != NULL){

		char *p = malloc(sizeof(char)*(size + strlen(cur->d_name) +3));
		strcpy(p,argv[1]);
		strcpy(p,"/");
		strcpy(p,cur->d_name);


		if(lstat(p, &st) == -1){ //OJO con stat para los link devuelve la info del fichero al que apunta
			printf("Archivo erroneo. \n");
			closedir(dir);
			return -1;
		} else {
			if (S_ISLNK(st.st_mode)) {
				char *linkname = malloc(st.st_size+1);
				readlink(p, linkname, st.st_size+1);
				printf("Link: %s->%s \n", cur->d_name, linkname);
				free(linkname);
			}

			else if((S_ISREG(st.st_mode)) && (access(cur->d_name, X_OK) == 0)) {
				printf("Fichero exec: %s* \n", cur->d_name);
				ts = ts  + ((st.st_blksize/8) * st.st_blocks);
				
			}
			else if((S_ISREG(st.st_mode)) && (access(cur->d_name, X_OK) != 0)) {
				printf("Fichero normal: %s \n", cur->d_name);
				ts = ts  + ((st.st_blksize/8) * st.st_blocks);
				
			}
			else if (S_ISDIR(st.st_mode)) {
				printf("Directorio: %s/ \n", cur->d_name);
			}
			
		}
		free(p);
		cur = readdir(dir);
	}
	printf("Total size: %ld\n", ts);

	closedir(dir);
	return 0;

}
