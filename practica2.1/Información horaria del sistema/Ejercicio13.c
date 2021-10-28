#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/time.h>

#define MILLION 1000000

int main(int argc, char **argv){

	struct timeval before;
	struct timeval after;
	struct timezone tz;

	gettimeofday(&before, &tz);

	for(int i = 0; i < MILLION; i++){}

	gettimeofday(&after, &tz);

	printf("Tiempo en incrementar una variable un millon de veces: %ld \n", ((after.tv_usec) - (before.tv_usec)));

	return 0;
}