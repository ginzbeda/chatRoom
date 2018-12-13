#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 8192

using namespace std;



typedef struct user {
	char nickname[16];
	int connfd;
<<<<<<< HEAD
	char room[25];
=======
>>>>>>> 842d6cb7f5bfb1f249ce89523e83b4099061b120
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
	static vector<user> usrs;
};