#include <iostream>
#include <vector>
#define MAXLINE 8192

typedef struct user {
	char nickname[16];
	struct sockaddr_in *server_addr;
	bool chatting;
}user;

typedef struct chatroom {
	vector<user> usrs;
	char name[25];
}chatroom;

vector<chatroom> chatrms;

user createUsr(char name[16], sockaddr_in* sockAdr);
int chattr(user *change);
int join(char name[25], char room[25]);
int rooms();
int leave();
int who();
int help();
int mess(char name[25], char msg[MAXLINE]);
