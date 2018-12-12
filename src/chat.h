#include <iostream>
#define MAXLINE 8192

typedef struct chatroom {
	vector<user> usrs;
	char name[25];
}chatroom;

vector<chatroom> chatrms;

int join(char name[25], char room[25]);
int rooms();
int leave();
int who();
int help();
int mess(char name[25], char msg[MAXLINE]);
