#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 8192

using namespace std;

struct chatroom;





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
	static vector<chatroom*> chatrms;
	static vector<user*> usrs;
};
class User {
public:
	char nickname[16];
	int connfd;
	chatroom *room;
	static void createUsr(int fd){
		connfd = fd;
	}

	static void setChatrm(chatroom *rum){
		room = rum;
	}
	static chatroom* getChatrm(){
		return room;
	}
	static void namer(char name){
		nickname = name;
	}
	static void getName(){
		return nickname;
	}
	static int getCon(){
		return connfd;
	}
};

class Chatroom {
public:
	vector <user*> usrs;
	char name[25];

	static void createChatrm(char* nm){
		strncpy(name, nm, 25);
	}

	static void addUsr(user* usr){
		usrs.push_back(usr);
	}
	static vector<user*> getUsrLst(){
		return usrs;
	}

	static char* getNm(){
		return (char*) name;
	}
};