#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main (int argc, char ** argv) {

      if(setuid(0) != 0) {
            //perror("setuid()");
            printf("Error número: %d \nDescripción de error: %s \n", errno, strerror(errno));
            return -1;
      }

      return 0;
}