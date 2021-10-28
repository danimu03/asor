#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char **argv){

	printf("UID real: %i \nUID efectivo: %i \n", geteuid(), getuid());

	return 0;
}

//UID cambia al usuario de fichero