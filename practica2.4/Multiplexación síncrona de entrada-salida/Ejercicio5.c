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
#include <sys/select.h>

#define MAX 256

int main(int argc, char **argv){
	char buf[MAX+1];
	int c = 0, act;
	char *t = "t";
	char *t2 = "t2";

	mkfifo(t, 0644);
	mkfifo(t2, 0644);

	int fd = open(t, O_RDONLY | O_NONBLOCK);
	int fd2 = open(t2, O_RDONLY | O_NONBLOCK);


	while(c != -1) {
		fd_set mul;
		FD_ZERO(&mul);
		FD_SET(fd, &mul);
		FD_SET(fd2, &mul);

		int num_act;


		c = select((fd < fd2) ? fd2+1 : fd+1, &mul, NULL, NULL, NULL);

		if(c > 0 ) {
			if(FD_ISSET(fd, &mul)){
				num_act = 1;
				act = fd;
			}else{
				num_act = 2;
				act = fd2;
			}

			int size =  MAX;

			while(size == MAX){
				size = read(act, buf, MAX);
				buf[size] = '\0';
				printf("TUBERIA %i -> %s", num_act, buf);
			}

			if (size != 256 && num_act == 1){
				close(fd);
				fd = open(t, O_RDONLY | O_NONBLOCK);
			} else if(size != 256 && num_act == 2) {
				close(fd2);
				fd2 = open(t2, O_RDONLY | O_NONBLOCK);
			}
		}
	}

	close(fd);
	close(fd2);

	return 0;
}