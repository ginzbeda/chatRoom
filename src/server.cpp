#include "server.h"
#include "chat.h"
#include "connection.h"

char message_buf[512];
pthread_mutex_t lck = PTHREAD_MUTEX_INITIALIZER;


void init_message_buf(){
	for(size_t i = 0; i<strlen(message_buf); i++){
		strcpy(&message_buf[i], "");
	}
}

/*
  @param {int} port - takes the port number for the server socket
*/
//  creates a server socket and listens for any incoming connections

int open_listenfd(int port){
	int listener;
	int optval = 1;
	struct sockaddr_in server_addr;
	if((listener = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
	if(setsockopt(listener, SOL_SOCKET, SO_REUSEADDR, (const void*) &optval, sizeof(int))<0)
		return -1;

	bzero((char *) &server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons((unsigned short)port);
	if (bind(listener, (SA *)&server_addr, sizeof(server_addr)) < 0) return -1;
	if(listen(listener, LISTENQ)< 0) return -1;
	return listener;
}



/* thread routine */
void *thread(void *vargp) {
  int connfd = *((int *)vargp);
  pthread_detach(pthread_self());
  User* nUser = new User(connfd);
  char buff[MAXLINE];
  vector<char*> args;
  while(receive_message(connfd, buff)){
	  	cout<< "prompt recieved: " << buff <<endl;
	  	char *token = strtok(buff, " ");
	  	while(token != NULL){
	  		args.push_back(token);
	  		token = strtok(NULL, " ");
	  	}
	  	for(size_t i = 0; i<args.size();i++){
	  		cout<<"args " << i << ": " <<args[i] <<endl;
	  	}
	    if(*(args[0]) == '\\')
	    { 
		    if(strcmp(args[0], "\\JOIN") == 0){
		    	join(args[1], args[2], nUser);
		    }
		    else if (strcmp(args[0], "\\ROOMS") == 0){
		    	rooms(nUser);
		    }
		    else if(strcmp(args[0], "\\LEAVE") == 0){
		    	leave(nUser);
		    }
		    else if(strcmp(args[0], "\\WHO") == 0){
		    	who(nUser);
		    }
		    else if(strcmp(args[0], "\\HELP") == 0){
		    	help(nUser);
		    }
		    else if((args.size()) == 2){
		    	pthread_mutex_lock(&lck);
		    	mess(args[0]+1,args[1],nUser);
		    	pthread_mutex_unlock(&lck);
		    }
		    else{
		    	char str0[50],str1[50],str2[30];
		    	strcpy(str0,"\""); 
		    	strcpy(str1,args[0]);
		    	strcpy(str2,"\" command not recognized.\n");
		    	strcat(str1,str2);
		    	strcat(str0,str1);
		    	send_message(connfd,str0);
		    }
    	}
	    else{
	    	pthread_mutex_lock(&lck);
	      	message_everyone(buff, nUser); 
	      	pthread_mutex_unlock(&lck);
	    }
		args.clear();
    	memset(buff, 0, MAXLINE);
  	}
  printf("client disconnected.\n");
  close(connfd);
  return NULL;
}