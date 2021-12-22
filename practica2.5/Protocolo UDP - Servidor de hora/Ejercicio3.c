#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>


int main (int argc, char**argv) {
    struct addrinfo h;
    struct addrinfo *res;
    char aux[2];
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];
   

    memset(&h, 0, sizeof(struct addrinfo));
    h.ai_family = AF_UNSPEC;
    h.ai_socktype = SOCK_DGRAM;
    h.ai_flags = AI_PASSIVE;

    
    if (getaddrinfo(argv[1], argv[2], &h, &res) != 0) {
        printf("ERROR-> No se ha podido ejecutar el getaddrinfo.\n");
        return -1;
    }

    int socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    freeaddrinfo(res);
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    sendto(socket, argv[3], 2, 0, res->ai_addr, res->ai_addrlen);
    printf("%s\n", argv[3]);

    if (*argv[3] == 'd' || *argv[3] == 't'){
        char buf[50];
        ssize_t bytes = recvfrom(socket, buf, 50, 0, (struct sockaddr *) &addr, &len);
        buf[bytes] = '\0';

        printf("%s\n", buf);
    }

    return 0;
}