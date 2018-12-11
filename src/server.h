#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <iostream>



using namespace std;

typedef struct sockaddr SA;

char message_buf[512];

#define MAXLINE 8192
#define LISTENQ 1024 // second argument to listen()

//initialize message buffer
void init_message_buf();

int open_listenfd(int port);

void *thread(void *vargp);
// struct chat{
// 	int numberOfUsers = sizeof(usrs);
// 	int chatId;
// 	vetor<user> usr;
// }




//adds message to message buffer
// void add_message(char *buf)

//recieves a command and a message
// int recieve_message(int connfd, char *message)

//sends a command and a message
// int send_message(int connfd, char*message)

//check if message is command
//check for "/"
// int is_list_message(char *message)

//TO BE COMPLETED