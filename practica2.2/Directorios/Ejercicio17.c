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


	char *p = malloc(sizeof(char)*(size + strlen(cur->d_name) +3));
	strcpy(p,argv[1]);
	

	if(stat(p, &st) == -1){
		printf("Archivo erroneo.");
		closedir(dir);
		return -1;
	} else {
		if((S_ISREG(st.st_mode)) && ((S_IWUSR | st.st_mode) == 0100)) {
			printf("Fichero exec: %s* \n", cur->d_name);
			
		}
		else if((S_ISREG(st.st_mode)) && !((S_IWUSR | st.st_mode) == 0100)) {
			printf("Fichero normal: %s \n", cur->d_name);
			
		}
		else if (S_ISDIR(st.st_mode)) {
			printf("Directorio: %s/ \n", cur->d_name);
		}

		else if (S_ISLNK(st.st_mode)) {
			char *linkname = malloc(st.st_size+1);
			readlink(p, linkname, st.st_size+1);
			printf("Link: %s->%s \n", cur->d_name, linkname);
			free(linkname);
		}
		
	}

	free(p);
	closedir(dir);
	return 0;

}