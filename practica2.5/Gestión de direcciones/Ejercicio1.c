#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(int argc, char **argv) {
    struct addrinfo h;
    struct addrinfo *res, *i;

    memset(&h, 0, sizeof(struct addrinfo));

    h.ai_family = AF_UNSPEC;
    h.ai_flags = AI_PASSIVE;

    int r = getaddrinfo(argv[1], NULL, &h, &res);

    if(r != 0){
        printf("ERROR getaddrinfo(): Name or service not known"); 
        return -1; 
    }

    for(i = res; i != NULL; i = i->ai_next){
        char hostname[NI_MAXHOST];
        getnameinfo(i->ai_addr, i-> ai_addrlen, hostname, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
        printf("%s  %i  %i\n", hostname, i->ai_family, i->ai_socktype);
    } 

    freeaddrinfo(res);

    return 0;

}