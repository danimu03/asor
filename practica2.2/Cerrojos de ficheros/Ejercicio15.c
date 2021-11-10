#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/file.h>

int main(int argc, char **argv){
	int fd = open(argv[1], O_CREAT | O_RDWR, 0777);


	if(lockf(fd, F_TEST,0) == 0){
		printf("DESBLOQUEADO. \n");

		lockf(fd, F_LOCK, 0);

		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		char buf[2048];
		sprintf(buf, "%d:%d actual time.\n", tm->tm_hour, tm->tm_min);
		write(fd, &buf, strlen(buf));

		sleep(30);

		lockf(fd, F_ULOCK, strlen(buf));

	}else {
		printf("BLOQUEADO. \n");
	}

	return 0;
}