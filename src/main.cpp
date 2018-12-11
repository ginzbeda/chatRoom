#include "chat.h"
#include "server.h"
#include "user.h"

int main(int argc, char **argv){
	//checks arguments and prints usage
	if (argc != 2) {
    	fprintf(stderr, "usage: %s <port>\n", argv[0]);
   		exit(0);
  	}

  	//message buffer initialized
  	init_message_buf();

  	//port number
  	int port = atoi(argv[1]);

  	//listening file descriptor
  	int listener = open_listenfd(port);

  	while(1){
  		//connection file descriptor
  		int *connfdp = (int*) malloc(sizeof(int));

  		//Client's IP address info
  		struct sockaddr_in client_addr;

  		//wait for incoming connections
  		socklen_t clientlen = sizeof(struct sockaddr_in);
  		*connfdp = accept(listener, (SA*)&client_addr, &clientlen);

  		//determine domain name and IP address of client
  		struct hostent *hp =
  			gethostbyaddr((const char*)&client_addr.sin_addr.s_addr, 
  				sizeof(client_addr.sin_addr.s_addr), AF_INET);

  		// The server IP address information.
    	char *haddrp = inet_ntoa(client_addr.sin_addr);

    	// The client's port number.
   		unsigned short client_port = ntohs(client_addr.sin_port);

    	printf("server connected to %s (%s), port %u\n", hp->h_name, haddrp,
           client_port);

    	// Create a new thread to handle the connection.
    	pthread_t tid;
    	pthread_create(&tid, NULL, thread, connfdp);
  	}
  	return 1;
}