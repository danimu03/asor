#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv){

	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);
	int fd2 = dup2(fd,1);

	printf("Redireccion de la salidada estandar a %s\n", argv[1]);
	dup2(fd2,fd);

	return 0;
}