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
    char aux[2];
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];
    int fin = 0;

    memset(&h, 0, sizeof(struct addrinfo));
    h.ai_family = AF_UNSPEC;
    h.ai_socktype = SOCK_DGRAM;
    h.ai_flags = AI_PASSIVE;

    if (getaddrinfo(argv[1], argv[2], &h, &res) != 0) {
        printf("ERROR-> No se ha podido ejecutar el getaddrinfo.\n");
        return -1;
    }

    int socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

    if (bind(socket, res->ai_addr, res->ai_addrlen) != 0) {
        printf("ERROR-> No se ha podido ejecutar el bind.\n");
        return -1;
    }

    freeaddrinfo(res);
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    fd_set lect; //Creamos un descriptor de lectura
    int fd = -1;

    while(fin == 0){

        while(fd == -1) {
            FD_ZERO(&lect); //Vaciamos el puntero (No nos interesa ningún descriptor de fichero).
            FD_SET(socketUDP, &lect); //Metemos el descriptor del socket
            FD_SET(0, &lect); //Metemos el descriptor de la entrada estándar
            fd = select(socketUDP+1, &lect, NULL, NULL, NULL);
        }

        time_t tmp = time(NULL);
        struct tm *tm = localtime(&tmp);
        size_t max;
        char s[50];

        
        if (FD_ISSET(socketUDP,&lect)){
              ssize_t bytes_ = recvfrom(socket, , 2, 0, (struct sockaddr *) &addr, &len);

            getnameinfo((struct sockaddr *) &addr, len, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);
            printf("RED -> %i byte(s) de %s:%s\n", bytes, host, server);
            aux[1] = '\0';

            if (aux[0] == 't'){
                size_t bytes = strftime(s, max, "%I:%M:%S %p\n", tm);
                s[bytes] = '\0';
                sendto(socket, s, bytes, 0, (struct sockaddr *) &addr, len);
            }
            else if (aux[0] =='d'){
                size_t bytes = strftime(s, max, "%Y-%m-%d\n", tm);
                s[bytes] = '\0';
                sendto(socket, s, bytes, 0, (struct sockaddr *) &addr, len);
            }
            else if (aux[0] =='q'){
                printf("Saliendo...\n");
                fin = 1;
            }
            else{
                printf("Comando no soportado: %d...\n", aux[0]);
            }
        }
        else {
            read(0, aux, 2);
            printf("CONSOLA -> %i byte(s)\n",2);
            aux[1] = '\0';

            if (aux[0] == 't'){
                size_t bytes = strftime(s, max, "%I:%M:%S %p", tm);
                s[bytes] = '\0';
                printf("%s\n", s);

            }
            else if (aux[0] =='d'){
                size_t bytes = strftime(s, max, "%Y-%m-%d", tm);
                s[bytes] = '\0';

                printf("%s\n", s);
            }
            else if (aux[0] =='q'){
                printf("Saliendo...\n");
                exit(0);
            }else{
                printf("Comando no soportado: %d...\n", aux[0]);
            }

        }
    }

  return 0;
}