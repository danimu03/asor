#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>


int main(int argc, char **argv){

	time_t t;
	time(&t);

	printf("Hora en segundos: %ld \n", t);

	return 0;
}