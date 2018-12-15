#include <iostream>
#include <vector>
#include <string.h>
#include <netinet/in.h>
#define MAXLINE 512

using namespace std;
class User;
class Chatroom;
class Chat;

//Join a room
/*
  @param {char*} name - nickname to join under
  @param {char*} room - room to join
  @param {User*} usr - takes in a pointer to User
*/
void join(char *name, char *room, User* usr);
//Lists rooms
/*
  @param {User*} usr - takes in a pointer to User
*/
void rooms(User* usr);
//Leaves current chatroom
/*
  @param {User*} usr - takes in a pointer to User
*/
void leave(User* usr);
//Lists Users in chatroom
/*
  @param {User*} usr - takes in a pointer to User
*/
void who(User* usr);
//Lists roocommands
/*
  @param {User*} usr - takes in a pointer to User
*/
void help(User* usr);
//Sends private emssage
/*
  @param {char} *name - nickname for destination
  @param {char} *msgr -message to be sent
  @param {User*} usr - takes in a pointer to User
*/
void mess(char name[25], char msg[MAXLINE], User* usr);
//Messages whole chatroom
/*
  @param {char} message[MAXLINE] - message to be sent
  @param {User*} usr - takes in a pointer to User
*/
void message_everyone(char msg[MAXLINE], User* usr);
//Ban from chatroom
/*
  @param {char*} name -User to ban
  @param {char*} room - room to ban from
  @param {User*} clnt - user to respond to
*/
void ban(char* name, char* room, User* usr);
// Unban all from chatroom
/*
  @param {char*} room - room to unban from
  @param {User*} clnt - User to respond to
*/
void unBan(char* room, User* clnt);

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
	void rmBan(){
		while(ban.size()>0){
			ban.pop_back();
		}
	}
	vector<int> getBanLst(){
		return ban;
	}
	
};



class Chat {
public:
	static vector<Chatroom *> chatrms;
};