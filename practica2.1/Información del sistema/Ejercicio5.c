#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argv) {
       struct utsname buf;

       int ret = uname(&buf);
       if(ret == -1) {
              printf("%s", strerror(errno));
       }

       printf("Sysname: %s \nNodename: %s \nRelease: %s \nVersion: %s \nMachine: %s \n", buf.sysname, buf.nodename, buf.release, buf.version, buf.machine);
       return 0;
}