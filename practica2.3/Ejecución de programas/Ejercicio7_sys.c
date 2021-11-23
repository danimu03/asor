#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char **argv){
	int aux = 1;
	for(int i=1; i < argc; ++i){
		aux += strlen(argv[i])+1;
	}

	char *command = malloc(sizeof(char)*aux);
	strcpy(command, "");

	for(int i = 1; i < argc; ++i){
		if(i != (argc-1)) {
			strcat(command, argv[i]);
			strcat(command, " ");
		}else {
			strcat(command, argv[i]);
		}

	}

	system(command);
	printf("El comando terminó de ejecutarse \n");


	return 0;
}

//Muestra "El comando terminó de ejecutarse" 