#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAX_ERRORS 255

int main (int argc, char ** argv) {

      for(int i = 1; i <= MAX_ERRORS; i++) {
            printf("Error número: %d    Descripción de error: %s \n", i, strerror(i));
          
      }

      return 0;
}