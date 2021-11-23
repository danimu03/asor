#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sys/time.h>

int int_cnt = 0;
int tstp_cnt = 0;

void handler(int s) {
	if(s == SIGINT) ++int_cnt;
	if(s == SIGTSTP) ++tstp_cnt;
}

int main(int argc, char **argv){

	struct sigaction a;
	sigset_t s;
	sigemptyset(&s);

	sigaction(SIGINT, NULL, &a);
	a.sa_handler = handler;
	sigaction(SIGINT, &a, NULL);

	sigaction(SIGTSTP, NULL, &a);
	a.sa_handler = handler;
	sigaction(SIGTSTP, &a, NULL);

	while ((int_cnt + tstp_cnt) <10){
		sigsuspend(&s);
	}

	printf ("%i SIGINT capturadas\n%i SIGTSTP caputradas\n", int_cnt, tstp_cnt);

	return 0;
}