#include "server.h"

char message_buf[512];


void init_message_buf(){
	for(int i = 0; i<sizeof(message_buf); i++){
		strcpy(&message_buf[i], "");
	}
}

// void add_message(char *buf){
// 	pthread_mutex_lock(&lock)

// }

// int recieve_message(int connfd, char *message)

// int send_message()

int open_listenfd(int port){
	int listener;
	int optval = 1;
	struct sockaddr_in server_addr;

  // socket descriptor created
	if((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;

  // socket already in use
	if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (const void*) &optval, sizeof(int))<0)
		return -1;

  /* Listenfd will be an endpoint for all requests to port
     on any IP address for this host */
	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons((unsigned short)port);
	
	if (bind(listener, (SA *)&server_addr, sizeof(server_addr)) < 0) return -1;

	// Make it a listening socket ready to accept connection requests 
	if(listen(listener, LISTENQ)< 0) return -1;
	return listener;
}


/* thread routine */
void *thread(void *vargp) {
  // Grab the connection file descriptor.
  int connfd = *((int *)vargp);
  // Detach the thread to self reap.
  pthread_detach(pthread_self());
  // Free the incoming argument - allocated in the main thread.
  free(vargp);
  // Handle the echo client requests.
  cout<< connfd << endl;
  printf("client disconnected.\n");
  // Don't forget to close the connection!
  close(connfd);
  return NULL;
}
