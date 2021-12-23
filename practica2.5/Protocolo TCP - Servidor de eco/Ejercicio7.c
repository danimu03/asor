#include <stdio.h>
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
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];
    ssize_t aux;
    int n = 0;
    char in[256];
    char out[256];

    memset(&h,0,sizeof(struct addrinfo));
    h.ai_family = AF_UNSPEC;
    h.ai_socktype = SOCK_STREAM; 
    h.ai_flags = AI_PASSIVE; 

    
    if (getaddrinfo(argv[1], argv[2], &h, &res) != 0) {
        printf("ERROR-> No se ha podido ejecutar getaddrinfo()\n");
        return -1;
    }

    int socket = socket(res->ai_family, res->ai_socktype, 0);
    connect(socket,(struct sockaddr *)res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    while (n == 0) {
        aux = read(0,out, 255);
        out[aux] = '\0';
        send(socket,out, aux, 0);


        if ((out[1] == 'q') && (aux == 2)) {
            printf("Conexión terminada\n");
            n == 1;
        }

        if(n == 0) {
            aux = recv(socket, in, 255, 0);
            in[aux] = '\0';
            printf("%s\n", in);
        }
    }

    close(socket);
    return 0;
}