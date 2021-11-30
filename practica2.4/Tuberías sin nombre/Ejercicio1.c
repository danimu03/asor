#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>




int main(int argc, char **argv) {
	int t[2];
	
	if(pipe(t) == -1){
		return -1;
	}

	pid_t pid;
	

	if((pid= fork())>0){
		dup2(t[1],1);
		close(t[0]);
		execlp(argv[1], argv[1], argv[2], NULL);
		close(t[1]);
	}
	else if (pid==0){
		dup2(t[0],0);
		close(t[1]);
		execlp(argv[3], argv[3], argv[4], NULL);
		close(t[0]);
	}

	return 0;

}