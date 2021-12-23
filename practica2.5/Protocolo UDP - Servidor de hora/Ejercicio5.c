#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <time.h>

int cnt;
void handler(int s) {
	if(s==SIGTERM) ++cnt;
}

int main (int argc, char**argv) {
    struct addrinfo h;
    struct addrinfo *res;
    char aux[2];
    char host[NI_MAXHOST];
    char server[NI_MAXSERV];
    int fin = 0;
    int i = 0;
    int status;

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
    signal(SIGTERM, handler);
    struct sockaddr_storage addr;
    socklen_t len = sizeof(addr);

    for (i = 0; i < 2; i++){
        pid_t pid;
        pid = fork();

        if (pid == 0) {
            while(fin == 0){
                ssize_t bytes = recvfrom(socket, aux, 2, 0, (struct sockaddr *) &addr, &len);
                aux[1] = '\0';

                getnameinfo((struct sockaddr *) &addr, len, host, NI_MAXHOST, server, NI_MAXSERV, NI_NUMERICHOST|NI_NUMERICSERV);

                printf("%i byte(s) de %s:%s\n", bytes, host, server);

                time_t tmp = time(NULL);
                struct tm *tm = localtime(&tmp);
                size_t max;
                char s[50];

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
        }
        else {
            pid = wait(&status);
        }
    }
