#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>

void ejercicio5(){
	struct rlimit l;
	getrlimit(RLIMIT_NOFILE, &l);
	char *p = malloc(sizeof(char)*(4096+1));
	getcwd(p, 4096+1);


	printf("PID -> %i\n", getpid());
	printf("PPID -> %i\n", getppid());
	printf("GID -> %i\n", getgid());
	printf("SID -> %i\n", getsid(getpid()));
	printf("LIMIT -> %li\n", l.rlim_max);
	printf("PATH -> %s\n", p);

	free(p);
}


int main (int argc, char **argv){
	pid_t pid = fork();

	if(pid == 0){
		setsid();
		chdir("/tmp");
		printf("Proceso hijo -> %i  (Proceso padre -> %i)\n Hijo:\n", getpid(), getppid());
		ejercicio5();

	}
	else {
		printf("Proceso padre -> %i  (Proceso padre -> %i)\n Padre:\n", getpid(), getppid());
		ejercicio5();
		sleep(3);
		
	}
	
	return 0;
}

