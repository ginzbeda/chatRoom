#include "server.h"
#include "connection.h"
#include "chat.h"

int main(int argc, char **argv){
	if (argc != 2) {
    	fprintf(stderr, "usage: %s <port>\n", argv[0]);
   		exit(0);
  	}
  	init_message_buf();
  	int port = atoi(argv[1]);
  	int listener = open_listenfd(port);

  	while(1){
  		int *connfdp = (int*) malloc(sizeof(int));
  		struct sockaddr_in client_addr;
  		socklen_t clientlen = sizeof(struct sockaddr_in);
  		*connfdp = accept(listener, (SA*)&client_addr, &clientlen);
  		struct hostent *hp = gethostbyaddr((const char*)&client_addr.sin_addr.s_addr, sizeof(client_addr.sin_addr.s_addr), AF_INET);
    	char *haddrp = inet_ntoa(client_addr.sin_addr);
   		unsigned short client_port = ntohs(client_addr.sin_port);
    	printf("server connected to %s (%s), port %u\n", hp->h_name, haddrp,client_port);
    	pthread_t tid;
    	pthread_create(&tid, NULL, thread, connfdp);
  	}
  	return 1;
}