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

char message_buf[];

#define MAXLINE 8192
struct chat{
	int numberOfUsers = sizeof(usrs);
	int chatId;
	user usrs[];
}

//initialize message buffer
void init_message_buf()

//adds message to message buffer
void add_message(char *buf)

//recieves a command and a message
int recieve_message(int connfd, char *message)

//sends a command and a message
int send_message(int connfd, char*message)

//check if message is command
//check for "/"
int is_list_message(char *message)

//send 