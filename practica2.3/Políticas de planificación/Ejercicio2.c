#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sched.h>


int main (int argc, char **argv){
	pid_t pid;
	int sched;
	int p_max;
	int p_min;
	struct sched_param sched_p;

	pid = getpid();
	sched = sched_getscheduler(pid);
	sched_getparam(pid, &sched_p);
	p_max = sched_get_priority_max(sched);
	p_min = sched_get_priority_min(sched);

	//Planificacion
	if(sched == SCHED_FIFO){
		printf("SCHEDULER FIFO\n");
	}
	else if(sched == SCHED_RR) {
		printf("SCHEDULER RR\n");
	}
	else if(sched == SCHED_OTHER) {
		printf("SCHEDULER OTHER\n");
	}

	//Prioridad
	printf("PRIORITY -> %i\n", sched_p.sched_priority);

	//Max y min
	printf("MAX-> %i\nMIN->%i\n", p_max,p_min);

	return 0;
	
}
