#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 8192

using namespace std;
class User;
class Chatroom;
class Chat;

//Joins chatroom (returns 1) Creates chatroom and joins (returns 2)
int join(char *name, char *room, User* usr);
int rooms(User* usr);
int leave(User* usr);
int who(User* usr);
int help(User* usr);
int mess(char name[25], char msg[MAXLINE], User* usr);


class User {
public:
	char nickname[16];
	int connfd;
	Chatroom *room;
	
	User(int fd){
		connfd = fd;
	}

	void setChatrm(Chatroom *rum){
		room = rum;
	}
	Chatroom* getChatrm(){
		return room;
	}
	void namer(char* name){
		strncpy(nickname, name, 16);
	}
	char* getName(){
		return nickname;
	}
	int getCon(){
		return connfd;
	}
};

class Chatroom {
public:
	vector <User*> usrs;
	char name[25];

	Chatroom(char* nm){
		strncpy(name, nm, 25);
	}

	void addUsr(User* usr){
		usrs.push_back(usr);
	}
	vector<User*> getUsrLst(){
		return usrs;
	}

	char* getNm(){
		return (char*) name;
	}
};

class Chat{
public:
	static vector<Chatroom*> chatrms;
};