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
    char buf[81];
    int clientSd;
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];
    ssize_t aux;
    int n = 0;

    memset(&h,0,sizeof(struct addrinfo));
    h.ai_family = AF_UNSPEC;
    h.ai_socktype = SOCK_STREAM; 
    h.ai_flags = AI_PASSIVE; 

    
    if (getaddrinfo(argv[1], argv[2], &h, &res) != 0) {
        printf("ERROR-> No se ha podido ejecutar getaddrinfo()\n");
        return -1;
    }

    int socket = socket(res->ai_family, res->ai_socktype, 0);
    bind(socket, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);

    listen(socket, 5);

    struct sockaddr_storage client;
    socklen_t len = sizeof(cli);
   
    while (n==0) {
        clientSd = accept(socket,(struct sockaddr *) &client, &len);
        getnameinfo((struct sockaddr *)&client, len, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST);
        printf("Conexión desde %s:%s\n", host, server);

        aux = recv(clientSd, buf, 80, 0);
        buf[aux] = '\0';

        if ((buf[0] == 'Q') && (aux == 2)) {
            printf("Conexión terminada\n");
            n = 1;
        }
        if(n == 0){
            send(clientSd, buf, aux, 0);
        }
    }

    close(clientSd);



    return 0;
}
