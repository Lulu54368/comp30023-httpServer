#define _POSIX_C_SOURCE 200112L
#define IMPLEMENTS_IPV6
#define MULTITHREADED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include "utils.h"
#include "multithreads.h"

int main(int argc, char** argv){
	int server_sockfd, newsockfd;
    socklen_t server_len, client_len;
    struct sockaddr_in6 server_address;
    struct sockaddr_in6 client_address;
	
    server_sockfd = socket(AF_INET6, SOCK_STREAM, 0); //AF_INET & AF_INET6
	//char buffer[2048];
	if (server_sockfd < 0) {
		perror("socket");
		exit(EXIT_FAILURE);
	}
	if (argc < 4) {
		fprintf(stderr, "ERROR, not enough args provided\n");
		exit(EXIT_FAILURE);
	}
    memset(&server_address, 0, sizeof(server_address));
	// Create address we're going to listen on (with given port number)
	server_address.sin6_family = AF_INET6;
    server_address.sin6_addr = in6addr_any;
    server_address.sin6_port = htons(atoi(argv[2]));    
	
    server_len = sizeof(server_address);
	// Reuse port if possible
	int re = 1;
	if (setsockopt(server_sockfd, SOL_SOCKET, SO_REUSEADDR, &re, sizeof(int)) < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
    // Bind address to the socket
	if (bind(server_sockfd, (struct sockaddr *)&server_address, server_len) < 0) {
		perror("bind");
		exit(EXIT_FAILURE);
	}
    
	// Listen on socket - means we're ready to accept connections,
	// incoming connection requests will be queued, man 3 listen
	if (listen(server_sockfd, 20) < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}
    
	// Accept a connection - blocks until a connection is ready to be accepted
	// Get back a new file descriptor to communicate on
	
	input_t *i;
	while(1){
		
		i = (input_t *)malloc(sizeof(input_t));
		i->folder = malloc(sizeof(argv[3]));
		i->folder = argv[3];
		client_len = sizeof(client_address);
		newsockfd = accept(server_sockfd,
        (struct sockaddr *)&client_address, &client_len);
	
		if (newsockfd < 0) {
			perror("accept");
		
			close(newsockfd);
		}
		i->newsockfd = newsockfd;
		pthread_t tid;
		pthread_create(&tid, NULL, thread_task, i);
		//pthread_join(tid, NULL);
		
		
		
	}
	// Read characters from the connection, then process
	close(server_sockfd);

	
	return 0;
}

