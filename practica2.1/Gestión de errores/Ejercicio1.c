#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char ** argv) {

      if(setuid(0) != 0) {
            perror("setuid()");
            return -1;
      }

      return 0;
}