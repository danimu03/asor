#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX 256

int main(int argc, char **argv) {
	pid_t pid;
	int p_h[2];
	int h_p[2];

	if(pipe(p_h) == -1){
		return -1;
	}
	if(pipe(h_p) == -1){
		return -1;
	}

	if((pid = fork()) >0){
		char msg[MAX];
		char msg_aux[1];
		close(p_h[0]);
		close(h_p[1]);

		

		while(msg_aux[0] != 'q'){
			printf("MSG: \n");
			int s = read(0, msg, 256);
			if(s == -1) {
				return -1;
			}

			msg[s] = '\0';
			write(p_h[1], msg, s+1);
			while(msg_aux[0] != 'l' && msg_aux[0] != 'q') {
				read(h_p[0], msg_aux,1);
			}
		}

		close(p_h[1]);
		close(h_p[0]);
		
	}
	else if(pid == 0){
		int i;
		char msg[MAX];
		char msg_aux[1];
		close(p_h[1]);
		close(h_p[0]);

		for(i = 0; i < 10; ++i){
			int s = read(p_h[0], msg, MAX);
			msg[s] = '\0';

			printf("HIJO -> %s", msg);
			sleep(1);

			if(i != 9){
				msg_aux[0]='l';
				write(h_p[1], msg_aux, 1);
			} else {
				msg_aux[0]='q';
				write(h_p[1], msg_aux, 1);
			}
			
		}

		close(p_h[0]);
		close(h_p[1]);
		return 0;
	}

	return 0;
}