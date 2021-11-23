#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>

int stp = 0;

void handler(int s) {
	if(s == SIGUSR1) stp = 1;
}

int main(int argc, char **argv) {
	int seg = atoi(argv[1]);
	struct sigaction a;
	sigset_t s;
	sigemptyset(&s);

	sigaction(SIGUSR1, NULL, &a);
	a.sa_handler = handler;
	sigaction(SIGUSR1, &a, NULL);

	sigaction(SIGALRM ,NULL, &a);
	a.sa_handler = handler;
	sigaction(SIGALRM, &a, NULL);


	alarm(seg);

	sigsuspend(&s);

	if(stp == 0) {
		printf("Borrado\n");
		unlink(argv[0]);
	}else {
		printf("No borrado\n");
	}


}