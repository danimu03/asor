#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>


int main(int argc, char **argv){

	struct tm *lt;
	time_t t;
	time(&t);

	lt = localtime(&t);

	printf("Año: %d \n", lt->tm_year);

	return 0;
}
