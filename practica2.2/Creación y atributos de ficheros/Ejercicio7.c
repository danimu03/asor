#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main (int argc, char **argv){

	mode_t cmask;
	cmask = umask(027);

	int fd = open(argv[1],O_CREAT|O_TRUNC, 0645);

	umask(cmask);

	return fd;
}
