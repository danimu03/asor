#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv){
	char *path = getenv("HOME");
	char *t = strcat(path, "/asor/practica2.4/Tuberías con nombre/t");

	mkfifo(t, 0777);
	int fd = open(t, O_WRONLY);

	write(fd, argv[1], strlen(argv[1]));

	return 0;
}