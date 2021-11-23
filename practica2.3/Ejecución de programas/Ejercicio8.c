#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <fcntl.h>




int main (int argc, char **argv){
	pid_t pid = fork();

	if(pid == 0){
		setsid();
		printf("Proceso hijo -> %i  (Proceso padre -> %i)\n Hijo:\n", getpid(), getppid());
		int fd_std = open("/tmp/daemon.out", O_CREAT | O_RDWR , 00777);
		int fd_err =  open("/tmp/daemon.err", O_CREAT | O_RDWR , 00777);
		int fd_null = open("/dev/null", O_CREAT | O_RDWR , 00777);
		dup2(fd_std,1);
		dup2(fd_err,2);
		dup2(fd_null,0);

		execvp(argv[1], argv+1);
	}
	else {
		printf("Proceso padre -> %i  (Proceso padre -> %i)\n Padre:\n", getpid(), getppid());
		sleep(3);		
	}
	
	return 0;
}
