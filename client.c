#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAXSIZE 1024

void communication(int socketfd, int id) {
    char write_buff[MAXSIZE];
    char read_buff[10];
    for(int i=0; i<MAXSIZE; i++) {
        write_buff[i] = '1';
    }
    write(socketfd, write_buff, MAXSIZE);
    read(socketfd, read_buff, 1);
    printf("\n Received: %c", read_buff[0]);
    write(socketfd, &id, sizeof(int));
    return;
}

int main(int argc, char *argv[]) {
    int clientid = atoi(argv[1]);
    int port = atoi(argv[2]);
    int socketfd, connfd;
    struct sockaddr_in serveradd, cli;

    // socket create and verification
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        printf("\n Error creating a socket");
        exit(1);
    } else {
        printf("Socket successfully created..\n");
    }
    bzero(&serveradd, sizeof(serveradd));

    // assign IP, PORT
    serveradd.sin_family = AF_INET;
    serveradd.sin_addr.s_addr = inet_addr("127.0.0.1");
    serveradd.sin_port = htons(port);

    // connect the client socket to server socket
    connfd = connect(socketfd, (struct sockaddr *) &serveradd, sizeof(serveradd));
    communication(socketfd, clientid);
    close(socketfd);
    // if (connect(socketfd, (SA*)&serveradd, sizeof(serveradd)) != 0) {
    //     printf("connection with the server failed...\n");
    //     exit(0);
    // }
    // else
    //     printf("connected to the server..\n");
}
