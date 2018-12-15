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
  User* nUser = new User(connfd);
  //input
  char buff[MAXLINE];
  //token holder
  vector<char*> args;
  // Handle the client requests.
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
	  		cout<<"args " << i << ": " <<args[i] <<endl;
	  	}
	  	//check first token for commands
	    if(*(args[0]) == '\\') // checks if its a command by checking if the first character of the first token is '\'
	    { 
		    if(strcmp(args[0], "\\JOIN") == 0){
		    	cout<< "Joining: " << args[1] << " to room: " << args[2] <<endl;
		    	join(args[1], args[2], nUser);
		    }
		    else if (strcmp(args[0], "\\ROOMS") == 0){
		    	cout<< "Listing rooms"<<endl;
		    	rooms(nUser);
		    }
		    else if(strcmp(args[0], "\\LEAVE") == 0){
		    	cout<< "Leaving room" <<endl;
		    	leave(nUser);
		    }
		    else if(strcmp(args[0], "\\WHO") == 0){
		    	cout<<"Listing users in room" <<endl;
		    	who(nUser);
		    }
		    else if(strcmp(args[0], "\\HELP") == 0){
		    	cout<<"Listing commands" <<endl;
		    	help(nUser);
		    }
		    else if(strcmp(args[0], "\\BAN")==0){
		    	cout<< "Banning user: " << args[1] << " from: " << args[2]<<endl;
		    	ban(args[1], args[2], nUser);
		    }
		    else if((args.size()) == 2){ // \nickname message is the only COMMAND with 2 arguments
		    	pthread_mutex_lock(&lck);
		    	mess(args[0]+1,args[1],nUser); // the +1 is for getting rid of the '\' in the command and sends just the nickname and not \nickname
		    	pthread_mutex_unlock(&lck);
		    }
		    else{
		    	cout<< "command not recognized" <<endl;
		    	char str0[50],str1[50],str2[30]; // uses three char[] to join to form the command "\LAEVE" command not recognized.
		    	strcpy(str0,"\"");                 //trust me, it works
		    	strcpy(str1,args[0]);
		    	strcpy(str2,"\" command not recognized.\n");
		    	strcat(str1,str2);
		    	strcat(str0,str1);
		    	send_message(connfd,str0);
		    }
    	}
	    else{
	      //sends message to everyone
	    	cout<<"Sending message to everyone" <<endl;
	    	pthread_mutex_lock(&lck);
	      	message_everyone(buff, nUser); 
	      	pthread_mutex_unlock(&lck);
	    }
		args.clear();
    	memset(buff, 0, MAXLINE);
  	}
  printf("client disconnected.\n");
  // Don't forget to close the connection!
  close(connfd);
  return NULL;
}