#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 8192

using namespace std;



typedef struct user {
	char nickname[16];
	sockaddr_in *server_addr;
	bool chatting;
}user;

typedef struct chatroom {
	vector <user> usrs;
	char name[25];
}chatroom;



user createUsr(char name[16], sockaddr_in* sockAdr);
int chattr(user *change);
int join(char *name, char *room);
int rooms();
int leave();
int who();
int help();
int mess(char name[25], char msg[MAXLINE]);

class Chat {
public:
	static vector<chatroom> chatrms;
};