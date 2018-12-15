#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 512

using namespace std;
class User;
class Chatroom;
class Chat;


void join(char *name, char *room, User* usr);
void rooms(User* usr);
void leave(User* usr);
void who(User* usr);
void help(User* usr);
void mess(char name[25], char msg[MAXLINE], User* usr);
void message_everyone(char msg[MAXLINE], User* usr);

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
	Chatroom *getChatrm(){
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
	vector <User *> usrs;
	char name[25];

	Chatroom(char* nm){
		strncpy(name, nm, 25);
	}

	 void addUsr(User *usr){
		usrs.push_back(usr);
	}
	 vector<User *> getUsrLst(){
		return usrs;
	}
	void rmUsr(User *usr){

		for(vector<User *>::iterator p = usrs.begin(); p != usrs.end(); ++p){
			cout<< "(*p)->getName(): " << (*p)->getName()<< endl;
			cout<< "usr->getName(): " << usr->getName() << endl;
			if(strcmp((*p)->getName(), usr->getName()) == 0){
				usrs.erase(p);
				break;
			}
		}
		usr->setChatrm(0);
	}

	 char *getNm(){
		return (char *) name;
	}
};



class Chat {
public:
	static vector<Chatroom *> chatrms;
};