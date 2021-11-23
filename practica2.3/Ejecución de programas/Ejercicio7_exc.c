#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>



int main (int argc, char **argv){
	
	execvp(argv[1], argv +1);
	printf("El comando terminó de ejecutarse \n");


	return 0;
}

// No imprime, cambia el flujo de ejecucion al del comando que hemos pasado