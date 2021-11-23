#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>


//Primero en shell:
// SLEEP_SECS="20"
// export SLEEP_SECS
// En otra shell:
// pkill Ejercicio11 -SIGTSTP


int main(int argc, char **argv){
	sigset_t s;
	

	sigemptyset(&s);
	sigaddset(&s, SIGINT);
	sigaddset(&s, SIGTSTP);
	if(sigprocmask(SIG_BLOCK, &s, NULL) == -1) {
		perror("No se pueden bloquear\n");
		return -1;
	}

	char *sl = getenv("SLEEP_SECS");
	if(sl == NULL) {
		printf("No se pueden leer seg\n");
		return -1;
	}
	int seg = atoi(sl);
	if(seg < 0) seg = 0;
	sleep(seg);

	sigset_t p;

	sigemptyset(&p);
	if(sigpending(&p) == -1){
		printf("No se pueden chequear\n");
		return -1;
	}

	if(sigismember(&p, SIGINT) ==1){
		printf("Recibida señal SIGINT\n");
		sigdelset(&s, SIGINT);
	}

	if(sigismember(&p, SIGTSTP) ==1){
		printf("Recibida señal SIGTSTP\n");
		sigdelset(&s, SIGTSTP);
	}

	sigprocmask(SIG_UNBLOCK, &s, NULL);
	

	return 0;
}