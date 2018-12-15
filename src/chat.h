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
void ban(char* name, char* room, User* usr);

class User {
public:
	char nickname[16]; //PROBLEMS WITH USING THESE VARIABLES IN STATIC METHODS
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
	vector <int> ban;
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

	int getBan(User* usr){
		for(size_t i=0; i<ban.size(); i++){
			if(ban[i] == usr->getCon()){
				return 1;
			}
		}
		return 0;
	}
	void banUsr(User* usr){
		for(size_t i=0; i<ban.size(); i++){
			if(ban[i] == usr->getCon()){
				return;
			}
		}
		ban.push_back(usr->getCon());
	}
	void rmBan(User* usr){
		for(vector<int>::iterator p = ban.begin(); p != ban.end(); ++p){
			if((*p) == usr->getCon()){
				ban.erase(p);
				break;
			}
		}
	}
};



class Chat {
public:
	static vector<Chatroom *> chatrms;
};