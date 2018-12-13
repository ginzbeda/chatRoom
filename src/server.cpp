#include "server.h"
#include "chat.h"
#include "connection.h"

char message_buf[512];

void init_message_buf(){
	for(size_t i = 0; i<strlen(message_buf); i++){
		strcpy(&message_buf[i], "");
	}
}


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


//DONT UNDERSTAND HOW TO GET MESSAGE FROM THREAD//

/* thread routine */
void *thread(void *vargp) {
  // Grab the connection file descriptor.
  int connfd = *((int *)vargp);
  // Detach the thread to self reap.
  pthread_detach(pthread_self());
  // Free the incoming argument - allocated in the main thread.
  free(vargp);
  //input
  char buff[MAXLINE];
  //token holder
  vector<char*> args;
  // Handle the echo client requests.
  while(receive_message(connfd, buff)){
  	cout<< "prompt recieved: " << buff <<endl;
  	//separate input into tokens
  	char *token = strtok(buff, " ");
  	//push tokens into holder
  	while(token != NULL){
  		args.push_back(token);
  		token = strtok(NULL, " ");
  	}
  	for(size_t i = 0; i<args.size();i++){
  		cout<<args[i] <<endl;
  	}
  	//check first token for commands

  	if(strcmp(args[0], "\\JOIN")){
        join(args[1], args[2], connfd);
    }else if (strcmp(args[0], "\\ROOMS") == 0){
		  rooms(connfd);
	   }
	else if(strcmp(args[0], "\\LEAVE") == 0){
		leave(connfd);
    }
    else if(strcmp(args[0], "\\WHO") == 0){
    	who(connfd);
    }
    else if(strcmp(args[0], "\\HELP") == 0){
    	help(connfd);
    }
 //    else if( condition for nickname and message ){
 //      //send message to nickname from sender
 //    }
    
 //    else if(/* condition for incorrect command*/){
 //      //print error message
 // 	}
 // 	else{
 //      //send message to every connected client
 //    }
  	}
  printf("client disconnected.\n");
  // Don't forget to close the connection!
  close(connfd);
  return NULL;
}