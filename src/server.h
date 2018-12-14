#include <arpa/inet.h>
#include <ctype.h>
#include <netdb.h>

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <iostream>



using namespace std;

typedef struct sockaddr SA; //should be sockaddr_in


//variable for username - char *username; or string username; if we need username lengths later

#define MAXLINE 512 // maximum length of a line - max length of a message
#define LISTENQ 1024 // second argument to listen() - is usually 5 but idk

//initialize message buffer
void init_message_buf();//or just use bzero(buff,len);

int open_listenfd(int port);

void *thread(void *vargp);
// struct chat{
// 	int numberOfUsers = sizeof(usrs);
// 	int chatId;
// 	vetor<user> usr;
// }

/*

vector for list of usernames in a room
vector for list of rooms
user structs should have
	- username
	-socket address

*/


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