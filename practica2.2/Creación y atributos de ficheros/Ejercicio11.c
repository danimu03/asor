#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/sysmacros.h>

int main(int argc, char **argv){
	struct stat st;
	stat(argv[1],&st);
	char *h = malloc(sizeof(char) *(5+strlen(argv[1])));
	char *s = malloc(sizeof(char) *(5+strlen(argv[1])));

	strcpy(h,argv[1]);
	strcpy(s,argv[1]);

	h = strcat(h, ".hard");
	s = strcat(s, ".sym");

	mode_t m = st.st_mode;

	if(S_ISREG(m)){
		link(argv[1],h);
		link(argv[1],s);
	}
	return 0;
}