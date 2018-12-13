#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 8192

using namespace std;



typedef struct user {
	char nickname[16];
	int connfd;
	bool chatting;
}user;

typedef struct chatroom {
	vector <user> usrs;
	char name[25];
}chatroom;



user createUsr(char name[16], sockaddr_in* sockAdr);
int chattr(user *change);
int join(char *name, char *room, int connfd);
int rooms(int connfd);
int leave(int connfd);
int who(int connfd);
int help(int connfd);
int mess(char name[25], char msg[MAXLINE], int connfd);

class Chat {
public:
	static vector<chatroom> chatrms;
};