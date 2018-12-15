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

typedef struct sockaddr SA; 


#define MAXLINE 512 
#define LISTENQ 1024

void init_message_buf();

int open_listenfd(int port);

void *thread(void *vargp);