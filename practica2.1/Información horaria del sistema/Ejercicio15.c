#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#define TAM_BUFFER 256

int main(int argc, char **argv){

	struct tm *lt;
	time_t t;
	time(&t);
	char buf[TAM_BUFFER];


	lt = localtime(&t);

	//  nano /etc/locale.gen puede ser solo es_ES
	printf("La configuracion local es: %s \n", setlocale(LC_ALL,"es_ES.UTF-8"));
	strftime(buf, TAM_BUFFER, "%A, %d de %B de %G, %H:%M", lt);

	printf("%s\n", buf);

	return 0;
}