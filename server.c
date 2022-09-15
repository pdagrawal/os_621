#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <strings.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#define SA struct sockaddr

int main(int argc, char *argv[]){
	if (argc < 3) {
		printf("\n Proper usage of the code: ./server <portnumber> <numberofclients>");
		exit(1);
	}
	// convert the portnumber to a integer
	int portnumber = atoi(argv[1]);
	// maximum number of clients that can connect to the server
	int maxnumclients = atoi(argv[2]);
	printf("\n Server supposed to start at %d for a maximum number of %d clients", portnumber, maxnumclients);

	// variables for socket definition
	int sockfd, connfd, len;
	struct sockaddr_in serveradd, cli;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd == -1) {
		printf("\n Error in creating the socket");
		exit(1);
	}
	bzero(&serveradd, sizeof(serveradd));
	serveradd.sin_family = AF_INET;
	// sin_addre
	serveradd.sin_addr.s_addr = htonl(INADDR_ANY);
	serveradd.sin_port = htons(portnumber);
	int val = bind(sockfd, (SA *) &serveradd, sizeof(serveradd));
	if (val != 0) {
		printf("\n Binding failed");
		exit(1);
	} else {
		printf("\n Binding succeeded");
	}

	val = listen(sockfd, maxnumclients);
	if (val != 0) {
		printf("\n Listening Failed");
	} else {
		printf("\n Listening succeeded");
	}
  len = sizeof(cli);
	connfd = accept(sockfd, (SA *) &cli, &len);
	if (connfd < 0) {
		printf("\n Error connecting to the server");
		exit(1);
	} else {
		printf("\n Hello world");
	}
}
